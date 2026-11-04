# AUTOSAR OS Training Programs

A collection of learning programs based on TOPPERS/ATK2 for studying AUTOSAR OS fundamentals. Targeting Renesas RH850/F1x microcontrollers, these programs enable step-by-step learning of core AUTOSAR OS features including tasks, interrupts, events, resources, alarms, and application modes.

**Developed by**: Nagoya University, Graduate School of Information Science, Center for Embedded Computing Systems (NCES)

## Features

- **17 Programs** — 16 learning programs, each focused on a single OS feature, plus a `sample` template
- **TOPPERS/ATK2** — Open-source RTOS compliant with AUTOSAR specification
- **athrill Simulator Support** — Run and verify programs on PC without hardware
- **Web-Based Development** — Use GitHub Codespaces directly from your browser
- **CS+ IDE (Windows) & Makefile (Linux / containers)** — Both workflows supported
- **Dev Containers Ready** — Easy local development with WSL support on Windows

## Learning Programs List

| Program | Description |
|---------|-------------|
| `led_1task` | LED blinking with a single task |
| `device_log_1task` | LED / push switch / DIP switch control |
| `multi_task_active` | Fully preemptive task activation |
| `multi_task_nonpre` | Non-preemptive task activation |
| `multi_task_actqueu` | Task activation queuing confirmation |
| `multi_task_chain` | Task activation via ChainTask |
| `int_isr2` | ISR2 interrupt handler execution |
| `int_disint` | Interrupt enable/disable control |
| `event_task` | Event notification via task |
| `event_int` | Event notification via interrupt |
| `resources_task_int` | Mutual exclusion using resources |
| `internal_resources` | Mutual exclusion using internal resources |
| `alarm_hwcounter` | Alarm using hardware counter |
| `alarm_swcounter` | Alarm using software counter |
| `appmode` | Task switching via application mode |
| `console_in` | Console input program |
| `sample` | Template program |

## Development Environment Setup

Multiple options are available to get started quickly without tedious setup. Choose one of the following:

### 1. GitHub Codespaces (Easiest & Recommended)

If you have a GitHub account, you can develop directly in your browser with no setup required.

1. Open this repository on GitHub
2. Click **Code** button → **Codespaces** → **Create codespace on main**
3. VS Code launches in your browser with the environment automatically configured
4. Ready to run `make` and `make exe` immediately

**Advantages**:
- Completely zero setup/installation required
- Works from school PCs, Chromebooks, and any device with a browser
- Always uses the latest environment
- No local resources needed

### 2. Local Development with Dev Containers

For offline development on your own PC using Docker and VS Code.

#### Requirements
- **Docker Desktop** or compatible Docker runtime
- **VS Code** + **Dev Containers extension**
- **WSL 2** on Windows (Windows Subsystem for Linux)

#### Setup on Windows + WSL

1. **Install WSL 2**
   ```bash
   wsl --install
   ```
   (Run PowerShell as Administrator)

2. **Install Docker Desktop**
   - Download from https://www.docker.com/products/docker-desktop
   - After installation, enable WSL 2 integration:
     - Docker Desktop Settings → Resources → WSL integration → Enable integration with your WSL distros

3. **Install VS Code**
   - Download from https://code.visualstudio.com/
   - Install the `Dev Containers` extension

4. **Open the Repository**
   ```bash
   git clone https://github.com/ncesnagoya/autosar_os_training.git
   cd autosar_os_training
   code .
   ```

5. **Start Dev Container**
   - Click the **`><`** icon in the bottom-left of VS Code
   - Select **"Reopen in Container"**
   - The first run pulls the prebuilt image `ghcr.io/ncesnagoya/autosar_os_training:debian13` (about 2 GB)

6. **Develop in VS Code Integrated Terminal**
   ```bash
   cd program/led_1task
   make
   make exe
   ```

#### Setup on macOS / Linux

Same process: install Docker and VS Code, then "Reopen in Container".
The image is built for `linux/amd64`; on Apple silicon Macs it runs under Docker Desktop's x86_64 emulation.

**Advantages**:
- Full offline development capability
- Comfortable local file editing
- Access to all IDE features

### Manual Setup (Not Recommended)

If you need to install all tools directly on your host system:

