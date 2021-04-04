#!/bin/sh
cd `dirname $0`
mkdir build-xcode
cd ./build-xcode
cmake .. -G Xcode
open ./clover.xcodeproj
