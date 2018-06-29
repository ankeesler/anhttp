#!/bin/bash

set -ex

cd build
cmake ..
make anhttp_test
./test/anhttp_test
