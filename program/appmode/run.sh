#!/bin/sh

cd "$(dirname "$0")" || exit 1

dsw_list=$*
dio_bin=../../dio_tools/dio.bin
dsw_tool=../../tools/dsw.sh

# Make the reset observable even when PPR0 already contains 0xff.
# athrill2 restores this temporary active-low bit before the polling completes.
sh "$dsw_tool" "$dio_bin" 1 on || exit 1

run_commands()
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
		echo "Error: timed out waiting for athrill2 to reset PPR0." >&2
		return 1
	fi

	for switch in $dsw_list; do
		case "$switch" in
			1|2|3|4)
				if ! sh "$dsw_tool" "$dio_bin" "$switch" on; then
					echo "Error: failed to configure DSW $switch." >&2
					return 1
				fi
				;;
			*) echo "Warning: invalid DSW number '$switch'; skipping." >&2 ;;
		esac
	done

	echo "c"
	cat
	return 0
}

status_file=$(mktemp "${TMPDIR:-/tmp}/appmode-run.XXXXXX") || exit 1
trap 'rm -f "$status_file"' 0 1 2 3 15

{
	run_commands
	echo "$?" > "$status_file"
} | athrill2 -c1 -i -d device_config.txt -m memory.txt atk2-sc1
athrill_status=$?
run_status=$(cat "$status_file") || exit 1

[ "$run_status" -eq 0 ] || exit "$run_status"
exit "$athrill_status"
