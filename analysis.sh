#!/bin/bash

mkdir -p analysis

# static analysis
lizard src/ -V > analysis/static_analysis.log

# dynamic analysis
for testable in build/test_*
do
    valgrind \
        --leak-check=full \
        --tool=memcheck \
        --show-leak-kinds=all \
        --track-origins=yes \
        --log-file=${testable}.txt \
        ${testable}
done
