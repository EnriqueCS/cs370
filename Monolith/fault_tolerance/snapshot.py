import os
import datetime
import pickle
# Other necessary imports

class Snapshot:
    def __init__(self, model, parameter_server, snapshot_dir="snapshots"):
        """
        Initialize the Snapshot object.
        :param model: The model object to be snapshotted.
        :param parameter_server: The parameter server object containing the model parameters.
        :param snapshot_dir: Directory where snapshots are stored.
        """
        self.model = model
        self.parameter_server = parameter_server
        self.snapshot_dir = snapshot_dir
        if not os.path.exists(snapshot_dir):
            os.makedirs(snapshot_dir)

    def create_snapshot(self):
        """
        Create a snapshot of the current state of the model and parameter server.
        """
        timestamp = datetime.datetime.now().strftime("%Y%m%d%H%M%S")
        snapshot_data = {
            "model": self.model,
            "parameters": self.parameter_server.get_parameters()
        }
        snapshot_file = os.path.join(self.snapshot_dir, f"snapshot_{timestamp}.pkl")

        with open(snapshot_file, 'wb') as file:
            pickle.dump(snapshot_data, file)
        
        print(f"Snapshot created at {snapshot_file}")

    def load_snapshot(self, snapshot_file):
        """
        Load a snapshot from the specified file.
        :param snapshot_file: Path to the snapshot file.
        """
        with open(snapshot_file, 'rb') as file:
            snapshot_data = pickle.load(file)
        
        self.model = snapshot_data["model"]
        self.parameter_server.set_parameters(snapshot_data["parameters"])

        print(f"Snapshot loaded from {snapshot_file}")

# Example Usage
if __name__ == "__main__":
    # Assume model and parameter_server are already defined
    snapshot = Snapshot(model, parameter_server)
    snapshot.create_snapshot()
    # To load a snapshot
    # snapshot.load_snapshot('path_to_snapshot_file')