@echo off
cd %~dp0
mkdir build-vs2017
cd ./build-vs2017
cmake .. -G "Visual Studio 15 2017 Win64"
cd %~dp0
