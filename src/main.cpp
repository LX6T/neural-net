#include <iostream>
#include "Matrix.h"
#include "Image.h"
#include "NeuralNet.h"


void trainTest(const std::string& filename, int n, int L) {
    std::vector<Image> trainingImages = csvToImages(filename, n);
    NeuralNet net = NeuralNet(L, 784, 300, 10);
    net.train(trainingImages, n);
    net.save("../networks");
}

void predictTest(const std::string& filename, int n, int L) {
    std::vector<Image> predictingImages = csvToImages(filename, n);
    NeuralNet net = NeuralNet(L, 784, 300, 10);
    net.load("../networks");
    double accuracy = net.predictImages(predictingImages, n);
    std::cout << "Accuracy: " << accuracy << std::endl;
}

int main() {

    trainTest("../data/mnist_test.csv", 10000, 2);
    predictTest("../data/mnist_test.csv", 10000, 2);

    return 0;
}