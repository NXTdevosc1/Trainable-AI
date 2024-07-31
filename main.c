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
double TrainingVals[] = {0, 0, 1, /**/ 0, 1, 0, /**/ 1, 0, 1, /**/ 1, 1, 0};

double Weights[] = {0.25, 0.15, 0.53};
double Outputs[] = {0, 0, 1, 1}; // last unusable

double sigmoid_derivative(double x)
{
    return x * (1 - x);
}

void printarr(double *arr, UINT Count)
{
    for (int i = 0; i < Count; i++)
    {
        printf("    %lf\n", arr[i]);
    }
}

double Think(double *Inputs)
{
    double Result = 0;
    for (int c = 0; c < 2; c++)
        Result += Inputs[c] * Weights[c];

    return Sigmoid(Result);
}

#define LEARNING_RATE 0.5

double SumArr(double *arr, UINT Count)
{
    double ret = 0;
    for (int i = 0; i < Count; i++)
        ret += arr[i];
    return ret;
}

void Train(double *Inputs, UINT InputLength, UINT MatrixCount, UINT Iterations)
{

    for (int i = 0; i < Iterations * MatrixCount; i++)
    {
        double *in = Inputs + ((i % MatrixCount) * InputLength);
        double Out = Outputs[i % MatrixCount];

        double Result = Think(in);

        double Error = Out - Result;

        double deriv = Error * sigmoid_derivative(Result);
        double arr[10];
        for (int c = 0; c < InputLength; c++)
        {
            arr[c] = in[c];
        }
        double arr2[10];
        for (int c = 0; c < InputLength; c++)
        {
            arr2[c] = arr[c] * SumArr(arr, InputLength);
        }

        for (int c = 0; c < InputLength; c++)
        {
            Weights[c] += arr2[c] * deriv;
        }

        // printf("IN %lf %lf %lf Result %lf Out %lf Error %lf Deriv %lf\n", in[0], in[1], in[2], Result, Out, Error, sigmoid_derivative(Result));
        // printf("New Weights :\n");
        // printarr(Weights, InputLength);
    }
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    printf("Machine Learning AI Startup\n");

    // for (int i = 0; i < 2; i++)
    // {
    //     // Weights[i] = RandVal();
    //     printf("Weight%d %lf Out %lf\n", i, Weights[i], Outputs[i]);
    // }

    double Input[3] = {1, 1, 0};
    double Input2[3] = {0, 1, 0};

    Train(TrainingVals, 3, 4, 0x10000);
    double val[3];

    printf("New Weights :\n");
    printarr(Weights, 3);

    printf("Result for after training : %lf\n", Think(Input));
    printf("Result for after training : %lf\n", Think(Input2));
    for (;;)
    {
        printf("Type your number :\n");
        printf("BIT0 : ");
        val[0] = fgetc(stdin) - '0';
        printf("BIT1 : ");
        fputc(0, stdin);
        val[1] = fgetc(stdin) - '0';
        fputc(0, stdin);

        printf("BIT2 : ");
        val[2] = fgetc(stdin) - '0';
        printf("Val %lf %lf %lf --- Prediction Result : %lf\n", val[0], val[1], val[2], Think(val));
        fputc(0, stdin);
    }

    return 0;
}