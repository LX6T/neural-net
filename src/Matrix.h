//
// Created by alex on 12/06/2022.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>

#pragma once

class Matrix {
public:
    // Declare constructors
    Matrix();
    Matrix(int nRows, int nCols);
    Matrix(int nRows, int nCols, double fillValue);
    Matrix(int nRows, int nCols, const double* inputData);
    Matrix(const Matrix& A);

    // Getters/Setters
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
    double getElement(int row, int col) const;
    double getElement(int index) const;
    void setElement(int row, int col, double value);
    void setElement(int index, double value);

    // Fill Matrix with a value
    void fill (double value);

    // Copy from another Matrix
    void copy (const Matrix& A);

    // Print Matrix
    void printMatrix() const;

    // Save to file
    void save(const std::string& filename) const;

    // Load from file
    void load (const std::string& filename);

    // Comparison function
    bool isEqualTo (const Matrix& A) const;
    bool isEqualTo (double a) const;

    // Matrix arithmetic
    Matrix plus (const Matrix& A) const;
    Matrix plus (double a) const;
    Matrix minus (const Matrix& A) const;
    Matrix minus (double a) const;
    Matrix dot (const Matrix& A) const;
    Matrix times (double a) const;
    Matrix toThePowerOf (int a) const;

    // Transpose
    Matrix transpose() const;

private:
    std::vector<double> matrixData;                                     // Linear array storing Matrix data
    int rows, cols, elements;                                           // Total number of rows, columns and elements
    [[nodiscard]] int flatten(int row, int col) const;  // Converts (rows, columns) to (index)
};


// CONSTRUCTOR (default: 1x1 containing 0)
Matrix::Matrix() {
    rows = 1;
    cols = 1;
    elements = rows * cols;
    matrixData = std::vector<double>(1, 0);
    matrixData[0] = 0;
}

// CONSTRUCTOR (empty)
Matrix::Matrix(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = std::vector<double>(elements, 0.0);
}

// CONSTRUCTOR (fill)
Matrix::Matrix(int nRows, int nCols, const double fillValue) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = std::vector<double>(elements, fillValue);
}

// CONSTRUCTOR (input)
Matrix::Matrix(int nRows, int nCols, const double* inputData) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = std::vector<double>(elements);
    for (int i=0; i<elements; ++i) {
        matrixData[i] = inputData[i];
    }
}

// CONSTRUCTOR (copy)

Matrix::Matrix(const Matrix& A) {
    rows = A.getRows();
    cols = A.getCols();
    elements = rows * cols;
    matrixData = std::vector<double>(elements);
    for (int i=0; i<elements; ++i) {
        matrixData[i] = A.getElement(i);
    }
}


// GETTER (element from row/column)
double Matrix::getElement(int row, int col) const {
    int index = flatten(row, col);
    return getElement(index);
}

// GETTER (element from index)
double Matrix::getElement(int index) const {
    if (index >= 0 and index < elements) {
        return matrixData[index];
    } else {
        std::cout << "get failed, index out of range" << std::endl;
        return 0.0;
    }
}

// SETTER (element from row/column)
void Matrix::setElement(int row, int col, double value) {
    int index = flatten(row, col);
    setElement(index, value);
}

// SETTER (element from index)
void Matrix::setElement(int index, double value) {
    if (index >= 0 and index < elements) {
        matrixData[index] = value;
    } else {
        std::cout << "set failed, index out of range" << std::endl;
    }
}

// GETTER (#rows)
int Matrix::getRows() const {
    return rows;
}

// GETTER (#columns)
int Matrix::getCols() const {
    return cols;
}


// Matrix == Matrix
bool Matrix::isEqualTo(const Matrix &A) const {

    // Checks if matrices have the same dimension
    if (rows != A.getRows() || cols != A.getCols())
        return false;

    // Checks if elements are the same
    bool isEqual = true;
    for (int i = 0; i < elements; ++i) {
        if (matrixData[i] != A.getElement(i)) {
            isEqual = false;
        }
    }
    return isEqual;
}

