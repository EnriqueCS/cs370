import re
import json

def parse_metrics(data):
    results = {}
    current_level = None
    file_title = None

    # Regular expression patterns to capture relevant data
    file_pattern = re.compile(r"File: (.+)")
    level_pattern = re.compile(r"Level (\d+) cache misses")
    total_strings_pattern = re.compile(r"Total Strings: (\d+)")
    metric_pattern = re.compile(r"([a-zA-Z ]+ \(Table is [a-zA-Z]+\)): (\d+) units")
    search_empty_pattern = re.compile(r"Search Metric \(Table is Empty\): (\d+) units")
    load_factor_pattern = re.compile(r"Load Factor (\d+\.\d+)% - ([a-zA-Z ]+): (\d+) units")
    load_factor_timing_pattern = re.compile(r"Load Factor (\d+\.\d+)% - ([a-zA-Z ]+): (\d+) ms")  # Pattern for timing data under load factors

    lines = data.split('\n')
    for line in lines:
        # Check for file title
        file_match = file_pattern.search(line)
        if file_match:
            file_title = file_match.group(1)
            results[file_title] = {}
            continue

        # Check for level
        level_match = level_pattern.search(line)
        if level_match:
            current_level = f"Level {level_match.group(1)} cache misses"
            results[file_title][current_level] = {'Total Strings': 0, 'Metrics': {}, 'Timing': {}}
            continue

        # Check for total strings
        total_strings_match = total_strings_pattern.search(line)
        if total_strings_match:
            results[file_title][current_level]['Total Strings'] = int(total_strings_match.group(1))
            continue

        # Check for general metrics
        metric_match = metric_pattern.search(line)
        if metric_match:
            results[file_title][current_level]['Metrics'][metric_match.group(1)] = int(metric_match.group(2))
            continue

        # Check for search empty metric
        search_empty_match = search_empty_pattern.search(line)
        if search_empty_match:
            results[file_title][current_level]['Metrics']['Search Metric (Table is Empty)'] = int(search_empty_match.group(1))
            continue

        # Check for load factor metrics
        load_factor_match = load_factor_pattern.search(line)
        if load_factor_match:
            load_factor_key = f"Load Factor {load_factor_match.group(1)}%"
            if load_factor_key not in results[file_title][current_level]['Metrics']:
                results[file_title][current_level]['Metrics'][load_factor_key] = {}
            results[file_title][current_level]['Metrics'][load_factor_key][load_factor_match.group(2).strip()] = int(load_factor_match.group(3))
            continue

        # Check for timing data under load factors
        load_factor_timing_match = load_factor_timing_pattern.search(line)
        if load_factor_timing_match:
            load_factor_key = f"Load Factor {load_factor_timing_match.group(1)}%"
            timing_key = load_factor_timing_match.group(2).strip()
            if load_factor_key not in results[file_title][current_level]['Timing']:
                results[file_title][current_level]['Timing'][load_factor_key] = {}
            results[file_title][current_level]['Timing'][load_factor_key][timing_key] = int(load_factor_timing_match.group(3))
            continue

    return results

def read_and_parse_file(filepath):
    with open(filepath, 'r') as file:
        data = file.read()
    return parse_metrics(data)

def write_json(data, output_filepath):
    with open(output_filepath, 'w') as file:
        json.dump(data, file, indent=4)

# Example usage
filepath = './temp/test.txt'  # Set your file path here
output_filepath = './temp/output.json'  # Set your output JSON file path here
parsed_data = read_and_parse_file(filepath)
write_json(parsed_data, output_filepath)
