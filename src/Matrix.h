//
// Created by alex on 12/06/2022.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cmath>
#include <random>

#pragma once

class Matrix {
public:
    // Declare constructors
    Matrix();
    Matrix(int nRows, int nCols);
    Matrix(int nRows, int nCols, const double* inputData);
    Matrix(Matrix& A);

    // Declare destructor
    ~Matrix();

    // Getters/Setters
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
    double getElement(int row, int col);
    double getElement(int index);
    void setElement(int row, int col, double value);
    void setElement(int index, double value);

    // Fill Matrix with a value
    void fill (double value);

    // Copy from another Matrix
    void copy (Matrix& A);

    // Transpose Matrix
    void transpose();

    // Randomise Matrix
    void randomise();

    // Print Matrix
    void printMatrix();

    // Save to file
    void save(const std::string& filename);

    // Load from file
    void load (const std::string& filename);

    // Comparison function
    bool isEqualTo (Matrix& A);
    bool isEqualTo (double a);

    // Matrix arithmetic
    void add (Matrix& A);
    void add (double a);
    void subtract (Matrix& A);
    void subtract (double a);
    void dot (Matrix& A);
    void multiply (double a);
    void power (int a);

protected:
    double* matrixData;                      // Linear array storing Matrix data
    int rows, cols, elements;           // Total number of rows, columns and elements
    [[nodiscard]] int subToInd(int row, int col) const;     // Converts (rows, columns) to (index)
};


// CONSTRUCTOR (default)
Matrix::Matrix() {
    rows = 1;
    cols = 1;
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = 0;
    }
}

// CONSTRUCTOR (fill)
Matrix::Matrix(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new double[elements];
}

// CONSTRUCTOR (input)
Matrix::Matrix(int nRows, int nCols, const double* inputData) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = inputData[i];
    }
}

// CONSTRUCTOR (copy)
Matrix::Matrix(Matrix& A) {
    rows = A.getRows();
    cols = A.getCols();
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = A.getElement(i);
    }
}

// DESTRUCTOR
Matrix::~Matrix() {
    delete[] matrixData;
}


// GETTER (element from row/column)
double Matrix::getElement(int row, int col) {
    int index = subToInd(row, col);
    return getElement(index);
}

// GETTER (element from index)
double Matrix::getElement(int index) {
    if (index >= 0) {
        return matrixData[index];
    } else {
//        std::cout << "get failed" << std::endl;
        return 0.0;
    }
}

// SETTER (element from row/column)
void Matrix::setElement(int row, int col, double value) {
    int index = subToInd(row, col);
    setElement(index, value);
}

// SETTER (element from index)
void Matrix::setElement(int index, double value) {
    if (matrixData != nullptr) {
        matrixData[index] = value;
    } else {
//        std::cout << "set failed" << std::endl;
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
bool Matrix::isEqualTo(Matrix &A) {

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
bool Matrix::isEqualTo(double a) {

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
void Matrix::add(Matrix &A) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] += A.getElement(i);
    }
}

// Matrix + scalar
void Matrix::add(double a) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] += a;
    }
}


// Matrix + Matrix
void Matrix::subtract(Matrix &A) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] -= A.getElement(i);
    }
}

// Matrix + scalar
void Matrix::subtract(double a) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] -= a;
    }
}


// Matrix * Matrix
void Matrix::dot(Matrix &A) {
    int leftRows = rows;
    int leftCols = cols;
    int rightRows = A.rows;
    int rightCols = A.cols;

    if (leftCols == rightRows) {

        int prodRows = leftRows;
        int prodCols = rightCols;
        int prodElements = leftRows * rightCols;

        double tempProd[prodElements];
        for (int i = 0; i < leftRows; ++i) {
            for (int j = 0; j < rightCols; ++j) {
                int prodIndex = i * rightCols + j;
                double sumOfProducts = 0.0;
                for (int k = 0; k < leftCols; ++k) {
                    int leftIndex = i * leftCols + k;
                    int rightIndex = k * rightCols + j;
                    sumOfProducts += matrixData[leftIndex] * A.getElement(rightIndex);
                }
                tempProd[prodIndex] = sumOfProducts;
            }
        }

        Matrix dotProduct(prodRows, prodCols, tempProd);
        copy(dotProduct);
    } else {
//        std::cout << "dot product failed" << std::endl;
    }

}

// Matrix * scalar
void Matrix::multiply(double a) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] *= a;
    }
}


// Matrix ^ integer
void Matrix::power(int a) {

    Matrix A(rows, cols, matrixData);
    Matrix B(rows, cols, matrixData);

    for (int i = 1; i < a; ++i) {
        B.dot(A);
    }

    copy(B);
}


// Converts rows and columns to linear index
int Matrix::subToInd(int row, int col) const {
    if (row < rows && col < cols && row >= 0 && col >= 0) {
        return row * cols + col;
    } else {
//        std::cout << "conversion fail" << std::endl;
        return -1;
    }
}

// Prints the Matrix
void Matrix::printMatrix() {
    std::cout << std::endl;
    if (matrixData != nullptr) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                std::cout << std::fixed << std::setprecision(3) << getElement(i, j) << ' ';
            }
            std::cout << std::endl;
        }
//        std::cout << "print success" << std::endl;
    } else {
//        std::cout << "print fail" << std::endl;
    }
}

void Matrix::transpose() {

    Matrix T(cols, rows, matrixData);

    if (matrixData != nullptr) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                T.setElement(j, i, getElement(i, j));
            }
        }
        copy(T);
//        std::cout << "transpose success" << std::endl;
    } else {
//        std::cout << "transpose fail" << std::endl;
    }
}

void Matrix::save(const std::string& filename) {
    std::ofstream mFile;
    mFile.open(filename);

    if (matrixData != nullptr) {
        mFile << rows << ' ' << cols << std::endl;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                mFile << getElement(i, j) << ' ';
            }
            mFile << std::endl;
        }
//        std::cout << "save success" << std::endl;
    } else {
//        std::cout << "save fail" << std::endl;
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
//        std::cout << "load success << std::endl";
    } else {
//        std::cout << "load fail" << std::endl;
    }

    mFile.close();

}

void Matrix::copy(Matrix &A) {
    rows = A.getRows();
    cols = A.getCols();
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = A.getElement(i);
    }
}

void Matrix::fill(double value) {
    if (matrixData != nullptr) {
        for (int i=0; i<elements; ++i) {
            matrixData[i] = value;
        }
//        std::cout << "fill success" << std::endl;
    } else {
//        std::cout << "fill fail" << std::endl;
    }

}

void Matrix::randomise() {
    double min = -1.0 / sqrt(rows);
    double max = 1.0 / sqrt(rows);
    for (int i = 0; i < elements; ++i) {
        matrixData[i] = ( rand() / ((double)RAND_MAX+1)) * (max-min) + min;
    }
}