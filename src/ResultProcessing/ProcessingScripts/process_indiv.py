import json

def split_json_into_files(input_filename):
    """
    Reads the input JSON file, splits its content based on the top-level keys (algorithms),
    and saves each section into separate files named after the algorithm.
    """
    with open(input_filename, 'r') as file:
        data = json.load(file)

    # Iterate through each top-level key (algorithm name) and save its data to a separate file
    for algorithm_name, details in data.items():
        output_filename = f"../IndividualProcessing/{algorithm_name}/{algorithm_name}.json"
        with open(output_filename, 'w') as outfile:
            json.dump(details, outfile, indent=4)
            print(f"Saved {algorithm_name}'s data to {output_filename}")

if __name__ == "__main__":
    input_filename = '../ProcessingSteps/step2_results.json'  # Update this to your input file's name
    split_json_into_files(input_filename)
