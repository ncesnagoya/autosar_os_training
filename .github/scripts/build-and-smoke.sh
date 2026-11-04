#!/bin/bash
# Build every training program and check that each one boots on athrill.
#
# Runs inside the devcontainer image (athrill-gcc, cfg, atk2-sc1 and athrill2
# installed). The serial output of channel 1 goes to stderr; a program passes
# the smoke test when the ATK2 start-up banner appears there.
set -u

repo="$(cd "$(dirname "$0")/../.." && pwd)"
cd "$repo"

# atk2-sc1 is not tracked (.gitignore); it links to the kernel tree that the
# image provides, as .setup.sh does in the devcontainer.
if [ ! -e atk2-sc1 ]; then
    ln -s "${ATK2_SC1_DIR:-/home/toppers/atk2-sc1}" atk2-sc1
fi

# dio_tools/dio.bin is the memory-mapped I/O file named in memory.txt.
if [ ! -f dio_tools/dio.bin ]; then
    unzip -q -o .devcontainer/dio_tools.zip
fi

clocks="${SMOKE_CLOCKS:-30000000}"
failed=0

for dir in program/*/; do
    name="$(basename "$dir")"
    if ! make -C "$dir" > "$dir/build.log" 2>&1; then
        echo "::error title=build failed::$name"
        tail -n 30 "$dir/build.log"
        failed=1
        continue
    fi
    # athrill2 exits with status 1 when it stops at the -t clock limit;
    # treat that as success when it says so on stdout.
    ( cd "$dir" && timeout 120 athrill2 -c1 -t "$clocks" \
        -d device_config.txt -m memory.txt atk2-sc1 \
        > athrill.stdout 2> athrill.serial )
    status=$?
    if [ $status -ne 0 ] && ! grep -q "EXIT for timeout" "$dir/athrill.stdout"; then
        echo "::error title=athrill failed (status $status)::$name"
        tail -n 20 "$dir/athrill.stdout"
        failed=1
        continue
    fi
    if grep -q "TOPPERS/ATK2-SC1" "$dir/athrill.serial"; then
        echo "ok   $name"
    else
        echo "::error title=no start-up banner::$name"
        cat "$dir/athrill.serial"
        failed=1
    fi
done

exit $failed
