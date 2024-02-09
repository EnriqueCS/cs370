#!/bin/bash

# Navigate to the Executables directory
cd Executables

# Check if the navigation was successful
if [ $? -eq 0 ]; then
    echo "Running ChainingTest..."
    ./ChainingTest
    echo "ChainingTest completed."

    echo "Running CuckooHashingTest..."
    ./CuckooHashingTest
    echo "CuckooHashingTest completed."

    echo "Running OpenAddressingTest..."
    ./OpenAddressingTest
    echo "OpenAddressingTest completed."
else
    echo "The Executables directory does not exist in the current path."
fi

# Navigate back to the original directory
cd ..