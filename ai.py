import numpy as np

class NeuralNetwork():
    def __init__(self):
        np.random.seed(1)
        self.synaptic_weights = 2 * np.random.random((3, 1)) -1

    def sigmoid(self, x):
        return 1 / (1 + np.exp(-x))

    def sigmoid_derivative(self, x):
        return x * (1 - x)
    def think(self, inputs):
        inputs = inputs.astype(float)
        return self.sigmoid(np.dot(inputs, self.synaptic_weights))
    def train(self, ins, touts, iterations):
        for i in range(iterations):
            outs = self.think(ins)
            error = touts - outs
            self.synaptic_weights += np.dot(ins.T, error * self.sigmoid_derivative(outs))


if __name__ == '__main__':

    training_inputs = np.array([[0, 0, 1]
    , [1, 1, 1], [1, 0, 1], [0, 1, 1]
    ])
    training_outputs = np.array([[0, 1, 1, 0]]).T
    print(training_outputs)

    nn = NeuralNetwork()

    print("Rand weights ", nn.synaptic_weights)

    print("----- weights before training\n", nn.synaptic_weights)
    print("----- outs before training\n", nn.think(training_inputs))
    nn.train(training_inputs, training_outputs, 100)
    print("----- weights after training\n", nn.synaptic_weights)
    print("----- outs after training\n", nn.think(training_inputs))

    while(True):
        print("Write your data: ")
        b0 = str(input("BIT0 : "))
        b1 = str(input("BIT1 : "))
        b2 = str(input("BIT2 : "))
        print("My prediction is : ", nn.think(np.array([b0, b1, b2])))