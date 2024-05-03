import json
import matplotlib.pyplot as plt
import numpy as np
import os
from plotFunctions import plot_data_and_save, plot_caches_and_save
from imageMani import combine_images, combine_images_side_by_side

def load_data(file_path):
    with open(file_path, 'r') as file:
        return json.load(file)

# Define the function
def reduce_data(data):
    # Data structure to store the results
    reduced_data = {}

    # Group trials by their base name (e.g., 'Chaining', 'Cuckoo', 'OpenAddressing')
    grouped_trials = {}

    # Separate data by trial type
    for trial_name, values in data.items():
        trial_base_name = trial_name.split(' ')[-1]  # Get base name (e.g., 'Chaining', 'Cuckoo', 'OpenAddressing')
        if trial_base_name not in grouped_trials:
            grouped_trials[trial_base_name] = []
        grouped_trials[trial_base_name].append(values)

    # Calculate average and standard deviation for each trial type and each key (25.0, 50.0, 75.0)
    for trial_type, trials in grouped_trials.items():
        # Create a dictionary to store the calculated values
        avg_sd_dict = {}
        # Get all unique keys across trials
        all_keys = set(key for trial in trials for key in trial.keys())

        # Calculate mean and standard deviation for each key
        for key in all_keys:
            values = [trial[key] for trial in trials]
            mean_value = np.mean(values)  # Calculate mean
            std_dev_value = np.std(values)  # Calculate standard deviation
            avg_sd_dict[key] = {'mean': mean_value, 'std_dev': std_dev_value}

        # Store the result in the reduced data dictionary
        reduced_data[trial_type] = avg_sd_dict

    return reduced_data

# File paths and algorithm names
colors = ['#1f77b4', '#2ca02c', '#d62728', '#aec7e8', '#98df8a', '#ff9896', '#c6dbef', '#c7e9c0', '#ffbdbd']

file_paths = ['./p_input/output1.json', './p_input/output2.json', './p_input/output3.json']
algo_names = ['Chaining', 'Cuckoo', 'OpenAddressing']

# Initialize dictionaries to store the plotting data
insert_data = {}
search_data = {}
remove_data = {}
insert_timing = {}
search_timing = {}
remove_timing = {}

# Load and process each file
for index, file_path in enumerate(file_paths):
    data = load_data(file_path)
    # Assume there is always one top-level key and we don't care what it is
    parent_key = next(iter(data))  # This gets the first key in the dictionary

    # Now, process the nested dictionary under that key
    nested_dict = data[parent_key]
    for level_key, cache_data in nested_dict.items():
        level = level_key.split()[1]
        algorithm_label = f'L{level} {algo_names[index]}'
        algorithm_run = f'Trial #{level} {algo_names[index]}'

        if algorithm_label not in insert_data:
            insert_data[algorithm_label] = {}
            search_data[algorithm_label] = {}
            remove_data[algorithm_label] = {}
            insert_timing[algorithm_run] = {}
            search_timing[algorithm_run] = {}
            remove_timing[algorithm_run] = {}

        metrics = cache_data.get("Metrics", {})
        timing = cache_data.get("Timing", {})
        
        # Process each set of metrics and timing data
        for metric_key, metric_value in metrics.items():
            if "Load Factor" in metric_key:
                load_factor = float(metric_key.split()[2].replace('%', ''))
                if "Insert Metric" in metric_value:
                    insert_data[algorithm_label][load_factor] = metric_value["Insert Metric"]
                    insert_timing[algorithm_run][load_factor] = timing.get(metric_key, {}).get("Insert Metric", 0)
                if "Search Metric" in metric_value:
                    search_data[algorithm_label][load_factor] = metric_value["Search Metric"]
                    search_timing[algorithm_run][load_factor] = timing.get(metric_key, {}).get("Search Metric", 0)
                if "Remove Metric" in metric_value:
                    remove_data[algorithm_label][load_factor] = metric_value["Remove Metric"]
                    remove_timing[algorithm_run][load_factor] = timing.get(metric_key, {}).get("Remove Metric", 0)

# Data structure to store the results
search_timing_reduced = reduce_data(search_timing)
insert_timing_reduced = reduce_data(insert_timing)
remove_timing_reduced = reduce_data(remove_timing)

# Define a dictionary of all reduced data
data_sets = {
    'Search Timing': search_timing_reduced,
    'Insert Timing': insert_timing_reduced,
    'Remove Timing': remove_timing_reduced,
}

# print(search_timing_reduced)
# print()
# print(insert_data)

# Create and save the 3x3 plot
plot_caches_and_save("Insert", insert_data, "./temp/row1.png")
plot_caches_and_save("Search", search_data, "./temp/row2.png")
combine_images(["./temp/row1.png", "./temp/row2.png"], './temp/row1.png')
plot_caches_and_save("Delete", remove_data, "./temp/row2.png")
combine_images(["./temp/row1.png", "./temp/row2.png"], './temp/caches.png')

# Create and save the 3x1 plot
plot_data_and_save("Insert", insert_timing_reduced, "./temp/row1.png")
plot_data_and_save("Search", search_timing_reduced, "./temp/row2.png")
combine_images(["./temp/row1.png", "./temp/row2.png"], './temp/row1.png')
plot_data_and_save("Delete", remove_timing_reduced, "./temp/row2.png")
combine_images(["./temp/row1.png", "./temp/row2.png"], './temp/timing.png')

# Create and save the 3x4 plot
combine_images_side_by_side(["./temp/caches.png", "./temp/timing.png"], './output/file.png')