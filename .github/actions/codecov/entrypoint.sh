#!/bin/sh
set -ex

echo $INPUT_TOKEN
echo $INPUT_PATH

apk add curl

curl
sh <(curl -s https://codecov.io/bash) -t $INPUT_TOKEN -s $INPUT_PATH

