#!/bin/bash

# Directory containing this bash script
readonly DIR=$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )

readonly PREVIOUS_DIRECTORY=$(pwd)

cd $DIR/external

mv ./actor-framework-0.17.3 ./libcaf

cd ./libcaf

./configure --libs-only

cd ./build

make -j$(nproc)

cd $PREVIOUS_DIRECTORY

exit 0

