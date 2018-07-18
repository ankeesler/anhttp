#!/bin/bash

set -e

BUILDIFIER=buildifier

which buildifier 1>&2 > /dev/null
if [[ $? -ne 1 ]]; then
    go get github.com/bazelbuild/buildtools/buildifier
    BUILDIFIER=$GOPATH/bin/buildifier
fi

buildifier $(find . -name "BUILD*")
