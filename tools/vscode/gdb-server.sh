#!/bin/sh
# Start athrill3 as a GDB server (-g) for a training program; used by the
# "Debug on athrill (gdb)" launch configuration. Usage: gdb-server.sh <program> [port]
set -eu

repo=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
[ "$#" -ge 1 ] && [ "$#" -le 2 ] || { echo "Usage: $0 <program> [port]" >&2; exit 2; }
dir="$repo/program/$1"
port=${2:-1234}
if [ ! -f "$dir/atk2-sc1" ]; then
	echo "$1 is not built yet; run the Build task first." >&2
	exit 1
fi

# memory.txt names dio.bin relative to the program directory.
cd "$dir"
# athrill3 writes the serial output (syslog) to stderr. cpptools shows only
# the server's stdout in the Debug Console (filterStderr makes the launch
# fail), so send both to stdout.
exec athrill3 -c1 -g "$port" -d device_config.txt -m memory.txt atk2-sc1 2>&1
