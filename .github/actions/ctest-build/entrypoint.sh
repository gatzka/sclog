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

CTEST_OPTIONS="-DSCLOG_CTEST_CONFIGURATION_TYPE:STRING="
if [ "x$INPUT_CTEST_CONFIGURATION_TYPE" == 'x' ]; then
	CTEST_OPTIONS+="Debug"
	INPUT_CTEST_CONFIGURATION_TYPE = "Debug"
else
	CTEST_OPTIONS+=${INPUT_CTEST_CONFIGURATION_TYPE}
fi

if ["x$INPUT_CTEST_TOOLCHAIN_FILE" != 'x']; then
	CTEST_OPTIONS+="-DSCLOG_CTEST_TOOLCHAIN_FILE:STRING="${INPUT_CTEST_TOOLCHAIN_FILE}
fi

if ["x$INPUT_CTEST_ANALYZER" != 'x']; then
	CTEST_OPTIONS+="-DSCLOG_CTEST_ANALYZER:STRING="${INPUT_CTEST_ANALYZER}
fi

ctest -VV -S build.cmake ${CTEST_OPTIONS}

