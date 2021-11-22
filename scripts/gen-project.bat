@echo off
pushd %~dp0\..\
mkdir build
call cmake.exe /S . /B 'build' /G 'Visual Studio 2019 Win64'
popd
PAUSE
