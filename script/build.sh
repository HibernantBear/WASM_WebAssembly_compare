#!/bin/bash
rm -rf output/$1
mkdir output/$1
emcc src/$1.c -O3 -s WASM=1 -s ALLOW_MEMORY_GROWTH=1 -s EXPORTED_FUNCTIONS='["_main","_test","_lorenz_attractor"]' -o output/$1/$1.$2