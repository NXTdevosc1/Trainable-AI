#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <math.h>
#include <time.h>

double Sigmoid(double Val)
{
    return 1 / (1 + exp(-Val));
}

#define RandVal() ((double)rand() / (double)RAND_MAX)

// Training values
BOOLEAN tInput0[] = {0, 0, 1};
BOOLEAN tInput[] = {1, 0, 0};
BOOLEAN tInput2[] = {0, 1, 1};
BOOLEAN tInput3[] = {1, 0, 1};

double Weights[3] = {0};
double Outputs[] = {0, 1, 999}; // last unusable

void Train(BOOLEAN *Inputs, BOOLEAN Val, UINT Iterations)
{
    double Out = Outputs[Val];

    for (int i = 0; i < Iterations; i++)
    {
        double Result = 0;
        for (int i = 0; i < 3; i++)
            Result += Inputs[i] * Weights[i];

        Result = Sigmoid(Result);
        double Error = Result - Out;
        printf("Result %lf Out %lf Error %lf\n", Result, Out, Error);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    printf("Machine Learning AI Startup\n");

    for (int i = 0; i < 3; i++)
    {
        Weights[i] = RandVal();
        Outputs[i] = Sigmoid(Outputs[i]);
        printf("Weight%d %lf Out %lf\n", i, Weights[i], Outputs[i]);
    }

    BOOLEAN Input[3] = {1, 1, 0};

    Train(Input, 1, 10);

    double NeuronOut = 0;

    for (int i = 0; i < 3; i++)
    {
        NeuronOut += Input[i] * Weights[i];
    }
    printf("Neuron Out %lf Sigmoid %lf\n", NeuronOut, Sigmoid(NeuronOut));

    return 0;
}