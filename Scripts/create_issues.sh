#!/bin/bash

# Check if the 'gh' command-line tool is installed
if ! command -v gh &> /dev/null; then
    echo "Error: 'gh' command-line tool not found. Please install GitHub CLI (https://cli.github.com/) and authenticate with your GitHub account."
    exit 1
fi

# Check if a directory path is provided as an argument
if [ $# -eq 0 ]; then
    echo "Usage: $0 <directory>"
    exit 1
fi

# Get the directory path from the command-line argument
directory="$1"

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "Error: Directory '$directory' not found."
    exit 1
fi

# Loop through all files in the directory
for file in "$directory"/*; do
    # Check if the file is a regular file (not a directory)
    if [ -f "$file" ]; then
        # Extract the filename without the path
        filename=$(basename "$file")
        
        # Create a GitHub issue for the file
        issue_title="Implementation of $filename"
        
        # Use the 'gh' command to create the issue (you might need to add authentication)
        gh issue create --title "$issue_title" --body "Implement the functionality described in $filename"
        
        echo "Created GitHub issue: $issue_title"
    fi
done

echo "GitHub issues created for all files in the directory."