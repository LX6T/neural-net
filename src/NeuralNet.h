//
// Created by alex on 9/07/2022.
//

#include <cmath>
#include "Matrix.h"
#include "Image.h"
#pragma once

class NeuralNet {
public:
    NeuralNet(int input, int hidden, int output);

    void train(std::vector<Image> trainingImages, int n);
    Matrix predictImage(const Image& img) const;
    Matrix predict(const Matrix& inputData) const;

    void saveNet(const std::string& directory) const;
    void loadNet(const std::string& filename);
    void printNet() const;

private:
    int input;
    int hidden;
    int output;
    Matrix hiddenWeights;
    Matrix outputWeights;
    static double randomise(double x);
    static double sigmoid(double x);
    static Matrix sigmoidPrime(const Matrix& A);
    static Matrix softMax(const Matrix& A);
};

NeuralNet::NeuralNet(int input, int hidden, int output) {
    this->input = input;
    this->output = output;
    this->hidden = hidden;
    hiddenWeights = Matrix(hidden, input).apply(randomise);
    outputWeights = Matrix(output, hidden).apply(randomise);
}

void NeuralNet::train(std::vector<Image> trainingImages, int n) {
    for (int i = 0; i < n; ++i) {

        // Process input data
        Image currentImage = trainingImages[i];
        Matrix inputData = Matrix(784, 1);
        for (int j = 0; j < 784; ++j) { inputData.setValue(j, currentImage.getValue(j)); }

        // Generate ideal output data
        Matrix outputData = Matrix(10, 1);
        outputData.setValue(currentImage.getLabel(), 1);

        // Feed input data forward
        Matrix hiddenInputs = hiddenWeights.dot(inputData);         // (300x784)*(784x1) = 300 x 1
        Matrix hiddenOutputs = hiddenInputs.apply(sigmoid);
        Matrix finalInputs = outputWeights.dot(hiddenOutputs);      // (10x300)*(300x1) = 10 x 1
        Matrix finalOutputs = finalInputs.apply(sigmoid);

        // Find errors
        Matrix outputErrors = outputData.minus(finalOutputs);
        Matrix hiddenErrors = outputWeights.transpose().dot(outputErrors);

        // Backpropagation
        outputWeights = outputWeights.plus(outputErrors.times(sigmoidPrime(finalOutputs)).dot(hiddenOutputs.transpose()).times(0.1));
        hiddenWeights = hiddenWeights.plus(hiddenErrors.times(sigmoidPrime(hiddenOutputs)).dot(inputData.transpose()).times(0.1));

        if (i == 700) {
            std::cout << "Img No. " << i << std::endl;
            currentImage.printImage();
            inputData.printMatrix();
            outputData.printMatrix();
            std::cout << hiddenOutputs.getRows() << "x" << hiddenOutputs.getCols() << std::endl;
            hiddenOutputs.printMatrix();
            std::cout << finalOutputs.getRows() << "x" << finalOutputs.getCols() << std::endl;
            finalOutputs.printMatrix();
            outputErrors.printMatrix();
            hiddenErrors.printMatrix();
            std::cout << std::endl;
        }
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

Matrix NeuralNet::softMax(const Matrix &A) {
    return Matrix();
}

void NeuralNet::saveNet(const std::string& directory) const {
    hiddenWeights.save(directory + "/hiddenWeights");
    outputWeights.save(directory + "/outputWeights");
}

Matrix NeuralNet::predictImage(const Image& img) const {
    return Matrix();
}

Matrix NeuralNet::predict(const Matrix& inputData) const {
    return Matrix();
}

void NeuralNet::loadNet(const std::string &filename) {

}

void NeuralNet::printNet() const {

}

double NeuralNet::randomise(double x) {
    return ((double) rand() / RAND_MAX) * 2 - 1;
}
