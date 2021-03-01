#!/bin/sh

if [ ! -f configure.sh ]; then
    echo "ERROR! This script only works when called from the project root."
    exit
fi

# Run cmake
mkdir -p build
cmake -G 'Unix Makefiles' -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebugInfo \
       -DWARNINGS_AS_ERRORS=FALSE -DSPDLOG_BUILD_SHARED=ON
