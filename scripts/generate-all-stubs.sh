#!/bin/bash

set -ex

scripts/generate-stubs.py source/syscall.c
scripts/generate-stubs.py source/log.c
