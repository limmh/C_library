#!/bin/bash

if [ ! -d "builds" ]; then
	mkdir build
fi

cmake -S . -B build
cd build
make all
cd ..
