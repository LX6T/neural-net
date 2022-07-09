#include <iostream>
#include "Matrix.h"
#include "Image.h"
#include "NeuralNet.h"

double addOne(double x) {
    return x + 1;
}

void matrixTest() {
    double data[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    Matrix A = Matrix(2,3,data);

    A = A.apply(addOne);
    A.printMatrix();
}

void trainTest() {
    int numberOfImages = 702;
    std::vector<Image> trainingImages = csvToImages("../data/mnist_train.csv", numberOfImages);
    NeuralNet net = NeuralNet(784, 300, 10);
    net.train(trainingImages, numberOfImages);
    net.saveNet("../networks");
}

int main() {

    //matrixTest();

    trainTest();

    return 0;
}
