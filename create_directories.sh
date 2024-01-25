#!/bin/bash

# Define the root directory
ROOT_DIR="MonolithRecommendationSystem"

# Define subdirectories
SUBDIRS=(
    "data/MovieLens"
    "data/Criteo"
    "data/preprocessing"
    "models"
    "models/utils"
    "training"
    "training/training_utils"
    "serving"
    "evaluation"
    "streaming_engine/kafka"
    "streaming_engine/flink"
    "fault_tolerance"
    "configs"
    "logs"
)

# Create the root directory
mkdir -p $ROOT_DIR

# Create each subdirectory
for dir in "${SUBDIRS[@]}"; do
    mkdir -p "$ROOT_DIR/$dir"
done

# Create README.md file in the root directory
touch "$ROOT_DIR/README.md"

# Feedback
echo "Directory structure for Monolith Real Time Recommendation System has been created."