#!/bin/sh
# Run a training program on athrill3 (make exe) and report each debugger stop
# as a clickable file:line. Usage: run.sh <program>
set -eu

repo=$(CDPATH= cd -- "$(dirname -- "$0")/../.." && pwd)
[ "$#" -eq 1 ] || { echo "Usage: $0 <program>" >&2; exit 2; }
dir="$repo/program/$1"
if [ ! -f "$dir/atk2-sc1" ]; then
	echo "$1 is not built yet; run the Build task first." >&2
	exit 1
fi

# athrill3 rewrites arg_sakura.txt with "-l <line> <path>" at every stop.
rm -f "$dir/arg_sakura.txt"
python3 "$repo/tools/vscode/follow.py" "$dir/arg_sakura.txt" &
follower=$!
trap 'kill "$follower" 2>/dev/null || true' EXIT
trap 'exit 130' INT TERM

# Same command as "make exe", called directly so that leaving the debugger
# with "exit" (status 1) does not end in a make error.
cd "$dir"
athrill3 -c1 -i -d device_config.txt -m memory.txt atk2-sc1 || true
