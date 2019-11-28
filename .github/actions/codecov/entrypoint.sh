#!/bin/bash
set -ex

echo $INPUT_TOKEN
echo $INPUT_PATH

find . -name *.gcda
bash <(curl -s https://codecov.io/bash) -t $INPUT_TOKEN -s $INPUT_PATH

