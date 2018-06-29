#!/bin/bash

set -ex

cd build
cmake ..
make server_test
./test/server_test
