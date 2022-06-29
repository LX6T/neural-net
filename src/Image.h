//
// Created by alex on 13/06/2022.
//

#include "Matrix.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#pragma once

class Image: public Matrix {
public:
    Image();
    Image(int label, int nRows, int nCols, const double* inputData);

    [[nodiscard]] int getLabel() const;
    void setLabel(int newLabel);

    void copy(Image* img);
    void printImage();

private:
    int label;
};

// CONSTRUCTOR (default)
Image::Image() : Matrix() {
    this->label = -1;
}

// CONSTRUCTOR (input + label)
Image::Image(int label, int nRows, int nCols, const double* inputData) : Matrix(nRows, nCols, inputData) {
    this->label = label;
}

// GETTER (image label)
int Image::getLabel() const {
    return label;
}

// SETTER (image label)
void Image::setLabel(int newLabel) {
    label = newLabel;
}

// Copies data from another image
void Image::copy(Image* img){
    label = img->getLabel();
    rows = img->getRows();
    cols = img->getCols();
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = img->getElement(i);
    }
}

// Prints image and label
void Image::printImage() {
    printMatrix();
    std::cout << "Label: " << label << std::endl;
}

// Converts data from a CSV file into an array of images
void csvToImages(Image* images, const std::string &filename, int n) {

    std::ifstream filein(filename);

    if (filein) {
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
            images[i].copy(&img);
        }
    } else {
        std::cout << "file not found" << std::endl;
    }

}