//
// Created by alex on 13/06/2022.
//

#include "Matrix.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#pragma once

class Image {
public:
    Image();
    Image(int label, int nRows, int nCols, const double* inputData);

    [[nodiscard]] int getLabel() const;
    [[nodiscard]] Matrix getMatrix() const;

    [[maybe_unused]] void printImage();

private:
    Matrix imgMatrix;
    int label;
};

Image::Image() {
    imgMatrix = Matrix();
    this->label = -1;
}

Image::Image(int label, int nRows, int nCols, const double* inputData) {
    imgMatrix = Matrix(nRows, nCols, inputData);
    this->label = label;
}

int Image::getLabel() const {
    return label;
}

Matrix Image::getMatrix() const {
    return imgMatrix;
}

[[maybe_unused]] void Image::printImage() {
    imgMatrix.printMatrix();
    std::cout << "Label: " << label << std::endl;
}


std::vector<Image> csvToImages(const std::string& filename, int n) {

    std::vector<Image> images = std::vector<Image>(n);

    std::ifstream filein(filename);

    std::string line;
    std::getline(filein, line);

    for (int i = 0; i < n; ++i) {
        std::getline(filein, line);
        std::istringstream lineStream(line);
        std::string labelString;
        std::getline(lineStream, labelString, ',');
        int label = std::stoi(labelString);

        double data[28*28];
        int j = 0;
        std::string num;
        while (std::getline(lineStream, num, ',')) {
            data[j] = std::stod(num) / 256.0;
            ++j;
        }
        Image img(label, 28, 28, data);
        images[i] = img;
    }
    return images;
}