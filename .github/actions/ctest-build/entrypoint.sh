#!/bin/sh

set -eu
echo "Hello action"
ls -l
ctest -S build.cmake
