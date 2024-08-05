#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

#define MAXINPUTS 2
#define TOTALPARAMS 3
#define INPUTLEN 2
typedef struct _neuralnetwork
{
    UINT InputLength;
    double Weights[TOTALPARAMS];
    double Biases[TOTALPARAMS];
} NEURALNET;

class NeuralNetwork
{
private:
    double Weights[3], Biases[3];
    double WeightedSum(double *Inputs, double *Weights, double *Biases, UINT Count)
    {
        double Sum = 0;
        for (UINT i = 0; i < Count; i++)
        {
            Sum += Inputs[i] * Weights[i] + Biases[i];
        }
        return Sum;
    }
    // By the help of ChatGPT :)
    void GenerateRandoms(double *arr, int size)
    {

        // Generate random values and compute their sum
        for (int i = 0; i < size; i++)
        {
            arr[i] = (double)std::rand() / RAND_MAX; // Generate random double in [0, 1)
        }
    }
    double ReLU(double x)
    {
        return max(0, x);
    }
    double MeanSquarredError(const double *actual, const double *predicted, size_t n)
    {

        double sumSquaredErrors = 0.0;

        // Sum of squared errors
        for (size_t i = 0; i < n; ++i)
        {
            double error = predicted[i] - actual[i];
            sumSquaredErrors += error * error; // Squaring the error directly
        }

        // Mean of squared errors
        return sumSquaredErrors / n;
    }
    double DeriveReLU(double x)
    {
        return (x > 0);
    }
    double LearningRate;

public:
    NeuralNetwork()
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        LearningRate = 0.1;
        GenerateRandoms(Weights, 3);
        GenerateRandoms(Biases, 3);
        std ::cout << "Neural Network Initialized Successfully\n"
                   << std::endl;
    }
    void VisualizeNetwork()
    {
        for (int i = 0; i < 3; i++)
        {
            printf("Weight %lf Bias %lf\n", Weights[i], Biases[i]);
        }
        printf("----------------");
    }

    void train(double Inputs[4][2], double *Outputs, int Count, int Iterations)
    {
        for (int x = 0; x < Iterations; x++)
        {
            for (int i = 0; i < Count; i++)
            {
                double *Input = Inputs[i];
                double Target = Outputs[i];
                printf("X=%d Input %lf %lf -> %lf\n", x, Input[0], Input[1], Target);
                double TotalWeight = 0;

                double ForwardProp = WeightedSum(Input, Weights, Biases, 2);
                double Output = ReLU(ForwardProp);
                // double Error = MeanSquarredError(&ForwardProp, &Target, 1);
                double Error = Target - Output;
                double Gradient = Error * DeriveReLU(ForwardProp);
                for (int j = 0; j < 2; j++)
                {
                    Weights[j] -= LearningRate * Gradient * Input[j];
                }

                printf("Forward Prop %lf -> %lf (%lf Loss)\n", ForwardProp, Output, Error);

                VisualizeNetwork();
                printf("___________________");
            }
        }
    }
};

int main()
{

    NeuralNetwork Nn;
    // Simple OR
    double TrainingInputs[4][2] = {{0, 0}, {0, 1}, {1, 0}, {1, 1}};
    double TrainingOutputs[4] = {0, 1, 1, 1};
    Nn.train(TrainingInputs, TrainingOutputs, 4, 500);

    /*
    2 (2 weights) - 1 (1 weight/bias) - 1 Setup
    */

    return 0;
}