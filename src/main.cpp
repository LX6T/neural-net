#include <iostream>
#include "Matrix.h"
#include "Image.h"
#include "NeuralNet.h"

// SET PATHS TO MNIST DATASETS (CSV FORMAT)
#define trainingSetPath "C:\\Users\\alex\\JetBrainsProjects\\CLionProjects\\neural-net\\data\\mnist_train.csv"
#define testingSetPath "C:\\Users\\alex\\JetBrainsProjects\\CLionProjects\\neural-net\\data\\mnist_test.csv"

void trainTest(int n, int L) {
    std::vector<Image> trainingImages = csvToImages(trainingSetPath, n);
    NeuralNet net = NeuralNet(L, 784, 300, 10);
    net.train(trainingImages, n);
    net.save("./networks");
}

double predictTest(int n, int L) {
    std::vector<Image> predictingImages = csvToImages(testingSetPath, n);
    NeuralNet net = NeuralNet(L, 784, 300, 10);
    net.load("./networks");
    double accuracy = net.predictImages(predictingImages, n);
    return accuracy;
}

int main(int argc, char* argv[]) {

    if (argc != 5) {
        std::cout << "The following arguments are required: rounds, hiddenLayers, trainingN, testingN" << std::endl;
        return 0;
    }

    int rounds = std::stoi(argv[1]);
    int hiddenLayers = std::stoi(argv[2]);
    int trainingN = std::stoi(argv[3]);
    int testingN = std::stoi(argv[4]);

    if (trainingN > 60000) {
        std::cout << "Maximum number of training images is 60000";
        return 0;
    } else if (testingN > 10000) {
        std::cout << "Maximum number of testing images is 10000";
        return 0;
    }

    std::cout << "Number of training/testing cycles: " << rounds << std::endl;

    for (int i = 0; i < rounds; ++i) {
        std::cout << " =========== ROUND " << i + 1 << " =========== " << std::endl;
        std::cout << "Number of hidden layers: " << hiddenLayers << std::endl;
        std::cout << "Number of images to train on: " << trainingN << std::endl;
        std::cout << "Number of images to test on: " << testingN << std::endl;

        trainTest(trainingN, hiddenLayers);
        double score = predictTest(testingN, hiddenLayers);
        std::cout << "Accuracy: " << score << std::endl << std::endl;
    }

    return 0;
}