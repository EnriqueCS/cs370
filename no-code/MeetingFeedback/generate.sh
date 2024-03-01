#!/bin/bash

# Specify the number of files to create
n=$1

# Check if the number of files to create is provided
if [ -z "$n" ]; then
  echo "Usage: $0 <number_of_files>"
  exit 1
fi

# Loop to create files
for i in $(seq 1 $n); do
  filename="MEETING_${i}.md"
  echo "Creating file: $filename"
  
  # Writing content to the file
  echo "# Meeting $i" > $filename
  echo "" >> $filename
  echo "## Agenda" >> $filename
  echo "- Item 1" >> $filename
  echo "- Item 2" >> $filename
  echo "" >> $filename
  echo "## Notes" >> $filename
  echo "" >> $filename
done

echo "Done. Created $n files."