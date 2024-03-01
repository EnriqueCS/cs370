import os
import json

def find_txt_files(start_path):
    directory_files = {}
    for root, dirs, files in os.walk(start_path):
        # Update the root path to include "Data/" prefix
        updated_root = os.path.join("Data", os.path.relpath(root, start_path))
        txt_files = [os.path.join(updated_root, file) for file in files if file.endswith('.txt')]
        if txt_files:
            # Use the updated root with "Data/" prefix as the key
            directory_files[updated_root] = txt_files
    return directory_files

def save_to_json(data, output_file):
    with open(output_file, 'w') as f:
        json.dump(data, f, indent=4)

def main():
    start_path = '.'  # Assuming the current directory is where the script is located
    output_file = './files_structure.json'
    
    txt_files = find_txt_files(start_path)
    save_to_json(txt_files, output_file)
    print(f'Done. The .txt files structure has been saved to {output_file}')

if __name__ == "__main__":
    main()