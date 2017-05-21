#!/bin/bash
g++ -std=c++0x -fmax-errors=1 -O2 -DLOCAL "$1.cc" -o $1
./$@
rm $1
