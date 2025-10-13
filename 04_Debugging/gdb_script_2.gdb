set confirm off
set pagination off
set logging file gdb_script_2_log.txt
set logging enabled on
file ./range

set $counter = 0
break range.c:38

commands
    set $counter = $counter + 1
    if $counter >= 28 && $counter <= 35
        printf "@@@ %ld %ld %ld %ld\n", start, stop, step, current
    end
    continue
end

run -100 100 3 > /dev/null

quit