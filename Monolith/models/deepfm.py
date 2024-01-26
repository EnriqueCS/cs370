import tensorflow as tf
from tensorflow.keras.layers import Dense, Embedding, Flatten, Input, Concatenate
from tensorflow.keras.models import Model

class DeepFM:
    def __init__(self, feature_sizes, embedding_size=8, hidden_layers=[64, 32, 1]):
        """
        Initialize the DeepFM model.
        :param feature_sizes: A list containing the number of unique values for each categorical feature.
        :param embedding_size: The size of the embedding vector.
        :param hidden_layers: The number of neurons in each layer of the deep part.
        """
        self.feature_sizes = feature_sizes
        self.embedding_size = embedding_size
        self.hidden_layers = hidden_layers
        self.model = self.build_model()

    def build_model(self):
        """
        Build the DeepFM model.
        """
        inputs = []
        embeddings = []

        # Factorization Machine part for modeling low-order interactions
        for feature_size in self.feature_sizes:
            input_layer = Input(shape=(1,))
            embedding_layer = Embedding(input_dim=feature_size, output_dim=self.embedding_size, input_length=1)(input_layer)
            embeddings.append(embedding_layer)
            inputs.append(input_layer)

        fm_part = Concatenate(axis=1)(embeddings)
        fm_part = Flatten()(fm_part)

        # Deep part for modeling high-order interactions
        deep_part = Dense(self.hidden_layers[0], activation='relu')(fm_part)
        for layer_size in self.hidden_layers[1:]:
            deep_part = Dense(layer_size, activation='relu')(deep_part)

        # Output layer
        output = Dense(1, activation='sigmoid')(deep_part)

        model = Model(inputs=inputs, outputs=output)
        model.compile(optimizer='adam', loss='binary_crossentropy', metrics=['accuracy'])
        return model

    def get_model(self):
        """
        Get the compiled DeepFM model.
        """
        return self.model

# Example usage
# feature_sizes = [number of unique values for each feature]
# deepfm = DeepFM(feature_sizes)
# model = deepfm.get_model()