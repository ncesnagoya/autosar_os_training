#!/bin/sh

dsw_list=$1
dio_bin=../../dio_tools/dio.bin
dsw_tool=../../tools/dsw.sh

# Make the reset observable even when PPR0 already contains 0xff.
# athrill2 restores this temporary active-low bit before the polling completes.
sh "$dsw_tool" "$dio_bin" 1 on || exit 1

{
	# athrill2 resets PPR0 at startup, so DIP switches must be changed after reset.
	count=0
	while [ "$count" -lt 50 ]; do
		value=$(od -An -tu1 -j 480 -N 1 "$dio_bin" 2>/dev/null | tr -d ' ')
		[ "$value" = "255" ] && break
		count=$((count + 1))
		sleep 0.2
	done

	if [ "$count" -eq 50 ]; then
		echo "Warning: timed out waiting for athrill2 to reset PPR0; continuing." >&2
	fi

	for switch in $dsw_list; do
		case "$switch" in
			1|2|3|4) sh "$dsw_tool" "$dio_bin" "$switch" on ;;
			*) echo "Warning: invalid DSW number '$switch'; skipping." >&2 ;;
		esac
	done

	echo "c"
	exec cat
} | athrill2 -c1 -i -d device_config.txt -m memory.txt atk2-sc1
