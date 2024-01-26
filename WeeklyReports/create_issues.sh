#!/bin/bash

# Loop through all Markdown files in the current directory
for file in *.md; do
    # Extract the file name without the extension
    title="${file%.md} Weekly Report due"

    # Create an issue on GitHub for each file
    gh issue create --title "$title" --body "Please finalize this week's progress report, ensuring it comprehensively covers all developments, including any challenges or issues faced. Additionally, detail any project reorganization or adjustments in expectations that have occurred. This report should provide a clear and thorough overview of the week's advancements and any significant changes in the project's trajectory."
done

echo "Issues created for all Markdown files."