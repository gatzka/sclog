#!/bin/bash
set -ex

if [ "x$INPUT_INSTALL_DEPS" != 'x' ]; then
  apt-get update
  pwd
  ls -la
  echo "${INPUT_INSTALL_DEPS}"
  source ${INPUT_INSTALL_DEPS}
  apt-get clean -y
fi

if [ "x$INPUT_CTEST_CONFIGURATION_TYPE" == 'x' ]; then
	INPUT_CTEST_CONFIGURATION_TYPE = "Debug"
fi

ctest -VV -S build.cmake -DSCLOG_CTEST_TOOLCHAIN_FILE:STRING=${INPUT_CTEST_TOOLCHAIN_FILE} -DSCLOG_CTEST_CONFIGURATION_TYPE:STRING=${INPUT_CTEST_CONFIGURATION_TYPE}
