#!/usr/bin/env python3
"""Browser board and portable command line tools for the athrill3 DIO mmap."""

import argparse
import json
import mmap
import os
from pathlib import Path
import threading
from http.server import BaseHTTPRequestHandler, ThreadingHTTPServer


ROOT = Path(__file__).resolve().parents[2]
DIO_PATH = Path(os.environ.get("DIO_BIN", ROOT / "dio_tools" / "dio.bin"))
LED_OFFSET = 0
DSW_OFFSETS = ((480, 0x80), (481, 0x01), (481, 0x02), (481, 0x04))
PSW_OFFSET = 512
LOCK = threading.RLock()


def read_bytes():
    with DIO_PATH.open("rb") as dio:
        if DIO_PATH.stat().st_size <= PSW_OFFSET:
            raise OSError(f"{DIO_PATH} is too short")
        return dio.read(PSW_OFFSET + 1)


def update_byte(offset, mask, value):
    with LOCK, DIO_PATH.open("r+b") as dio:
        if os.fstat(dio.fileno()).st_size <= offset:
            raise OSError(f"{DIO_PATH} is too short")
        with mmap.mmap(dio.fileno(), 0) as mapped:
            current = mapped[offset]
            mapped[offset] = (current | mask) if value else (current & (0xFF ^ mask))
            mapped.flush()


def state():
    data = read_bytes()
    return {
        "available": True,
        "led": [not bool(data[0] & (1 << bit)) for bit in range(4, 8)],
        "dsw": [not bool(data[offset] & mask) for offset, mask in DSW_OFFSETS],
        "psw": [bool(data[PSW_OFFSET] & (1 << bit)) for bit in range(2)],
    }


CLOCK_TICKS = os.sysconf("SC_CLK_TCK") if hasattr(os, "sysconf") else 100
SAMPLE_PERIOD = 1.0  # seconds between CPU time samples
BUSY_RATIO = 0.2  # CPU share above which athrill3 counts as executing
SAMPLES = {}  # pid -> (sample time, cpu ticks, executing)


def cpu_ticks(pid):
    with open(f"/proc/{pid}/stat", encoding="ascii") as stat:
        # The command name may contain spaces; fields after it are fixed.
        fields = stat.read().rsplit(")", 1)[1].split()
    return int(fields[11]) + int(fields[12])  # utime + stime


def executing(pid, now):
    """Report whether the process used CPU over the last sample period.

    athrill3 spins while it simulates, even when the kernel idles, and sleeps
    while it waits at the debugger prompt, so its CPU time tells the two
    apart. Returns None until a full sample period has passed.
    """
    ticks = cpu_ticks(pid)
    with LOCK:
        previous = SAMPLES.get(pid)
        if previous is None:
            SAMPLES[pid] = (now, ticks, None)
            return None
        then, old_ticks, busy = previous
        if now - then >= SAMPLE_PERIOD:
            busy = (ticks - old_ticks) / CLOCK_TICKS / (now - then) > BUSY_RATIO
            SAMPLES[pid] = (now, ticks, busy)
        return busy


def athrill_status(settle=False):
    """Find athrill3 processes that map this board's dio.bin (Linux only).

    With settle, sample twice so that a one-shot caller gets a real answer.
    """
    import time

    if settle:
        athrill_status()
        time.sleep(SAMPLE_PERIOD)
    proc = Path("/proc")
    if not (proc / "self" / "maps").exists():
        return {"supported": False}
    target = os.path.realpath(DIO_PATH)
    now = time.monotonic()
    found = []
    for entry in proc.iterdir():
        if not entry.name.isdigit():
            continue
        try:
            if (entry / "comm").read_text(encoding="utf-8").strip() != "athrill3":
                continue
            maps = (entry / "maps").read_text(encoding="utf-8", errors="replace")
            if not any(line.split(None, 5)[-1] == target for line in maps.splitlines() if "/" in line):
                continue
            pid = int(entry.name)
            found.append({
                "pid": pid,
                "program": os.path.basename(os.readlink(entry / "cwd")),
                "executing": executing(pid, now),
            })
        except (OSError, ValueError, IndexError):
            continue  # the process exited or is not ours
    with LOCK:
        for pid in set(SAMPLES) - {item["pid"] for item in found}:
            del SAMPLES[pid]
    found.sort(key=lambda item: item["pid"])
    return {"supported": True, "instances": found}


