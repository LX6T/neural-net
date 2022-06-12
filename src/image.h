//
// Created by alex on 13/06/2022.
//

#include "matrix.h"
#include <iostream>
#include <cstring>
#include <string>
#include <sstream>
#pragma once

class image: public matrix {
public:
    image();
    image(int label, int nRows, int nCols, const double* inputData);

    [[nodiscard]] int getLabel() const;
    void setLabel(int newLabel);

    void copy(image& img);
    void printImage();

private:
    int label;
};

image::image() : matrix() {
    this->label = -1;
}

image::image(int label, int nRows, int nCols, const double* inputData) : matrix(nRows, nCols, inputData) {
    this->label = label;
}

int image::getLabel() const {
    return label;
}

void image::setLabel(int newLabel) {
    label = newLabel;
}

void image::copy(image &img){
    label = img.getLabel();
    rows = img.getRows();
    cols = img.getCols();
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = img.getElement(i);
    }
}

void image::printImage() {
    printMatrix();
    std::cout << "Label: " << label << std::endl;
}


void csvToImages(image* images, const std::string &filename, int n) {
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
        image img(label, 28, 28, data);
        images[i].copy(img);
    }
}