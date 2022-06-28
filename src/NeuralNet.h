//
// Created by alex on 28/06/2022.
//

#include <iostream>
#include "Image.h"

#pragma once

class NeuralNet {
public:
    NeuralNet();
    NeuralNet(int input, int hidden, int output);
private:
    int input;
    int hidden;
    int output;
    Matrix hidden_weights;
    Matrix output_weights;
};

NeuralNet::NeuralNet(int input, int hidden, int output) {
    this->input = input;
    this->hidden = hidden;
    this->output = output;
    hidden_weights = Matrix(hidden, input);
    output_weights = Matrix(output, hidden);
    hidden_weights.randomise();
    output_weights.randomise();
}