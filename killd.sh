#!/bin/sh

# Simple script to kill daemons

ps -A | awk '
BEGIN { }
{
	if ($5 == "uvmtd:"){
		print $1
	}
}
END { }
' | 
while read PID 
do 
	kill $PID
done
