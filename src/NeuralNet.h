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

    void train(Image* images , int n);

private:
    int input;
    int hidden;
    int output;
    Matrix hidden_weights;
    Matrix output_weights;
};

NeuralNet::NeuralNet() {
    this->input = 0;
    this->hidden = 0;
    this->output = 0;
    hidden_weights = Matrix();
    output_weights = Matrix();
}

NeuralNet::NeuralNet(int input, int hidden, int output) {
    this->input = input;
    this->hidden = hidden;
    this->output = output;
    hidden_weights = Matrix(hidden, input);
    output_weights = Matrix(output, hidden);
    hidden_weights.randomise();
    output_weights.randomise();
}

void NeuralNet::train(Image* images, int n) {
    for (int i = 0; i < n; ++i) {
        if (i % 100 == 0) { std::cout << "Img: " << i << std::endl; }
        Image currentImage = images[i];
        Matrix correctOutput = Matrix(10, 1);
        correctOutput.setElement(currentImage.getLabel(), 1);

        // Train
        

    }
}