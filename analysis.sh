#!/bin/bash

mkdir -p analysis

# static analysis
lizard src/ -V > analysis/static_analysis.log

# dynamic analysis

valgrind \
    --leak-check=full \
    --tool=memcheck \
    --show-leak-kinds=all \
    --track-origins=yes \
    --log-file=analysis/test_threadpool.txt \
    build/test_threadpool
