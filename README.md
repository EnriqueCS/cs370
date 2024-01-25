# cs-370

Directory Outline:
Readings/
Syllabus/
MonolithRecommendationSystem/
│
├── data/                     # Directory for datasets and data processing scripts
│   ├── MovieLens/
│   ├── Criteo/
│   └── preprocessing/        # Scripts for data preprocessing and cleaning
│
├── models/                   # Machine learning models, including the DeepFM model
│   ├── deepfm.py
│   ├── hash_table.py         # Implementation of the collisionless hash table
│   └── utils/                # Utility scripts for model operations
│
├── training/                 # Training scripts and configurations
│   ├── batch_training.py
│   ├── online_training.py
│   └── training_utils.py     # Helper functions for training processes
│
├── serving/                  # Scripts and utilities for model serving
│   ├── server.py             # Code for the model server
│   └── client.py             # Client-side code for sending requests to the server
│
├── evaluation/               # Evaluation scripts and metrics calculations
│   ├── evaluate.py
│   └── metrics.py            # Implementation of evaluation metrics like AUC
│
├── streaming_engine/         # Components for the streaming engine
│   ├── kafka/
│   ├── flink/
│   └── online_joiner.py      # Implementation of the online joiner functionality
│
├── fault_tolerance/          # Fault tolerance mechanisms and utilities
│   └── snapshot.py           # Snapshotting and recovery processes
│
├── configs/                  # Configuration files for models, servers, etc.
│   ├── model_config.json
│   └── server_config.json
│
├── logs/                     # Log files
│
└── README.md                 # Overview and instructions for the project