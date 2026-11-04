#!/usr/bin/env bash
set -eu

if [ ! -f dio_tools/dio.bin ]; then
    unzip -q -o .devcontainer/dio_tools.zip
fi

chmod 755 dio_tools/*.sh dio_tools/dip_switch dio_tools/push_button dio_tools/digital_state
