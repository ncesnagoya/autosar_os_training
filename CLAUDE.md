# CLAUDE.md

This file provides guidance to Claude Code (claude.ai/code) when working with code in this repository.

## Project Overview

AUTOSAR OS learning programs (教材) built on **TOPPERS/ATK2-SC1** (Automotive Kernel v2, Scalability Class 1), targeting Renesas **RH850/F1x** (V850 architecture). Each program under [program/](program/) is a small self-contained example illustrating one OS feature (tasks, ISR2, events, resources, alarms, app-modes, etc.). Maintained by NCES, Nagoya University.

The files in this repository are **UTF-8** (converted from EUC-JP in 2026-11). The kernel tree behind the `atk2-sc1` symlink is not part of the repository and stays EUC-JP.

## Build & Run Environment

The repo expects a cross-compile toolchain that is **not part of this repo**:

- `athrill-gcc` (V850 cross-GCC) at `/usr/local/athrill-gcc`
- `athrill3` (RH850/F1x simulator, toppers/athrill-target-rh850f1x v1.0.0 release, core v3.0.0) at `/home/toppers/athrill-target-rh850f1x/bin`
- `cfg_py` (ATK2 configurator in Python, from exshonda/atk2_sc1_shin) at `atk2-sc1/cfg/cfg_py/`, run as `python3 cfg.py`; no AUTOSAR XML schema is needed
- `abrex.py` (YAML → ARXML, needs PyYAML) at `atk2-sc1/utils/abrex/`
- `atk2-sc1/` (kernel source tree) — present here as a **symlink** to `/home/toppers/atk2-sc1` (devcontainer) or GitHub Codespaces. The symlink target is provisioned by [.devcontainer/base.Dockerfile](.devcontainer/base.Dockerfile), published as `ghcr.io/ncesnagoya/autosar_os_training:debian13`.

Always work inside the devcontainer or Codespaces environment — host-side builds will fail because `atk2-sc1` resolves to a non-existent path.

## Common Commands

All commands run from inside one program directory, e.g. `cd program/led_1task`:

```sh
make             # build → produces ELF `atk2-sc1` plus .srec, .syms, .map, .dump
make exe         # launch athrill3 simulator on the built binary
make clean       # remove build artifacts (objects, generated cfg, libkernel.a)
make realclean   # clean + remove dependency files
make depend      # regenerate Makefile.depend
./abrex.sh       # regenerate the .arxml from the program's .yaml (via abrex.py)
```

`make exe` launches: `athrill3 -c1 -i -d device_config.txt -m memory.txt atk2-sc1`. Stop the simulator with Ctrl-C.

Building one program does **not** build any other; there is no top-level Makefile. The kernel library `libkernel.a` is rebuilt per program directory unless `KERNEL_LIB` is set in the Makefile.

## Architecture

### Per-program layout
Every directory in `program/` follows the same shape (use [program/sample/](program/sample/) as the canonical reference — others are derivatives):

- `<appname>.c` / `.h` — application code (tasks, ISRs, alarms)
- `<appname>.arxml` — AUTOSAR XML config consumed by the `cfg` tool to generate OS objects
- `<appname>.yaml` — higher-level config; `abrex.sh` expands it into `.arxml`
- `Makefile` — invokes the kernel's three-pass configurator and links against `libkernel.a`
- `device_config.txt`, `memory.txt` — athrill simulator configuration
- `cfg/`, `kernel/` — CS+ project subprojects (Renesas IDE; not used in athrill build)
- `atk2-sc1.mtpj`, `*.mtsp`, `*.bat` — CS+ IDE project files (Windows GUI workflow)

The Makefile structure is essentially identical across all programs — the differences are `APPLNAME`, `CFGNAME`, and the application source list. When adding a feature to one program, check whether the same change is needed in the other 16.

### Build pipeline (the `cfg` 3-pass dance)
The Makefile drives a three-pass configurator that is unusual and easy to break:
1. **pass 1**: `cfg --pass 1` reads `*.arxml`, emits `cfg1_out.c`.
2. **pass 2**: link a partial image (`cfg1_out` ELF + S-record + symbol table), then `cfg --pass 2` emits `Os_Lcfg.{c,h}` and `Os_Cfg.h`. The Makefile only overwrites `Os_Cfg.h` when it differs (`cmp` check) to avoid spurious rebuilds.
3. **pass 3**: after the final link, `cfg --pass 3` validates the ROM image against the symbol table.

`offset.h` is generated separately and is required to compile the kernel. Do not hand-edit any `Os_Cfg.*`, `Os_Lcfg.*`, `cfg?_out*`, or `offset.*` — they are regenerated and `.gitignore`d.

### Shared driver
[driver/device.c](driver/device.c) and [driver/device.h](driver/device.h) provide LED / DIP-switch / push-button abstractions used by every program. Constants like `LED1..LED4`, `DSW1..DSW4` live here.

### dio_tools (simulator-side I/O)
[dio_tools/](dio_tools/) is a host-side helper, **not** target code. It builds three native binaries (`digital_state`, `dip_switch`, `push_button`) that interact with athrill via `dio.bin` to inject switch presses and read LED state. The shell wrappers `DSW*.sh`, `PSW*.sh`, `STATE.sh` invoke them. The `dio_tools/` directory is `.gitignore`d — its contents are unzipped from `.devcontainer/dio_tools.zip` at container init by the devcontainer's initialization scripts.

## Editing Notes

- Source files are UTF-8 (`def.py` declares `coding: utf-8`). Keep line endings as they are: many files are CRLF and marked `-text` in `.gitattributes`.
- Two parallel build workflows coexist: **CS+ on Windows** (the `.mtpj`/`.mtsp`/`.bat` files) and **athrill on Linux** (the `Makefile`). Changes to source/config must work for both; do not delete the CS+ project files.
- The kernel target is fixed to `hsbrh850f1k_gcc` in every program Makefile. Don't change this unless switching hardware.
