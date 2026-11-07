#!/usr/bin/env python3
"""Report where athrill3 stopped, as a file:line that VS Code can open.

At every debugger stop athrill3 rewrites arg_sakura.txt with
"-l <line> <path>" (it used to start an editor with that). This prints the
location as "<path>:<line>", which the VS Code terminal turns into a link.
With ATHRILL_FOLLOW=open it also opens the line in the editor through the
`code` command; the editor then takes the keyboard focus from the terminal.
"""

import os
import shutil
import subprocess
import sys
import time

POLL = 0.1  # seconds
REPEAT = 0.5  # athrill3 writes the file in steps; drop a repeat this soon


def location(path):
    try:
        with open(path, encoding="utf-8", errors="replace") as handle:
            fields = handle.read().split(None, 2)
    except OSError:
        return None
    if len(fields) != 3 or fields[0] != "-l" or not fields[1].isdigit():
        return None
    # The path is relative to the program directory, where athrill3 runs.
    source = os.path.normpath(os.path.join(os.path.dirname(os.path.abspath(path)), fields[2].strip()))
    return f"{source}:{fields[1]}"


def main():
    if len(sys.argv) != 2:
        sys.exit(f"Usage: {sys.argv[0]} <arg_sakura.txt>")
    path = sys.argv[1]
    open_editor = os.environ.get("ATHRILL_FOLLOW") == "open" and shutil.which("code")
    stamp = None
    last, last_time = None, 0.0
    while True:
        try:
            current = os.stat(path).st_mtime_ns
        except OSError:
            current = None
        if current is not None and current != stamp:
            stamp = current
            where = location(path)
            now = time.monotonic()
            if where and not (where == last and now - last_time < REPEAT):
                last, last_time = where, now
                print(f"  -> {where}", flush=True)
                if open_editor:
                    subprocess.run(["code", "--reuse-window", "--goto", where], check=False)
        time.sleep(POLL)


if __name__ == "__main__":
    try:
        main()
    except KeyboardInterrupt:
        pass