def watch(interval=0.1):
    """Redraw the I/O table until Ctrl-C, like the former digital_state tool."""
    import sys
    import time

    on_off = lambda value: " ON" if value else "OFF"
    try:
        while True:
            try:
                current = state()
            except (OSError, ValueError):
                current = {"led": [False] * 4, "dsw": [False] * 4, "psw": [True, True]}
            lines = ["**** DIGITAL STATE ****"]
            lines += [f"     LED{i + 1} : {on_off(v)}" for i, v in enumerate(current["led"])]
            lines += [f"     DSW{i + 1} : {on_off(v)}" for i, v in enumerate(current["dsw"])]
            # Push switches read 1 while released.
            lines += [f"     PSW{i + 1} : {on_off(not v)}" for i, v in enumerate(current["psw"])]
            sys.stdout.write("\033[2J\033[H" + "\n".join(lines) + "\n")
            sys.stdout.flush()
            time.sleep(interval)
    except KeyboardInterrupt:
        sys.stdout.write("\n")


class Handler(BaseHTTPRequestHandler):
    def log_message(self, _format, *_args):
        return

    def respond(self, code, body, content_type="application/json; charset=utf-8"):
        encoded = body.encode("utf-8")
        self.send_response(code)
        self.send_header("Content-Type", content_type)
        self.send_header("Content-Length", str(len(encoded)))
        self.send_header("Cache-Control", "no-store")
        self.end_headers()
        self.wfile.write(encoded)

    def do_GET(self):
        if self.path == "/api/state":
            try:
                current = state()
            except (OSError, ValueError):
                current = {"available": False, "led": [False] * 4, "dsw": [False] * 4, "psw": [False] * 2}
            current["athrill"] = athrill_status()
            self.respond(200, json.dumps(current))
            return
        if self.path in ("/", "/index.html"):
            try:
                page = (Path(__file__).parent / "index.html").read_text(encoding="utf-8")
                self.respond(200, page, "text/html; charset=utf-8")
            except OSError as error:
                self.respond(500, str(error), "text/plain; charset=utf-8")
            return
        self.respond(404, "{}")

    def do_POST(self):
        if self.path not in ("/api/dsw", "/api/psw"):
            self.respond(404, "{}")
            return
        try:
            payload = json.loads(self.rfile.read(int(self.headers.get("Content-Length", "0"))))
            number = int(payload["number"])
            enabled = payload["on"]
            if not isinstance(enabled, bool):
                raise ValueError("on must be boolean")
            if self.path == "/api/dsw" and number in range(1, 5):
                offset, mask = DSW_OFFSETS[number - 1]
                # DIP inputs are active low: an ON switch clears its bit.
                update_byte(offset, mask, not enabled)
            elif self.path == "/api/psw" and number in range(1, 3):
                # Push switches are active high; on press drive low, on release high.
                update_byte(PSW_OFFSET, 1 << (number - 1), not enabled)
            else:
                raise ValueError("invalid switch number")
            self.respond(200, json.dumps(state()))
        except (KeyError, TypeError, ValueError, OSError, json.JSONDecodeError) as error:
            self.respond(400, json.dumps({"error": str(error)}))


def command_line():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="command", required=True)
    sub.add_parser("state")
    sub.add_parser("watch")
    dsw = sub.add_parser("dsw")
    dsw.add_argument("number", type=int, choices=range(1, 5))
    dsw.add_argument("state", choices=("on", "off", "1", "0"))
    psw = sub.add_parser("psw")
    psw.add_argument("number", type=int, choices=(1, 2))
    psw.add_argument("state", choices=("on", "off", "1", "0"))
    psw.add_argument("--dio-bin", help="DIO mmap file (defaults to the repository dio.bin)")
    server = sub.add_parser("serve")
    server.add_argument("--host", default="127.0.0.1")
    server.add_argument("--port", type=int, default=8989)
    args = parser.parse_args()
    if getattr(args, "dio_bin", None):
        global DIO_PATH
        DIO_PATH = Path(args.dio_bin)
    if args.command == "state":
        current = state()
        current["athrill"] = athrill_status(settle=True)
        print(json.dumps(current))
    elif args.command == "watch":
        watch()
    elif args.command == "dsw":
        update_byte(*DSW_OFFSETS[args.number - 1], args.state not in ("on", "1"))
    elif args.command == "psw":
        update_byte(PSW_OFFSET, 1 << (args.number - 1), args.state not in ("on", "1"))
    else:
        server = ThreadingHTTPServer((args.host, args.port), Handler)
        print(f"Board UI listening on http://{args.host}:{args.port}", flush=True)
        server.serve_forever()


if __name__ == "__main__":
    command_line()
