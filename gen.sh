#!/bin/bash

day=$1
year=$(date +"%Y")
name="${year}-${day}"
exe="exe/${name}"

echo "generate files: ${exe}"

mkdir -p $exe

cat <<EOF > "${exe}/CMakeLists.txt"
include(../day.cmake)
EOF

cat <<EOF > "${exe}/main.cpp"
#include "lib.h"

using namespace std;

int main() {
    return 0;
}
EOF

touch "testdata/${name}.txt"
