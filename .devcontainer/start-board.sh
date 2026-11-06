#!/bin/sh
# Start the board server in the background (devcontainer postStartCommand).
set -eu

cd "$(dirname "$0")/.."
port=8989
url="http://127.0.0.1:$port/api/state"
log=/tmp/autosar-os-training-board.log

answers()
{
	python3 -c "import urllib.request,sys; urllib.request.urlopen(sys.argv[1], timeout=1)" "$url" 2>/dev/null
}

if answers; then
	exit 0
fi

nohup setsid python3 tools/board/board.py serve --host 0.0.0.0 --port "$port" </dev/null >"$log" 2>&1 &

# VS Code tears down the lifecycle command's session as soon as this script
# returns. Wait until the server answers so it is fully detached by then;
# python3 starts slowly under x86_64 emulation on Apple silicon.
i=0
while [ "$i" -lt 30 ]; do
	if answers; then
		echo "Board: http://localhost:$port/"
		exit 0
	fi
	i=$((i + 1))
	sleep 1
done
echo "Board did not start; see $log" >&2
exit 1
