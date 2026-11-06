#!/bin/sh
set -eu
script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
if [ -f "$script_dir/../tools/board/board.py" ]; then
    repo=$(CDPATH= cd -- "$script_dir/.." && pwd)
elif [ -f "$script_dir/../board.py" ]; then
    repo=$(CDPATH= cd -- "$script_dir/../../.." && pwd)
else
    echo "Cannot locate tools/board/board.py" >&2
    exit 1
fi
DIO_BIN="$repo/dio_tools/dio.bin" python3 "$repo/tools/board/board.py" watch
