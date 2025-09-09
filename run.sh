#!/bin/bash

cd "$(dirname "$0")"


g++ -std=c++17 -Wall -Wextra Main_Code.cpp -o main

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    ./main
else
    echo "Compilation failed."
fi

