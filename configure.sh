#!/bin/sh

if [ ! -f configure.sh ]; then
    echo "ERROR! This script only works when called from the project root."
    exit
fi
# Choose build configuration
while true; do
    read -p "Specify a build configuration (Debug|Release): " Config
    case $Config in
        D*) Config='Debug'; break;;
        R*) Config='Release'; break;;
        *) echo "Please enter a valid argument.";;
    esac
done
# Export compile commands
while true; do
    read -p "Export compile commands? (Yes|No): " Ans
    case $Ans in
        Y*) Ans='YES'; break;;
        N*) Ans='NO'; break;;
        *) echo "Please answer Yes or No.";;
    esac
done
# Run cmake
mkdir -p build
cmake -G 'Unix Makefiles' -S . -B build -DCMAKE_BUILD_TYPE=${Config} \
      -DCMAKE_EXPORT_COMPILE_COMMANDS=${Ans}
