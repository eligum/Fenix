#!/bin/sh

if [ ! -f configure.sh ]; then
    echo "ERROR! This script only works when called from the project root."
    exit
fi

# Create nested build-dir and run cmake
mkdir -p build
cmake -G 'Unix Makefiles' -S . -B build -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DWARNINGS_AS_ERRORS=FALSE -DHAZEL_BUILD_SHARED=OFF || exit 1

# Ask if the user wants to compile now
echo "---------------------------------------------------"
while true; do
    read -p "Do you want to compile this project now? (Yes|No): " Ans
    case $Ans in
        Y*|y*) Ans='YES'; break;;
        N*|n*) Ans='NO'; break;;
        *) echo "Please answer Yes or No.";;
    esac
done
echo "You answered ${Ans}."
if [ $Ans = 'YES' ]; then
    cmake --build build --target all -j
fi
