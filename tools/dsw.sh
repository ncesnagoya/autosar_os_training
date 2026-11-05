#!/bin/sh
set -eu
[ "$#" -eq 3 ] || { echo "Usage: $0 <dio.bin> <1-4> <on|off|1|0>" >&2; exit 2; }
dio_bin=$1
switch=$2
state=$3
script_dir=$(CDPATH= cd -- "$(dirname -- "$0")" && pwd)
export DIO_BIN=$dio_bin
exec python3 "$script_dir/board/board.py" dsw "$switch" "$state"
