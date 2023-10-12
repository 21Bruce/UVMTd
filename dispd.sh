#!/bin/sh

# Simple script to print info about daemons

ps -A | 
awk '
{
	if ($1 == "PID") {
		print $0
	} else if ($5 == "uvmtd:"){
		print $0
	}
}
'
