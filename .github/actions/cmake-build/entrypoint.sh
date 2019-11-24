#!/bin/bash
set -ex

if [ "x$INPUT_INSTALL_DEPS" != 'x' ]; then
  apt-get update
  source ${INPUT_INSTALL_DEPS}
  apt-get clean -y
fi

CMAKE_OPTIONS="-DCMAKE_BUILD_TYPE:STRING="
if [ "x$INPUT_CMAKE_BUILD_TYPE" == 'x' ]; then
	INPUT_CMAKE_BUILD_TYPE="Debug"
fi
CMAKE_OPTIONS+=${INPUT_CMAKE_BUILD_TYPE}

if [ "x$INPUT_CMAKE_TOOLCHAIN_FILE" != 'x' ]; then
	CMAKE_OPTIONS+=" -DCMAKE_TOOLCHAIN_FILE:STRING="${INPUT_CMAKE_TOOLCHAIN_FILE}
fi

if [ "x$INPUT_CMAKE_BUILD_TARGET" != 'x' ]; then
	CMAKE_BUILD_TARGET+=" --target "${INPUT_CMAKE_BUILD_TARGET}
fi

mkdir build
cd build

cmake .. ${CMAKE_OPTIONS}
cmake --build . ${CMAKE_BUILD_TARGET}

