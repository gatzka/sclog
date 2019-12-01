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

wget --quiet https://scan.coverity.com/download/linux64 --post-data "token=${INPUT_COVERITY_TOKEN}&project=${INPUT_COVERITY_ACCOUNT}%2F${INPUT_COVERITY_PROJECT}" -O coverity_tool.tgz
tar -xf coverity_tool.tgz
cd cov-analysis-linux64*
export PATH=$PATH:`pwd`/bin
cd ..
mkdir build
cd build
cmake -GNinja .. ${CMAKE_OPTIONS}
cov-build --dir cov-int cmake --build .
tar czvf ${INPUT_COVERITY_PROJECT}.tgz cov-int
curl --form token=${INPUT_COVERITY_TOKEN} --form email=${INPUT_COVERITY_EMAIL} --form file=@${INPUT_COVERITY_PROJECT}.tgz --form version="${INPUT_COVERITY_VERSION}" --form description="${INPUT_COVERITY_DESCRIPTION}" https://scan.coverity.com/builds?project=${INPUT_COVERITY_ACCOUNT}%2F${INPUT_COVERITY_PROJECT}

