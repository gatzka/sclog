#!/bin/sh

set -eu

if [ "x$INPUT_INSTALL_DEPS" != 'x' ]; then
  echo "got dependency script: $INPUT_INSTALL_DEPS"
else
  echo "no dependency script"
fi

ctest -VV -S build.cmake
