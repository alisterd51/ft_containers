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
CC=clang CXX=clang++ cmake ..
if cmake --build .
then
	./test1
	./test2
	./test3
	./stack_test
fi
