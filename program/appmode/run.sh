#!/bin/sh

cd "$(dirname "$0")" || exit 1

dsw_list=$*
dio_bin=../../dio_tools/dio.bin
dsw_tool=../../tools/dsw.sh

original_ppr0=$(od -An -tu1 -j 480 -N 1 "$dio_bin" 2>/dev/null | tr -d ' ')
case "$original_ppr0" in
	''|*[!0-9]*) echo "Error: failed to read PPR0 before setting the reset marker." >&2; exit 1 ;;
esac
if [ $((original_ppr0 & 128)) -eq 0 ]; then
	original_dsw1=on
else
	original_dsw1=off
fi

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
		if ! sh "$dsw_tool" "$dio_bin" 1 "$original_dsw1"; then
			echo "Warning: failed to restore the original DSW1 state." >&2
		fi
		return 1
	fi
	# Do not restore DSW1 after reset detection: athrill2 has reset PPR0, so
	# writing the pre-reset state here would incorrectly overwrite that reset.

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
