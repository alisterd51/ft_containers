#!/usr/bin/env sh

######################################################################
# @author      : anclarma (anclarma@$HOSTNAME)
# @file        : test
# @created     : Monday May 09, 2022 00:40:28 CEST
#
# @description : 
######################################################################

mkdir debug
cd debug
cmake ..
cmake --build .
./test1
./test2
./test3
