#include <iostream>
#include "matrix.h"
#include "image.h"

int main() {

    int n = 702;
    image images[n];
    std::string filename;

    std::cin >> filename;
    csvToImages(images, filename, n);

    images[701].printImage();

    return 0;
}
