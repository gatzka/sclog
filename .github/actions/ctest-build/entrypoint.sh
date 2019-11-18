#!/bin/sh

set -eu

if [ "x$INPUT_INSTALL_DEPS" != 'x' ]; then
  apt-get update
  pwd
  ls -la
  echo "${INPUT_INSTALL_DEPS}"
  source ${INPUT_INSTALL_DEPS}
  apt-get clean -y
fi

ctest -S build.cmake
