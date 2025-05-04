#!/bin/bash

(
mkdir -p build
cd build
cmake -B . -S ..
make
make test
)