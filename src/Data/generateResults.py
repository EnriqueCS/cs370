import os

def create_directories_for_txt_files(start_path):
    for root, dirs, files in os.walk(start_path):
        for file in files:
            if file.endswith('.txt'):
                # Extract the subfolder path relative to the start_path
                relative_subfolder_path = os.path.relpath(root, start_path)
                # Construct the new directory path based on the file name (without the .txt extension)
                new_dir_path = os.path.join('..', 'Results', relative_subfolder_path, os.path.splitext(file)[0])
                # Create the directory, including intermediate directories
                os.makedirs(new_dir_path, exist_ok=True)
                print(f"Created directory: {new_dir_path}")

def main():
    current_directory = '.'  # Use the current directory
    create_directories_for_txt_files(current_directory)
    print("Done creating directories based on .txt files in subfolders.")

if __name__ == "__main__":
    main()