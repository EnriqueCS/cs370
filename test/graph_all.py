import json
import subprocess
import os
import shutil

def run_make_commands_with_file_handling(input_json_path):
    # Load grouped file paths from input JSON
    with open(input_json_path, 'r') as file:
        grouped_files = json.load(file)

    # Create a directory to store results if it doesn't exist
    results_dir = './results'
    os.makedirs(results_dir, exist_ok=True)
    
    # Counter for file numbering
    file_count = 1

    # Iterate over each group of files and execute the make command
    for group_name, files in grouped_files.items():
        if len(files) >= 3:
            # Construct the make command with the first three file paths
            make_command = [
                'make',
                'run-all',
                f'FILE1={files[0]}',
                f'FILE2={files[1]}',
                f'FILE3={files[2]}'
            ]
            
            # Execute the make command
            result = subprocess.run(make_command, capture_output=True, text=True)
            
            # Print output of the make command
            print(f"Running make for group: {group_name}")
            print("Output:", result.stdout)
            print("Error:", result.stderr)

            # Move and rename the output file
            source_file = './output/file.png'
            if os.path.exists(source_file):
                dest_file = os.path.join(results_dir, f'file{file_count}.png')
                shutil.move(source_file, dest_file)
                print(f"Moved {source_file} to {dest_file}")
                file_count += 1
            else:
                print("Expected output file not found, skipping file move.")
        else:
            print(f"Skipping group {group_name} as it does not have enough files.")

# Example usage
input_json_path = 'grouped_data.json'
run_make_commands_with_file_handling(input_json_path)
