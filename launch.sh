#!/bin/sh

make cppview
LD_LIBRARY_PATH=`pwd`/freenect_cpp/lib/ ./cppview
