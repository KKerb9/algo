#!/bin/bash

a=$1
/opt/homebrew/bin/g++-15 -D_Alignof=__alignof__ -std=c++23 -Wall -Wextra -Wshadow -g -DLOCAL -D_GLIBCXX_DEBUG -O2 "$a.cpp" -o "$a"
