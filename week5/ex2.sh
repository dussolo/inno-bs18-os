#!/usr/bin/env bash

function lock {
	ln -s $1 "$1.lck" >/dev/null 2>/dev/null
}

function unlock {
	rm -f "$1.lck" >/dev/null 2>/dev/null
}

function last_num {
	cat $1 | tr ' ' "\n" | tail -n 1
}

function step {
	FILE=$1

	LAST=$(last_num $FILE)
	printf "%d " $(($LAST + 1)) >>$FILE
}

function onexit {
	echo Exiting normally
	
	unlock $1
	exit $?
}

lock $1

if [[ $? -ne 0 ]]; then
	echo File is locked

	exit -1
fi

trap "onexit $1" SIGINT

while true; do
	step $1
	sleep 0.1
done
