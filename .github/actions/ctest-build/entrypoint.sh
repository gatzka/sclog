#!/bin/sh

set -eu
echo "Hello action"
ls -l
ctest -VV -S build.cmake
