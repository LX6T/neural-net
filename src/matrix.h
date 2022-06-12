//
// Created by alex on 12/06/2022.
//

#include <iostream>
#pragma once

class matrix {
public:
    // Declare constructors
    matrix();
    matrix(int nRows, int nCols);
    matrix(int nRows, int nCols, const double* inputData);
    matrix(matrix& A);

    // Declare destructor
    ~matrix();

    // Getters/Setters
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
    double getElement(int row, int col);
    double getElement(int index);
    bool setElement(int row, int col, double value);
    bool setElement(int index, double value);

    // Print matrix
    bool printMatrix();

    // Comparison function
    bool isEqualTo (matrix& A);
    bool isEqualTo (double a);

    // Matrix arithmetic
    void add (matrix& A);
    void add (double a);

    void subtract (matrix& A);
    void subtract (double a);

    matrix dot (matrix& A);
    void multiply (double a);

    matrix power (int a);

private:
    double* matrixData;                      // Linear array storing matrix data
    int rows, cols, elements;           // Total number of rows, columns and elements
    [[nodiscard]] int subToInd(int row, int col) const;     // Converts (rows, columns) to (index)
};


// CONSTRUCTOR (default)
matrix::matrix() {
    rows = 1;
    cols = 1;
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = 0;
    }
}

// CONSTRUCTOR (zeros)
matrix::matrix(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = 0;
    }
}

// CONSTRUCTOR (input)
matrix::matrix(int nRows, int nCols, const double* inputData) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = inputData[i];
    }
}

// CONSTRUCTOR (copy)
matrix::matrix(matrix& A) {
    rows = A.getRows();
    cols = A.getCols();
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = A.getElement(i);
    }
}

// DESTRUCTOR
matrix::~matrix() {
    delete[] matrixData;
}


// GETTER (element from row/column)
double matrix::getElement(int row, int col) {
    int index = subToInd(row, col);
    return getElement(index);
}

// GETTER (element from index)
double matrix::getElement(int index) {
    if (index >= 0) {
        return matrixData[index];
    } else {
        return 0.0;
    }
}

// SETTER (element from row/column)
bool matrix::setElement(int row, int col, double value) {
    int index = subToInd(row, col);
    return setElement(index, value);
}

// SETTER (element from index)
bool matrix::setElement(int index, double value) {
    if (matrixData != nullptr) {
        matrixData[index] = value;
        return true;
    } else {
        return false;
    }
}

// GETTER (#rows)
int matrix::getRows() const {
    return rows;
}

// GETTER (#columns)
int matrix::getCols() const {
    return cols;
}


// matrix == matrix
bool matrix::isEqualTo(matrix &A) {

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

// matrix == scalar
bool matrix::isEqualTo(double a) {

    // Checks if elements are the same
    bool isEqual = true;
    for (int i = 0; i < elements; ++i) {
        if (matrixData[i] != a) {
            isEqual = false;
        }
    }
    return isEqual;
}


// matrix + matrix
void matrix::add(matrix &A) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] += A.getElement(i);
    }
}

// matrix + scalar
void matrix::add(double a) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] += a;
    }
}


// matrix + matrix
void matrix::subtract(matrix &A) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] -= A.getElement(i);
    }
}

// matrix + scalar
void matrix::subtract(double a) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] -= a;
    }
}


// matrix * matrix
matrix matrix::dot(matrix &A) {
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

        matrix dotProduct(prodRows, prodCols, tempProd);
        return dotProduct;
    } else {
        std::cout << "dot product failed" << std::endl;
    }

}

// matrix * scalar
void matrix::multiply(double a) {
    for (int i = 0; i < elements; ++i) {
        matrixData[i] *= a;
    }
}


// matrix ^ integer
matrix matrix::power(int a) {

    matrix A(rows, cols, matrixData);
    matrix B(rows, cols, matrixData);

    for (int i = 1; i < a; ++i) {
        B = B.dot(A);
    }

    return B;
}


// Converts rows and columns to linear index
int matrix::subToInd(int row, int col) const {
    if (row < rows && col < cols && row >= 0 && col >= 0) {
        return row * cols + col;
    } else {
        std::cout << "conversion fail" << std::endl;
        return -1;
    }
}

// Prints the matrix
bool matrix::printMatrix() {
    if (matrixData != nullptr) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                int index = subToInd(i, j);
                std::cout << getElement(index) << ' ';
            }
            std::cout << std::endl;
        }
        std::cout << "print success" << std::endl;
        return true;
    } else {
        std::cout << "print fail" << std::endl;
        return false;
    }
}

