#!/bin/bash

set -ex

cd build
cmake ..

TESTS="server_test list_test"
for t in $TESTS; do
    make $t
    ./test/$t
done
