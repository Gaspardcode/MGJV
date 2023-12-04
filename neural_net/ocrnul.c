#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
//#include "mnist.h"
//#include "testfile.h"
#include "load_image.h"

#define INPUT 784
#define HIDDEN 30
#define OUTPUT 10


//definition of weight and bias array
double** h_weight;
double* h_bias;
double** o_weight;
double* o_bias;

double softmax_derivative(double softmax_output, double target_output) 
{
    return softmax_output * (1.0 - softmax_output);
}
double soft_max(double* outputs, double x)
{
    double sum = 0;
    for(size_t i = 0; i < 10; i++)
    {
        sum += exp(outputs[i]);
    }
    return (exp(x)/sum);
}

double* softmax(double* list)
{
    double* res = calloc(10, sizeof(double));
    double somme = 0;
    for(size_t i =0; i <10; i++)
    {
        somme+= exp(list[i]);
    }
    for(size_t j = 0; j<10; j++)
    {
        res[j] = exp(list[j])/somme;
    }
    return res;
}


double sigmoid(double x) 
{
    return 1.0 / (1.0 + exp(-x));
}

double sigmoid_prime(double x)
{
    return x * (1-x);
}

double* predict(double* inputs)
{
    double hiddens[HIDDEN];
    for(size_t i =0; i<HIDDEN;i++)
    {
        double hidden = 0;
        for(size_t j = 0; j<INPUT;j++)
            hidden+= h_weight[i][j] * inputs[j];
        hidden = sigmoid(hidden +h_bias[i]);
        hiddens[i] = hidden;
    }

    double* outputs = calloc(OUTPUT, sizeof(double));
    double output = 0;
    for(size_t i =0; i<OUTPUT;i++)
    {
        output =0;
        for(size_t j =0; j < HIDDEN; j++)
            output+= o_weight[i][j] * hiddens[j];
        //output = sigmoid(output + o_bias[i]);
        outputs[i] = output;
    }
    outputs = softmax(outputs);
    return outputs;
}


void learn(double *inputs, double targets[OUTPUT], double alpha)
{
    // Forward pass through the hidden layer
    double hiddens[HIDDEN];
    for (size_t i = 0; i < HIDDEN; i++)
    {
        double hidden = 0;
        for (size_t j = 0; j < INPUT; j++)
        {
            // Weighted sum of inputs passed through the sigmoid activation function
            hidden += h_weight[i][j] * inputs[j];
        }
        hidden = sigmoid(hidden + h_bias[i]);
        hiddens[i] = hidden;
    }

    // Forward pass through the output layer
    double* outputs = calloc(10, sizeof(double));
    for (size_t i = 0; i < OUTPUT; i++)
    {
        double output = 0;
        for (size_t j = 0; j < HIDDEN; j++)
        {
            // Weighted sum of hidden layer outputs passed through the softmax activation function
            output += o_weight[i][j] * hiddens[j];
        }
        outputs[i] = output;
    }
    outputs = softmax(outputs);

    // Compute errors between target outputs and actual outputs
    double errors[OUTPUT];
    for (size_t i = 0; i < OUTPUT; i++)
    {
        double error = targets[i] - outputs[i];
        errors[i] = error;
    }

    // Compute derivative of errors with respect to output layer outputs
    double derrors[OUTPUT];
    for (size_t i = 0; i < OUTPUT; i++)
    {
        double derror = errors[i] * sigmoid_prime(outputs[i]);
        derrors[i] = derror;
    }

    // Backward pass: Compute the contribution of each hidden layer neuron to the error
    double ds[HIDDEN];
    for (size_t i = 0; i < HIDDEN; i++)
    {
        ds[i] = 0;
    }
    for (size_t i = 0; i < OUTPUT; i++)
    {
        for (size_t j = 0; j < HIDDEN; j++)
        {
            // Accumulate contributions to the error from the output layer
            ds[j] += derrors[i] * o_weight[i][j] * sigmoid_prime(hiddens[j]);
        }
    }

    // Update weights and biases in the output layer
    for (size_t i = 0; i < OUTPUT; i++)
    {
        for (size_t j = 0; j < HIDDEN; j++)
        {
            o_weight[i][j] += alpha * hiddens[j] * derrors[i];
        }
        o_bias[i] += alpha * derrors[i];
    }

    // Update weights and biases in the hidden layer
    for (size_t i = 0; i < HIDDEN; i++)
    {
        for (size_t j = 0; j < INPUT; j++)
        {
            h_weight[i][j] += alpha * inputs[j] * ds[i];
        }
        h_bias[i] += alpha * ds[i];
    }
}


int main(int argc, char **argv)
{
}
