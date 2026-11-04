#!/usr/bin/env bash
# Prepare a fresh checkout inside the training image (devcontainer
# postCreateCommand; CI runs it too).
set -eu

# atk2-sc1 is not tracked (.gitignore); every program's Makefile reaches the
# kernel tree that the image provides through this link.
if [ ! -e atk2-sc1 ]; then
    ln -s "${ATK2_SC1_DIR:-/home/toppers/atk2-sc1}" atk2-sc1
fi

if [ ! -f dio_tools/dio.bin ]; then
    unzip -q -o .devcontainer/dio_tools.zip
fi

chmod 755 dio_tools/*.sh dio_tools/dip_switch dio_tools/push_button dio_tools/digital_state
