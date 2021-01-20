echo "exit 2" > test.sh; bash test.sh; echo $?; rm test.sh

export TEST=CODAM; echo $TEST; unset TEST; echo $TEST
