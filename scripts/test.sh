#!/bin/bash

set -ex

cmake .
make anhttp_test
./test/anhttp_test
