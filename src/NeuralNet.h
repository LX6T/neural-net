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

    void train(std::vector<Image> images, int n);
    int predict(Image img) const;
    double predictImages(std::vector<Image> images, int n) const;

    void save(const std::string& directory) const;
    void load(const std::string& filename);
    void print() const;

private:
    int input;
    int hidden;
    int output;
    Matrix hiddenWeights;
    Matrix outputWeights;
    static double randomise(double x);
    static double sigmoid(double x);
    static Matrix sigmoidPrime(const Matrix& A);
};

NeuralNet::NeuralNet(int input, int hidden, int output) {
    this->input = input;
    this->output = output;
    this->hidden = hidden;
    hiddenWeights = Matrix(hidden, input).apply(randomise);
    outputWeights = Matrix(output, hidden).apply(randomise);
}

void NeuralNet::train(std::vector<Image> images, int n) {
    for (int i = 0; i < n; ++i) {

        // Process input data
        Image currentImage = images[i];
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

        if (i % 1000 == 0) {
            std::cout << "Img No. " << i << std::endl;
//            outputData.printMatrix();
//            hiddenOutputs.printMatrix();
//            finalOutputs.printMatrix();
//            outputErrors.printMatrix();
//            hiddenErrors.printMatrix();
//            std::cout << std::endl;
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

void NeuralNet::save(const std::string& directory) const {
    hiddenWeights.save(directory + "/hiddenWeights");
    outputWeights.save(directory + "/outputWeights");
}

int NeuralNet::predict(Image img) const {
    // Process input data
    Matrix inputData = Matrix(784, 1);
    for (int j = 0; j < 784; ++j) { inputData.setValue(j, img.getValue(j)); }

    // Feed input data forward
    Matrix hiddenInputs = hiddenWeights.dot(inputData);         // (300x784)*(784x1) = 300 x 1
    Matrix hiddenOutputs = hiddenInputs.apply(sigmoid);
    Matrix finalInputs = outputWeights.dot(hiddenOutputs);      // (10x300)*(300x1) = 10 x 1
    Matrix finalOutputs = finalInputs.apply(sigmoid);

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
    int correctGuesses = 0;
    for (int i = 0; i < n; ++i) {
        // Network predicted value
        int prediction = predict(images[i]);

        // Compare network's guess with correct answer
        if (prediction == images[i].getLabel())
            correctGuesses++;

        if (i % 1000 == 0)
            std::cout << "Img No. " << i << std::endl;
    }
    return 1.0 * correctGuesses / n;
}

void NeuralNet::load(const std::string &directory) {
    hiddenWeights.load(directory + "/hiddenWeights");
    outputWeights.load(directory + "/outputWeights");
}

void NeuralNet::print() const {

}

double NeuralNet::randomise(double x) {
    return ((double) rand() / RAND_MAX) * 2 - 1;
}

