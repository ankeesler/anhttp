#!/bin/bash

set -ex

scripts/generate-stubs.py \
    source/syscall.h \
    source/syscall_stubs.h \
    source/syscall_stubs.c
scripts/generate-stubs.py \
    source/listener.h \
    source/listener_stubs.h \
    source/listener_stubs.c
scripts/generate-stubs.py \
    source/thread.h \
    source/thread_stubs.h \
    source/thread_stubs.c
