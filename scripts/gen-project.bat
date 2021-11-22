@echo off
pushd %~dp0\..\
call cmake.exe -S . -B build -G "Visual Studio 16 2019"
popd
PAUSE
