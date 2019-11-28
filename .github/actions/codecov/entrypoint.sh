#!/bin/sh
set -ex

echo $INPUT_TOKEN
echo $INPUT_PATH

apk add curl bash

bash <(curl -s https://codecov.io/bash) -t $INPUT_TOKEN -s $INPUT_PATH

