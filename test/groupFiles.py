import json
from collections import defaultdict
from os.path import basename

def group_files_by_name(input_json_path, output_json_path):
    # Load file paths from input JSON
    with open(input_json_path, 'r') as file:
        file_paths = json.load(file)
    
    # Create a dictionary to hold grouped paths
    grouped_files = defaultdict(list)
    
    # Group file paths by their base filename
    for path in file_paths:
        filename = basename(path)
        grouped_files[filename].append(path)
    
    # Convert defaultdict to regular dict for JSON compatibility
    grouped_files = dict(grouped_files)
    
    # Write grouped paths to output JSON
    with open(output_json_path, 'w') as file:
        json.dump(grouped_files, file, indent=4)

# Example usage
input_json_path = 'leaf_txt_files.json'
output_json_path = 'grouped_data.json'
group_files_by_name(input_json_path, output_json_path)
