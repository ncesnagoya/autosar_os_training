# Build, run and debug from VS Code

`.vscode/tasks.json` builds and runs the training programs from VS Code. Each
task asks which program to use. The tasks set `reevaluateOnRerun` to false,
so **Tasks: Rerun Last Task** should run the same task again with the program
chosen last time instead of asking again.

| Task | What it does |
|---|---|
| Build (`Ctrl+Shift+B`) | `make` in `program/<program>`. Compiler errors appear in the Problems panel. |
| Build for debugging (-O0) | `make clean`, then `make OMIT_OPTIMIZATION=1`. Without `-O2` the code follows the source order and `print` can find local variables. |
| Run on athrill | Starts athrill3 in the debugger, as `make exe` does. |
| Clean | `make clean`. |

Run the Clean task before going back from the debugging build to the normal
one: `make` alone does not rebuild objects when only the options change.

## Debugging in the editor (F5)

`.vscode/launch.json` has the configuration **Debug on athrill (gdb)**. It
starts athrill3 as a GDB server (`athrill3 -g 1234`, through
`tools/vscode/gdb-server.sh`) and connects `gdb-multiarch` to it, so the
usual VS Code debugger works on the source: breakpoints in the editor
margin, Step Over / Into / Out, variables, watch and the call stack.

1. Build the program with **Build for debugging (-O0)**.
2. Open **Run and Debug**, choose **Debug on athrill (gdb)** and press F5.
3. Choose the same program as in step 1.

The program stops at the reset vector (`_tp` in `prc_support.S`). Set
breakpoints, then press Continue (F5). Pause stops a running program, and
Stop ends athrill3.

The program's serial output (`syslog`) appears in the **Debug Console**, with
a `gdb-server:` prefix and mixed with athrill3's start-up messages and GDB's
output. athrill3 writes it to stderr; `gdb-server.sh` sends it to stdout,
which cpptools shows there.

Notes:

- Only one debug session runs at a time: it uses port 1234.
- Reading a peripheral register in the Watch or Memory view reads the device,
  which may change its state.
- athrill3 needs the Athrill core v3.1.0 or later (`-g`), and the image needs
  `gdb-multiarch`.

## Debugging in the terminal

Run on athrill stops at the reset vector with a `[DBG>` prompt. Type the
debugger commands in that terminal, for example:

```text
break toppers_atk2.c 136    stop at a source line
cont                        run until the next stop
next                        execute one instruction
print <variable>            show a variable
bt                          show the call stack
exit                        leave athrill3
```

`help` lists every command. At each stop the terminal also prints the
location as a full path, such as
`-> /workspaces/autosar_os_training/program/led_1task/toppers_atk2.c:136`.
Ctrl+click (Cmd+click on macOS) the path to open that line.

To have the editor jump to the line at every stop, set `ATHRILL_FOLLOW=open`
before running the task (for example in the `env` of the task's `options`).
The editor then takes the keyboard focus, so click the terminal again before
typing the next command.

`tools/vscode/run.sh <program>` does the same as the Run task from any
terminal.
