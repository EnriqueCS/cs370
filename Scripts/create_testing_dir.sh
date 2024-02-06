#!/bin/bash

# Check if a directory path is provided as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Get the directory path from the command-line argument
directory="$1"

# Check if the directory exists; if not, create it
if [ ! -d "$directory" ]; then
    mkdir -p "$directory"
fi

# Define directory names
dirs=("Random Data" "Ordered Data" "Repeating Data" "Real-World Data")

# Create the four directories
for dir_name in "${dirs[@]}"; do
    # Check if the directory exists; if not, create it
    if [ ! -d "$directory/$dir_name" ]; then
        mkdir -p "$directory/$dir_name"
    fi
    
    # Create 5 JSON files in each directory
    for j in {1..5}; do
        file_name="${dir_name// /_}_${j}.json"
        touch "$directory/$dir_name/$file_name"
        echo "Created $directory/$dir_name/$file_name"
    done
done

echo "Directories and files created successfully in $directory."