#include <iostream>
#include "Matrix.h"
#include "Image.h"

void matrixTest() {
    double data[6] = {1.0, 2.0, 3.0, 4.0, 5.0, 6.0};

    Matrix A = Matrix(2,3,data);
    Matrix B = A.dot(A.transpose());
    Matrix C = A.transpose().dot(A);

    A.printMatrix();
    B.printMatrix();
    C.printMatrix();
}

void trainTest() {
    const int MNIST_TRAIN_N = 702;
    const std::string MNIST_TRAIN = "../data/mnist_train.csv";

    Image trainingImages[MNIST_TRAIN_N];

    csvToImages(trainingImages, MNIST_TRAIN, MNIST_TRAIN_N);

    trainingImages[MNIST_TRAIN_N - 1].printImage();
}

int main() {

    trainTest();

    return 0;
}
