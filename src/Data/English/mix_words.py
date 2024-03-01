import random

def scramble_file_words_order(input_filename, output_filename):
    """Reads words from an input file, scrambles their order, and writes them to an output file."""
    try:
        # Open the input file and read the words
        with open(input_filename, 'r') as file:
            words = [line.strip() for line in file.readlines()]
        
        # Scramble the order of the words
        random.shuffle(words)
        
        # Write the scrambled words to the output file
        with open(output_filename, 'w') as file:
            for word in words:
                file.write(f"{word}\n")
                
        print(f"Words in scrambled order written to {output_filename}")
    except Exception as e:
        print(f"An error occurred: {e}")

# Example usage
input_filename = 'words.txt'
output_filename = 'mixed_words3.txt'

# Call the function with your specific file paths
scramble_file_words_order(input_filename, output_filename)