#!/bin/sh

# Simple script to kill daemons

ps -A  |
awk '
{
	if ($5 == "uvmtd:"){
		print $1
	}
}
' | 
while read PID 
do 
	kill $PID
done
