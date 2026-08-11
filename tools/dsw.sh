#!/bin/sh

usage()
{
	echo "Usage: $0 <dio.bin> <1-4> <on|off|1|0>" >&2
	exit 1
}

[ "$#" -eq 3 ] || usage

dio_bin=$1
switch=$2
state=$3

case "$switch" in
	1) offset=480; mask=128 ;;
	2) offset=481; mask=1 ;;
	3) offset=481; mask=2 ;;
	4) offset=481; mask=4 ;;
	*) usage ;;
esac

case "$state" in
	on|1) turn_on=true ;;
	off|0) turn_on=false ;;
	*) usage ;;
esac

[ -f "$dio_bin" ] && [ -r "$dio_bin" ] && [ -w "$dio_bin" ] || usage

# Read and update only the bit assigned to the selected active-low switch.
value=$(od -An -tu1 -j "$offset" -N 1 "$dio_bin") || exit 1
[ -n "$value" ] || exit 1

if [ "$turn_on" = true ]; then
	value=$((value & (255 ^ mask)))
else
	value=$((value | mask))
fi

octal=$(printf '%03o' "$value") || exit 1
if ! printf "\\$octal" | dd of="$dio_bin" bs=1 seek="$offset" count=1 conv=notrunc 2>/dev/null; then
	echo "Error: failed to write $dio_bin." >&2
	exit 1
fi
