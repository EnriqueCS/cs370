import os
import random
import string

# Function to generate a random string
def random_string(length=4):
    return ''.join(random.choices(string.ascii_letters + string.digits, k=length))

# Function to ensure the target folder exists
def ensure_folder_exists(folder):
    if not os.path.exists(folder):
        os.makedirs(folder)

# Function to generate unique random strings and write them into a single .txt file
def generate_unique_strings(num_strings, output_file):
    unique_strings = set()  # Use a set to ensure uniqueness
    while len(unique_strings) < num_strings:
        unique_strings.add(random_string())
    # Write unique strings to the specified .txt file
    with open(output_file, 'w') as f:
        for s in unique_strings:
            f.write(s + '\n')  # Write each unique string on a new line

# Function to generate non-unique random strings and write them into a single .txt file
def generate_non_unique_strings(num_strings, output_file):
    # Write random strings to the specified .txt file
    with open(output_file, 'w') as f:
        for _ in range(num_strings):
            f.write(random_string() + '\n')  # Write each string on a new line

# Ensure the folder exists
ensure_folder_exists('./pyGenStrings')

# Generate unique random strings and write them to a single .txt file
generate_unique_strings(2000000, './pyGenStrings/unique_strings.txt')

# Generate non-unique random strings and write them to a single .txt file
generate_non_unique_strings(2000000, './pyGenStrings/non_unique_strings.txt')