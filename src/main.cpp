#include <iostream>
#include "Matrix.h"
#include "Image.h"
#include "NeuralNet.h"


void trainTest(const std::string& root, const std::string& filename, int n, int L) {
    std::vector<Image> trainingImages = csvToImages(root + filename, n);
    NeuralNet net = NeuralNet(L, 784, 300, 10);
    net.train(trainingImages, n);
    net.save(root + "/networks");
}

double predictTest(const std::string& root, const std::string& filename, int n, int L) {
    std::vector<Image> predictingImages = csvToImages(root + filename, n);
    NeuralNet net = NeuralNet(L, 784, 300, 10);
    net.load(root + "/networks");
    double accuracy = net.predictImages(predictingImages, n);
    return accuracy;
}

int main() {
    std::string root = "C:/Users/alex/CLionProjects/neural-net";
    int n = 10;

    double avgScore = 0.0;
    for (int i = 0; i < n; ++i) {
        trainTest(root, "/data/mnist_test.csv", 10000, 2);
        double score = predictTest(root, "/data/mnist_train.csv", 702, 2);
        std::cout << "Score: " << score << std::endl;
        avgScore += score;
    }

    avgScore /= n;
    std::cout << "Average score: " << avgScore << std::endl;

    return 0;
}