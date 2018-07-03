#!/bin/bash

set -ex

scripts/generate-stubs.py source/syscall.h source/syscall_stubs.h source/syscall_stubs.c
