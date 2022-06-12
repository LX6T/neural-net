#include <iostream>
#include "matrix.h"
#include "image.h"

int main() {

    int n = 702;

    image images[n];
    csvToImages(images, "datasets/mnist_train.csv", n);

    images[701].printImage();

    return 0;
}
