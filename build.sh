#!/bin/bash
mkdir -p build
cd build
cmake ..
make all

cd ..
mkdir -p bin
cp build/*.so bin
