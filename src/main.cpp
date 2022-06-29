#include <iostream>
#include "Image.h"

int main() {

    auto* trainingImages = new Image[702];
    std::string trainSetFilename = "datasets/mnist_train.csv";
    std::string testSetFilename = "datasets/mnist_test.csv";


    csvToImages(trainingImages, trainSetFilename, 702);

    trainingImages[701].printImage();

    delete[] trainingImages;

    return 0;
}
