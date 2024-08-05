import numpy as np
import tensorflow as tf

# Load MNIST dataset using TensorFlow
def load_mnist_data():
    (train_images, train_labels), (test_images, test_labels) = tf.keras.datasets.mnist.load_data()

    # Normalize images
    train_images = train_images / 255.0
    test_images = test_images / 255.0

    # Flatten images
    train_images = train_images.reshape(-1, 28 * 28)
    test_images = test_images.reshape(-1, 28 * 28)

    # Convert labels to one-hot encoding
    train_labels = np.eye(10)[train_labels]
    test_labels = np.eye(10)[test_labels]

    return train_images, train_labels, test_images, test_labels

# Activation functions
def sigmoid(x):
    return 1 / (1 + np.exp(-x))

def sigmoid_derivative(x):
    return x * (1 - x)

def softmax(x):
    e_x = np.exp(x - np.max(x, axis=1, keepdims=True))
    return e_x / np.sum(e_x, axis=1, keepdims=True)

# Initialize weights and biases
def initialize_parameters(input_size, hidden_size, output_size):
    np.random.seed(42)  # For reproducibility
    W1 = np.random.randn(input_size, hidden_size) * 0.01
    b1 = np.zeros((1, hidden_size))
    W2 = np.random.randn(hidden_size, output_size) * 0.01
    b2 = np.zeros((1, output_size))
    return W1, b1, W2, b2

# Forward pass
def forward_pass(X, W1, b1, W2, b2):
    Z1 = np.dot(X, W1) + b1
    A1 = sigmoid(Z1)
    Z2 = np.dot(A1, W2) + b2
    A2 = softmax(Z2)
    return A1, A2

# Compute loss
def compute_loss(Y, A2):
    m = Y.shape[0]
    loss = -np.sum(Y * np.log(A2 + 1e-10)) / m
    return loss

# Backward pass
def backward_pass(X, Y, A1, A2, W2):
    m = X.shape[0]
    dZ2 = A2 - Y
    dW2 = np.dot(A1.T, dZ2) / m
    db2 = np.sum(dZ2, axis=0, keepdims=True) / m
    dA1 = np.dot(dZ2, W2.T)
    dZ1 = dA1 * sigmoid_derivative(A1)
    dW1 = np.dot(X.T, dZ1) / m
    db1 = np.sum(dZ1, axis=0, keepdims=True) / m
    return dW1, db1, dW2, db2

# Update weights and biases
def update_parameters(W1, b1, W2, b2, dW1, db1, dW2, db2, learning_rate):
    W1 -= learning_rate * dW1
    b1 -= learning_rate * db1
    W2 -= learning_rate * dW2
    b2 -= learning_rate * db2
    return W1, b1, W2, b2

# Training the neural network
def train(X_train, Y_train, X_test, Y_test, hidden_size, epochs, learning_rate):
    input_size = X_train.shape[1]
    output_size = Y_train.shape[1]
    
    W1, b1, W2, b2 = initialize_parameters(input_size, hidden_size, output_size)
    
    for epoch in range(epochs):
        A1, A2 = forward_pass(X_train, W1, b1, W2, b2)
        loss = compute_loss(Y_train, A2)
        dW1, db1, dW2, db2 = backward_pass(X_train, Y_train, A1, A2, W2)
        W1, b1, W2, b2 = update_parameters(W1, b1, W2, b2, dW1, db1, dW2, db2, learning_rate)
        
        if epoch % 10 == 0:
            print(f'Epoch {epoch}: Loss {loss}')
    
    # Evaluate on test set
    _, test_predictions = forward_pass(X_test, W1, b1, W2, b2)
    test_labels_pred = np.argmax(test_predictions, axis=1)
    test_labels_true = np.argmax(Y_test, axis=1)
    accuracy = np.mean(test_labels_pred == test_labels_true)
    print(f'Test Accuracy: {accuracy * 100:.2f}%')

# Main function
def main():
    X_train, Y_train, X_test, Y_test = load_mnist_data()
    hidden_size = 128
    epochs = 100
    learning_rate = 0.01
    
    train(X_train, Y_train, X_test, Y_test, hidden_size, epochs, learning_rate)

if __name__ == '__main__':
    main()
