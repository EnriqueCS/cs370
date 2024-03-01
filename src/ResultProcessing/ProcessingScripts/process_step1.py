import os
import json

def process_folder(root_dir):
    """
    Process each test folder and subfolders to extract and combine JSON data.
    """
    combined_data = {}

    # Walk through the directory structure
    for root, dirs, files in os.walk(root_dir):
        for dir_name in dirs:
            test_path = os.path.join(root, dir_name)
            test_data = {}
            # Process each Test Folder
            for test_root, test_dirs, test_files in os.walk(test_path):
                for test_dir in test_dirs:
                    final_path = os.path.join(test_root, test_dir)
                    folder_data = {}
                    # Process each file in the final folders
                    for file_name in os.listdir(final_path):
                        if file_name.endswith('.json'):
                            with open(os.path.join(final_path, file_name), 'r') as f:
                                data = json.load(f)
                                folder_data[file_name.replace('.json', '')] = data
                    # Only add non-empty folder_data
                    if folder_data:
                        test_data[test_dir] = folder_data
            if test_data:  # Check if test_data is not empty before adding
                combined_data[dir_name] = test_data

    return combined_data

def save_to_json(data, file_name='../ProcessingSteps/step1_results.json'):
    """
    Save the combined data to a JSON file.
    """
    with open(file_name, 'w') as f:
        json.dump(data, f, indent=4)

if __name__ == "__main__":
    root_directory = '../../Results'  # Current directory
    combined_json_data = process_folder(root_directory)
    save_to_json(combined_json_data)
