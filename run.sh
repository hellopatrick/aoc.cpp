#!/bin/bash

day=$1
year=${2:-$(date +"%Y")}
name="${year}-${day}"

cmake --build build --target $name

build/exe/$name/$name < testdata/$name.txt
