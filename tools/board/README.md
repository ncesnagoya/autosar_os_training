# Browser board

The browser board shows the four active-low LEDs and DIP switches and lets you
operate PSW1/PSW2. It reads and writes the same `dio.bin` mmap used by athrill3.

## Open the board

The Dev Container starts the server when it starts. Open forwarded port **8989**
in the Ports panel. The server listens on all container interfaces and serves
the board at `/`.

To start it manually from the repository root:

```sh
python3 tools/board/board.py serve --host 0.0.0.0 --port 8989
```

## Simulator status

The line above the board shows whether athrill3 is using this board's
`dio.bin`. The server finds athrill3 processes in `/proc` that map the file,
so it only works when the server runs in the same container as athrill3 (the
Dev Container and Codespaces).

| Lamp | Meaning |
|---|---|
| green | running: athrill3 is simulating; the program directory is shown |
| yellow | stopped: athrill3 used almost no CPU in the last second, for example while it waits at the `[DBG>` prompt |
| grey | not started: no athrill3 uses this `dio.bin`; LEDs display OFF |
| red | two or more athrill3 share this `dio.bin`; stop all but one |

For about a second after athrill3 starts, the line reads "確認中" (checking)
while the first CPU time sample settles.

athrill3 keeps the CPU busy even while the kernel idles, so only the debugger
prompt reads as stopped. The server must run as the same user as athrill3
(`vscode` in the Dev Container); otherwise it cannot read the process's memory
map and reports athrill3 as not started.

`board.py state` includes the same information under `athrill`; it takes one
second to sample the CPU time.

## Command line

The same implementation is available without the browser:

```sh
python3 tools/board/board.py state
python3 tools/board/board.py dsw 1 on
python3 tools/board/board.py dsw 1 off
```

The compatibility scripts `dio_tools/DSW1.sh` through `DSW4.sh` keep their
existing names and accept `on`/`off` (or `1`/`0`). `PSW1.sh` and `PSW2.sh`
accept an optional `on` or `off` argument; without one, they pulse the switch
once. `STATE.sh` keeps redrawing the I/O table until Ctrl-C, like the former
tool; `python3 tools/board/board.py state` prints the values once as JSON.

The GUI and command line both write the mmap directly, so the register value
currently in `dio.bin` is the shared source of truth. athrill3 initializes the
DIP register when it starts; the GUI reflects that value. If the simulator or
mmap is unavailable, LEDs display OFF; their state while the simulator is
stopped is otherwise undefined.
