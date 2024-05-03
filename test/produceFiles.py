import os
import json

def find_leaf_txt_files(dir_path):
    leaf_files = []
    for root, dirs, files in os.walk(dir_path):
        # Check if the directory has no subdirectories
        if not dirs:
            # Add all .txt files from this directory to the list
            leaf_files.extend(os.path.join(root, file) for file in files if file.endswith('.txt'))
    return leaf_files

def main():
    directory_to_search = '../src/Papi_Results'  # Replace with your directory path
    leaf_txt_files = find_leaf_txt_files(directory_to_search)

    # Save the list to a JSON file
    json_filename = './leaf_txt_files.json'
    with open(json_filename, 'w') as f:
        json.dump(leaf_txt_files, f, indent=4)
    
    print(f"Leaf .txt files have been written to {json_filename}")

if __name__ == "__main__":
    main()