// Matrix == scalar
bool Matrix::isEqualTo(double a) const {

    // Checks if elements are the same
    bool isEqual = true;
    for (int i = 0; i < elements; ++i) {
        if (matrixData[i] != a) {
            isEqual = false;
        }
    }
    return isEqual;
}


// Matrix + Matrix
Matrix Matrix::plus(const Matrix &A) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < elements; ++i) {
        result.setElement(i, getElement(i) + A.getElement(i));
    }
    return result;
}

// Matrix + scalar
Matrix Matrix::plus(double a) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < elements; ++i) {
        result.setElement(i, getElement(i) + a);
    }
    return result;
}


// Matrix - Matrix
Matrix Matrix::minus(const Matrix &A) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < elements; ++i) {
        result.setElement(i, getElement(i) - A.getElement(i));
    }
    return result;
}

// Matrix - scalar
Matrix Matrix::minus(double a) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < elements; ++i) {
        result.setElement(i, getElement(i) - a);
    }
    return result;
}


// Matrix * Matrix
Matrix Matrix::dot(const Matrix &A) const {

    int dpRows = rows;
    int dpCols = A.getCols();
    Matrix result = Matrix(dpRows, dpCols);

    int lr = rows;
    int lc = cols;
    int rr = A.getRows();
    int rc = A.getCols();

    if (lc == rr) {
        for (int i = 0; i < lr; ++i) {
            for (int j = 0; j < rc; ++j) {
                int dpIndex = i * rc + j;
                double sum = 0.0;
                for (int k = 0; k < lc; ++k) {
                    int leftIndex = i * lc + k;
                    int rightIndex = k * rc + j;
                    sum += getElement(leftIndex) * A.getElement(rightIndex);
                }
                result.setElement(dpIndex, sum);
            }
        }
    } else {
        std::cout << "dot product failed, matrix dimensions invalid" << std::endl;
    }
    return result;
}

// Matrix * scalar
Matrix Matrix::times(double a) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < elements; ++i) {
        result.setElement(i, getElement(i) * a);
    }
    return result;
}


// Matrix ^ integer
Matrix Matrix::toThePowerOf(int a) const {

    Matrix result = Matrix(*this);

    for (int i = 1; i < a; ++i) {
        result = result.dot(*this);
    }

    return result;
}


// Converts rows and columns to linear index
int Matrix::flatten(int row, int col) const {
    if (row < rows && col < cols && row >= 0 && col >= 0) {
        return row * cols + col;
    } else {
        std::cout << "conversion fail, index out of range" << std::endl;
        return -1;
    }
}

// Prints the Matrix
void Matrix::printMatrix() const {
    std::cout << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << std::fixed << std::setprecision(3) << getElement(i, j) << ' ';
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::transpose() const {

    Matrix transposedMatrix(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposedMatrix.setElement(j, i, getElement(i, j));
        }
    }

    return transposedMatrix;
}

void Matrix::save(const std::string& filename) const {
    std::ofstream mFile;
    mFile.open(filename);

    mFile << rows << ' ' << cols << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            mFile << getElement(i, j) << ' ';
        }
        mFile << std::endl;
    }

    mFile.close();
}

void Matrix::load(const std::string& filename) {
    std::ifstream mFile;
    mFile.open(filename);

    if(mFile.peek() != std::ifstream::traits_type::eof()) {
        mFile >> rows;
        mFile >> cols;
        elements = rows * cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double value;
                mFile >> value;
                setElement(i, j, value);
            }
        }
        std::cout << "load success" << std::endl;
    } else {
        std::cout << "load fail, file is empty" << std::endl;
    }

    mFile.close();

}

void Matrix::copy(const Matrix &A) {
    rows = A.getRows();
    cols = A.getCols();
    elements = rows * cols;
    matrixData = std::vector<double>(elements);
    for (int i=0; i<elements; ++i) {
        matrixData[i] = A.getElement(i);
    }
}

void Matrix::fill (double value) {
    for (int i=0; i<elements; ++i) {
        matrixData[i] = value;
    }
    std::cout << "fill success" << std::endl;
}