import json

def flatten_json_structure(input_json):
    """
    Adjust the JSON structure so that algorithms are top-level keys, and the combined first and second nesting levels
    become the second-level keys with their details as nested data.
    """
    flattened_data = {}
    # Navigate through the nested JSON structure
    for first_level_name, first_level_data in input_json.items():
        for second_level_name, algorithms in first_level_data.items():
            # Combine first and second level names
            combined_name = f"{first_level_name}_{second_level_name}"
            for algorithm_name, details in algorithms.items():
                # Ensure algorithm_name key exists
                if algorithm_name not in flattened_data:
                    flattened_data[algorithm_name] = {}
                # Assign details to the combined name within the algorithm
                flattened_data[algorithm_name][combined_name] = details
    return flattened_data

def process_and_save_json(input_filename, output_filename):
    """
    Read the input JSON, adjust the structure as described, and save the result to a new file.
    """
    with open(input_filename, 'r') as file:
        data = json.load(file)
        adjusted_data = flatten_json_structure(data)
    
    with open(output_filename, 'w') as file:
        json.dump(adjusted_data, file, indent=4)

if __name__ == "__main__":
    input_filename = 'step1_results.json'  # Update this with the path to your input file
    output_filename = 'step2_results.json'  # Desired path for the output file
    process_and_save_json(input_filename, output_filename)
