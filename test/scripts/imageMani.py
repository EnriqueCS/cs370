import json
import matplotlib.pyplot as plt
import numpy as np
import os
from PIL import Image

def combine_images_side_by_side(file_paths, save_path):
    images = [Image.open(fp) for fp in file_paths]

    # Get the dimensions of each image
    widths, heights = zip(*(i.size for i in images))

    # Calculate the total width and height for the combined image
    total_width = sum(widths)
    max_height = max(heights)

    # Create a new blank image with the calculated dimensions
    combined_image = Image.new('RGB', (total_width, max_height))

    # Paste each image onto the combined image
    x_offset = 0
    for img in images:
        combined_image.paste(img, (x_offset, 0))
        x_offset += img.size[0]  # Increase x_offset for the next image

    # Save the combined image
    combined_image.save(save_path)

    # Close all the opened images to release resources
    for img in images:
        img.close()

    return save_path


def combine_images(file_paths, save_path):
    images = [Image.open(fp) for fp in file_paths]

    # Get the dimensions of the first image
    widths, heights = zip(*(i.size for i in images))

    # Calculate the total width and height for the combined image
    total_width = max(widths)
    total_height = sum(heights)

    # Create a new blank image with the calculated dimensions
    combined_image = Image.new('RGB', (total_width, total_height))

    # Paste each image onto the combined image
    y_offset = 0
    for img in images:
        combined_image.paste(img, (0, y_offset))
        y_offset += img.size[1]  # Increase y_offset for the next image

    # Save the combined image
    combined_image.save(save_path)

    # Close all the opened images to release resources
    for img in images:
        img.close()

    return save_path