#!/bin/bash
if [ $# -eq 1 ]
then
	cp template.cc "$1.cc"
	subl "$1.cc"
else
	echo "Type \"subl a\" to restart a.cc"
fi
