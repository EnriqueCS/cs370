import json
import matplotlib.pyplot as plt
import numpy as np
import os
from PIL import Image

scale = 18  # Scale factor for plot size

def plot_caches_and_save(data_title, data, save_path):
    plt.figure(figsize=(scale, scale/3))  # Adjusted figure size for 1x3 plot

    cache_levels = ["L1", "L2", "L3"]

    for idx, cache_level in enumerate(cache_levels, start=1):
        plt.subplot(1, 3, idx)

        trials = {k: v for k, v in data.items() if cache_level in k}

        for trial_type, stats in trials.items():
            keys = list(stats.keys())
            values = [stats[key] for key in keys]

            plt.plot(
                keys,
                values,
                'o-',
                label=trial_type
            )

        plt.title(f'{data_title} - {cache_level}')
        plt.ylabel('Cache Misses')
        plt.xlabel('Load Factor (%)')

        # Start axes from zero
        plt.xlim(left=0)  # Start x-axis from zero
        plt.ylim(bottom=0)  # Start y-axis from zero

        plt.grid(True)
        plt.legend()

    # Adjust left margin to add more space for labels and add space between graphs
    plt.subplots_adjust(left=0.2, wspace=0.35)  # Increased wspace for more space between subplots

    plt.savefig(save_path)
    plt.close()

    return save_path

def plot_data_and_save(data_key, data_value, save_path):
    plt.figure(figsize=(scale/3, scale/3))  # Adjusted figure size for 3x1 plot

    for idx, (trial_type, stats) in enumerate(data_value.items(), start=1):
        keys = list(stats.keys())
        means = [stats[key]['mean'] for key in keys]
        std_devs = [stats[key]['std_dev'] for key in keys]

        avg_std_dev = sum(std_devs) / len(std_devs)

        plt.errorbar(
            keys,
            means,
            yerr=std_devs,
            fmt='o-',
            label=f"{trial_type} (Avg Std Dev: {avg_std_dev:.2f})"
        )

    plt.title(f'{data_key} - Mean ± Standard Deviation')
    plt.ylabel('Time (ms)')
    plt.xlabel('Load Factor (%)')

    # Start axes from zero
    plt.xlim(left=0)  # Start x-axis from zero
    plt.ylim(bottom=0)  # Start y-axis from zero

    plt.grid(True)
    plt.legend()

    # Adjust left margin to add more space for labels
    plt.subplots_adjust(left=0.2)

    plt.savefig(save_path)
    plt.close()

    return save_path
