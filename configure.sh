#!/bin/sh

if [ ! -f configure.sh ]; then
    echo "ERROR! This script only works when called from the project root."
    exit
fi

# Create nested build-dir and run cmake
mkdir -p build
cmake -G 'Unix Makefiles' -S . -B build -DCMAKE_BUILD_TYPE=Debug \
      -DWARNINGS_AS_ERRORS=FALSE -DSPDLOG_BUILD_SHARED=OFF
