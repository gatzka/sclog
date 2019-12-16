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

wget --quiet http://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
unzip build-wrapper-linux-x86.zip
export PATH=$PATH:`pwd`/build-wrapper-linux-x86/


