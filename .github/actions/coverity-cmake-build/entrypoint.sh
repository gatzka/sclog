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

wget --quiet https://scan.coverity.com/download/linux64 --post-data "token=${INPUT_COVERITY_TOKEN}&project=gatzka%2Fsclog" -O coverity_tool.tgz
tar -xf coverity_tool.tgz
cd cov-analysis-linux64*
export PATH=$PATH:`pwd`/bin
cd ..
mkdir build
cd build
cov-build

cmake .. ${CMAKE_OPTIONS}
cmake --build . ${CMAKE_BUILD_TARGET}

