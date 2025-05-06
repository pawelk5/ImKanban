#!/bin/bash

# Function to build and test
build_and_test() {
    mkdir -p build
    cd build
    cmake -B . -S ..
    make  
    make test
    cd ..
}

# Watch for changes and rebuild
while true; do
    build_and_test
    inotifywait -e modify,create,delete -r .
done