- **athrill-gcc** — V850/RH850 cross-compiler
- **athrill3** — RH850/F1x simulator
- **cfg_py** — ATK2 configurator in Python (from [atk2_sc1_shin](https://github.com/exshonda/atk2_sc1_shin)), placed at `atk2-sc1/cfg/cfg_py/`
- **abrex.py** — YAML → ARXML generator, placed at `atk2-sc1/utils/abrex/`
- **make**, **perl**, **python3**, **PyYAML**

See [.devcontainer/base.Dockerfile](.devcontainer/base.Dockerfile) for the exact versions.

**Note**: Manual setup is complex and time-consuming. One of the two methods above is strongly recommended.

## Quick Start

### 1. Navigate to a Program

```bash
cd program/led_1task  # or choose another program
```

### 2. Build

```bash
make
```

This automatically:
- Generates OS configuration from AUTOSAR XML (`*.arxml`)
- Compiles V850 assembly objects
- Builds the kernel library (`libkernel.a`)
- Links the final ELF binary (`atk2-sc1`)

### 3. Run in athrill Simulator

```bash
make exe
```

The simulator launches and runs the program. Exit with `Ctrl-C`.

### 4. Cleanup

```bash
make clean       # Remove build artifacts
make realclean   # Remove all generated files
```

## athrill Simulation Environment

**athrill** is an instruction-level simulator for RH850/F1x microcontrollers developed by the TOPPERS project. This project uses athrill to enable full verification of AUTOSAR OS program behavior on your PC without purchasing hardware boards.

### athrill Features

- **Instruction-Level Simulation** — Accurately models V850/RH850 CPU, memory, and peripherals
- **Real-time Verification** — Confirm task priority scheduling, timeouts, and interrupt handling
- **I/O Simulation** — Control LEDs, DIP switches, and push buttons via `dio_tools`
- **Trace & Debug** — Record CPU clock cycles and logs to trace program execution

### athrill3 Execution Model

```
[Target ELF Binary (atk2-sc1)]
         ↓
   [athrill3 Simulator]
         ↓
  [Virtual Memory / Registers]
         ↓
 [I/O Output via dio_tools]
         ↓
   [LED Status & Log Display]
```

The built ELF binary contains V850/RH850 machine code, but athrill3 executes it on your PC (x86_64 Linux, or the container).

### Running and Verification

```bash
cd program/led_1task
make exe
```

This executes:

```
athrill3 -c1 -i -d device_config.txt -m memory.txt atk2-sc1
```

Options:
- `-c1` : Single CPU core
- `-i` : Interactive mode (step execution, breakpoints)
- `-d device_config.txt` : Device configuration
- `-m memory.txt` : Memory map configuration
- `atk2-sc1` : Target ELF binary

During simulation, you see:
- Task activation logs
- LED on/off events
- Interrupt handling
- Error messages

### I/O Verification

In a separate terminal, use `dio_tools`:

```bash
# Check current LED state
./dio_tools/STATE.sh

# Toggle DIP switch (program reads this)
./dio_tools/DSW1.sh on
./dio_tools/DSW1.sh off

# Simulate push button (triggers interrupt)
./dio_tools/PSW1.sh
```

You can verify that your program correctly controls LEDs and responds to switch interrupts.

### Real Hardware Alternative

To run on actual hardware, use the Renesas **HSBRH850F1L100** board + **E1 Emulator** + **CS+ IDE**. See "Hardware Execution (Optional)" section for details.

## Directory Structure

```
autosar_os_training/
├── program/              # Learning programs (17 directories)
│   ├── led_1task/
│   ├── multi_task_active/
│   ├── sample/          # Reference template
│   └── ...
├── driver/              # Shared driver code
│   ├── device.c         # LED / switch abstraction
│   └── device.h
├── dio_tools/           # Simulator I/O tools (extracted at container init)
│   ├── dip_switch       # DIP switch simulation
│   ├── push_button      # Push button simulation
│   └── ...
├── atk2-sc1/            # ATK2 kernel source (symlink)
├── tools/               # Helper scripts
├── .devcontainer/       # Dev Containers config and image Dockerfile
├── .github/             # CI (builds the image and runs every program)
└── CLAUDE.md            # AI coding assistance guide
```

## Program Structure

Typical structure of each program directory:

```
program/led_1task/
├── toppers_atk2.c       # Application code
├── toppers_atk2.h       # Header file
├── toppers_atk2.arxml   # AUTOSAR XML configuration
├── toppers_atk2.yaml    # YAML config (expanded to .arxml via abrex)
├── Makefile             # Build script
├── device_config.txt    # athrill device configuration
├── memory.txt           # athrill memory configuration
├── atk2-sc1.mtpj        # CS+ project (Windows IDE)
├── cfg/                 # Configuration (CS+ use)
├── kernel/              # Kernel (CS+ use)
└── abrex.sh / abrex.bat # YAML → ARXML conversion script
```

## YAML to ARXML Generation

When modifying YAML configuration:

```bash
./abrex.sh
```

This regenerates `*.arxml` from `*.yaml` (via abrex.py; needs Python 3 and PyYAML).

## Simulator I/O Operations

The `dio_tools/` directory contains utilities to simulate LED control and switch input:

```bash
# Display LED status
./dio_tools/STATE.sh

# Toggle DIP switch
./dio_tools/DSW1.sh on
./dio_tools/DSW1.sh off

# Simulate push button
./dio_tools/PSW1.sh
```

## Character Encoding

All source files and documentation in this repository are encoded in **UTF-8**.
The TOPPERS/ATK2 kernel sources under `atk2-sc1` are not part of this repository and keep their original EUC-JP encoding.

## References

- [TOPPERS Project](https://www.toppers.jp/)
- [TOPPERS/ATK2 Documentation](https://www.toppers.jp/atk2.html)
- [AUTOSAR Specification](https://www.autosar.org/)
- [athrill Simulator](https://github.com/toppers/athrill-target-rh850f1x)

## Hardware Execution (Optional)

To run on real hardware without a PC:

- **Renesas HSBRH850F1L100** — Target board
- **E1 Emulator** — On-board programming and debugging
- **Renesas CS+** — IDE (free evaluation version available)

See [README.txt](README.txt) for hardware details.

## Troubleshooting

### `atk2-sc1` not found
Run inside the container. The `atk2-sc1` symlink target doesn't exist on the host.

### `cfg` command not found
Verify that `athrill-gcc`, `athrill3`, `python3`, and `atk2-sc1/cfg/cfg_py/cfg.py` are available.  
Codespaces and Dev Containers provide these automatically.

### Build fails
```bash
make realclean
make depend
make
```

Reset dependencies and rebuild.

## License

TOPPERS License (similar to BSD License). See [README.txt](README.txt) for details.

## Development & Contribution

This repository is for learning purposes. General feature additions are not expected.  
Please report bugs or suggest improvements via GitHub Issues.

---

**Last Updated**: November 2026  
**Repository**: https://github.com/ncesnagoya/autosar_os_training
