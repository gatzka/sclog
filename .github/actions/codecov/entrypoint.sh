#!/bin/bash
set -ex

echo $INPUT_TOKEN
echo $INPUT_PATH

ls -l

find ./build/ -name *.gcda
bash <(curl -s https://codecov.io/bash) -t $INPUT_TOKEN -s $INPUT_PATH

