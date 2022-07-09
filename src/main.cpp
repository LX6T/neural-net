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
    net.save("../networks");
}

void predictTest() {
    int numberOfImages = 10000;
    std::vector<Image> testingImages = csvToImages("../data/mnist_test.csv", numberOfImages);
    NeuralNet net = NeuralNet(784, 300, 10);
    net.load("../networks");
    double accuracy = net.predictImages(testingImages, numberOfImages);
    std::cout << "Accuracy: " << accuracy << std::endl;
}

int main() {

    //matrixTest();

    trainTest();

    predictTest();

    return 0;
}
