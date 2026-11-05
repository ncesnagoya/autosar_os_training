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
state=${1:-pulse}
case "$state" in
    on|1) DIO_BIN="$repo/dio_tools/dio.bin" python3 "$repo/tools/board/board.py" psw 1 on ;;
    off|0) DIO_BIN="$repo/dio_tools/dio.bin" python3 "$repo/tools/board/board.py" psw 1 off ;;
    pulse) DIO_BIN="$repo/dio_tools/dio.bin" python3 "$repo/tools/board/board.py" psw 1 on; sleep 0.05; DIO_BIN="$repo/dio_tools/dio.bin" python3 "$repo/tools/board/board.py" psw 1 off ;;
    *) echo "Usage: $0 [on|off]" >&2; exit 2 ;;
esac
