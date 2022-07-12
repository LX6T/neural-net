#include <iostream>
#include "Matrix.h"
#include "Image.h"
#include "NeuralNet.h"


void trainTest(const std::string& filename, int n) {
    std::vector<Image> trainingImages = csvToImages(filename, n);
    NeuralNet net = NeuralNet(3, 784, 300, 10);
    net.train(trainingImages, n);
    net.save("../networks");
}

void predictTest(const std::string& filename, int n) {
    std::vector<Image> predictingImages = csvToImages(filename, n);
    NeuralNet net = NeuralNet(3, 784, 300, 10);
    net.load("../networks");
    double accuracy = net.predictImages(predictingImages, n);
    std::cout << "Accuracy: " << accuracy << std::endl;
}

int main() {

//    trainTest("../data/mnist_test.csv", 2500);
//    predictTest("../data/mnist_test.csv", 10000);

    for (int i = 500; i < 10000; i = i + 500) {
        trainTest("../data/mnist_test.csv", i);
        predictTest("../data/mnist_test.csv", 10000);
    }

    return 0;
}