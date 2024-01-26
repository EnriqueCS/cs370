class OnlineJoiner:
    def __init__(self, feature_stream, action_stream, output_stream):
        """
        Initialize the online joiner.
        :param feature_stream: Stream of feature data.
        :param action_stream: Stream of user action data.
        :param output_stream: Output stream for joined data.
        """
        self.feature_stream = feature_stream
        self.action_stream = action_stream
        self.output_stream = output_stream

    def join_streams(self):
        """
        Join feature and action streams.
        """
        while True:
            # Implement logic to read from feature_stream and action_stream
            # ...

            # Join the data based on a common key (e.g., user ID)
            joined_data = self._join_data(feature_data, action_data)

            # Write joined data to output_stream
            self._write_to_output_stream(joined_data)

    def _join_data(self, feature_data, action_data):
        """
        Private method to join feature data with action data.
        :param feature_data: Data from the feature stream.
        :param action_data: Data from the action stream.
        :return: Joined data.
        """
        # Implement the joining logic based on your system's requirements
        # ...

    def _write_to_output_stream(self, data):
        """
        Private method to write joined data to the output stream.
        :param data: The data to be written.
        """
        # Implement the logic to write data to output_stream
        # ...

# Example usage
# Initialize streams (feature_stream, action_stream, output_stream)
# online_joiner = OnlineJoiner(feature_stream, action_stream, output_stream)
# online_joiner.join_streams()