set confirm off
set pagination off
set logging file gdb_script_1_log.txt
set logging enabled on
file ./range

break range.c:38 if current % 5 == 0

commands
    printf "@@@ %ld %ld %ld %ld\n", start, stop, step, current
    continue
end

run 1 12 > /dev/null

quit