//
// Created by alex on 9/07/2022.
//

#include <cmath>
#include "Matrix.h"
#include "Image.h"
#pragma once

class NeuralNet {
public:
    NeuralNet(int hiddenLayers, int inputSize, int layerSize, int outputSize);

    void train(std::vector<Image> images, int n);

    [[nodiscard]] int predict(const Image& img) const;
    [[nodiscard]] double predictImages(std::vector<Image> images, int n) const;

    void save(const std::string& directory) const;
    void load(const std::string& directory);

private:
    int hiddenLayers;
    std::vector<Matrix> weightsLayer;
    static double sigmoid(double x);
    static Matrix sigmoidPrime(const Matrix& A);
};

NeuralNet::NeuralNet(int hiddenLayers, int inputSize, int layerSize, int outputSize) {

    this->hiddenLayers = hiddenLayers;

    // Initialise weightsLayer randomly
    weightsLayer = std::vector<Matrix>(hiddenLayers + 1);
    weightsLayer[0] = Matrix(layerSize, inputSize, "random");
    for (int i = 1; i < hiddenLayers; ++i) {
        weightsLayer[i] = Matrix(layerSize, layerSize, "random");
    }
    weightsLayer[hiddenLayers] = Matrix(outputSize, layerSize, "random");
    // weightsLayer[0]              : 300x784
    // weightsLayer[i]              : 300x300
    // weightsLayer[hiddenLayers]   : 10x300
}


void NeuralNet::train(std::vector<Image> images, int n) {
    std::cout << "Training network on " << n << " images..." << std::endl;
    for (int i = 0; i < n; ++i) {
        if (i % 1000 == 0 && i != 0) {
            std::cout << "\tTrained on " << i << " images..." << std::endl;
        }

        // Generate ideal output data
        Matrix outputData = Matrix(10, 1, 0.0);
        outputData.setValue(images[i].getLabel(), 1.0);
        // outputData: 10x1


        // Feed input data forward
        std::vector<Matrix> nodeLayer = std::vector<Matrix>(hiddenLayers + 2);     // hiddenLayers+2 layers
        nodeLayer[0] = images[i].getMatrix().flatten();
        for (int j = 1; j < hiddenLayers + 2; ++j) {
            nodeLayer[j] = weightsLayer[j - 1].dot(nodeLayer[j - 1]).apply(sigmoid);
        }
        Matrix finalOutputs = nodeLayer[hiddenLayers + 1];
        // nodeLayer[0]        : 784x1
        // nodeLayer[j]        : 300x1
        // nodeLayer[hiddenLayers+1]        : 10x1


        // Find errors
        std::vector<Matrix> errors = std::vector<Matrix>(hiddenLayers + 2);      // hiddenLayers+2 layers
        errors[hiddenLayers + 1] = outputData.minus(finalOutputs);
        for (int j = hiddenLayers; j >= 0; --j) {
            errors[j] = weightsLayer[j].transpose().dot(errors[j + 1]);
        }
        // errors[0] : 784x1 (not used)
        // errors[j] : 300x1
        // errors[hiddenLayers] : 10x1


        // Backpropagation
        for (int j = hiddenLayers; j >= 0; --j) {
            weightsLayer[j] = weightsLayer[j].plus(errors[j+1].times(sigmoidPrime(nodeLayer[j+1])).dot(nodeLayer[j].transpose()).times(0.1));
        }
        // weightsLayer[0]        : 300x784
        // weightsLayer[i]        : 300x300
        // weightsLayer[hiddenLayers]        : 10x300

        // Testing
        if (i % 100 == 0) {
//            images[i].printImage();
//            finalOutputs.printMatrix();
        }
    }
}


int NeuralNet::predict(const Image& img) const {

    // Feed input data forward
    std::vector<Matrix> nodeLayer = std::vector<Matrix>(hiddenLayers + 2);     // hiddenLayers+2 layers
    nodeLayer[0] = img.getMatrix().flatten();
    for (int j = 1; j < hiddenLayers + 2; ++j) {
        nodeLayer[j] = weightsLayer[j - 1].dot(nodeLayer[j - 1]).apply(sigmoid);
    }
    Matrix finalOutputs = nodeLayer[hiddenLayers + 1];
    // nodeLayer[0]        : 784x1      (input data)
    // nodeLayer[j]        : 300x1
    // nodeLayer[hiddenLayers+1]      : 10x1       (final outputs)

    // Identify network's prediction
    int prediction = -1;
    double predictionWeight = 0.0;
    for (int j = 0; j < 10; ++j) {
        if (finalOutputs.getValue(j) > predictionWeight) {
            prediction = j;
            predictionWeight = finalOutputs.getValue(j);
        }
    }
    return prediction;
}

double NeuralNet::predictImages(std::vector<Image> images, int n) const {
    std::cout << "Predicting " << n << " images..." << std::endl;
    int correctGuesses = 0;
    for (int i = 0; i < n; ++i) {

        // Network predicted value
        int prediction = predict(images[i]);

        // Compare network's guess with correct answer
        if (prediction == images[i].getLabel())
            correctGuesses++;
    }
    return 1.0 * correctGuesses / n;
}


void NeuralNet::save(const std::string& directory) const {
    for (int i = 0; i < hiddenLayers + 1; ++i) {
        weightsLayer[i].save(directory + "/weightsLayer" + (char)(i + 48));
    }
}

void NeuralNet::load(const std::string &directory) {
    for (int i = 0; i < hiddenLayers + 1; ++i) {
        weightsLayer[i].load(directory + "/weightsLayer" + (char)(i + 48));
    }
}


double NeuralNet::sigmoid(double x) {
    return 1 / (1 + std::exp(-x));
}

Matrix NeuralNet::sigmoidPrime(const Matrix &A) {
    Matrix ones = Matrix(A.getRows(), A.getCols());
    Matrix subtracted = ones.minus(A);
    Matrix multiplied = A.times(subtracted);
    return multiplied;
}