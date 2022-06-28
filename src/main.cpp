#include <iostream>
#include "Image.h"

int main() {

    int n = 702;
    Image images[n];
    std::string trainSetFilename = "datasets/mnist_train.csv";
    std::string testSetFilename = "datasets/mnist_test.csv";


    csvToImages(images, trainSetFilename, n);

    images[701].printImage();

    return 0;
}
