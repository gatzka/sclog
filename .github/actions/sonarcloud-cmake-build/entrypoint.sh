#!/bin/bash
set -ex

if [ "x$INPUT_INSTALL_DEPS" != 'x' ]; then
  apt-get update
  source ${INPUT_INSTALL_DEPS}
  apt-get clean -y
fi

export GITHUB_TOKEN=${INPUT_GITHUB_TOKEN}
export SONAR_TOKEN=${INPUT_SONAR_TOKEN}

CMAKE_OPTIONS="-DCMAKE_BUILD_TYPE:STRING="
if [ "x$INPUT_CMAKE_BUILD_TYPE" == 'x' ]; then
  INPUT_CMAKE_BUILD_TYPE="Debug"
fi
CMAKE_OPTIONS+=${INPUT_CMAKE_BUILD_TYPE}

wget --quiet http://sonarcloud.io/static/cpp/build-wrapper-linux-x86.zip
unzip -qq build-wrapper-linux-x86.zip
export PATH=$PATH:`pwd`/build-wrapper-linux-x86/
wget --quiet https://binaries.sonarsource.com/Distribution/sonar-scanner-cli/sonar-scanner-cli-4.2.0.1873-linux.zip
unzip -qq sonar-scanner-cli-4.2.0.1873-linux.zip
export PATH=$PATH:`pwd`/sonar-scanner-4.2.0.1873-linux/bin/

cmake . ${CMAKE_OPTIONS}
build-wrapper-linux-x86-64 --out-dir bw-output cmake --build .
sonar-scanner

