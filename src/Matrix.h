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
    Matrix (int nRows, int nCols);
    Matrix (int nRows, int nCols, double value);
    Matrix (int nRows, int nCols, const double* inputData);
    explicit Matrix (Matrix* A);

    // Declare destructor
    ~Matrix();

    // Getters/Setters
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
    [[nodiscard]] double getElement (int row, int col) const;
    [[nodiscard]] double getElement (int index) const;
    void setElement (int row, int col, double value);
    void setElement (int index, double value);

    // Fill Matrix with a value
    void fill (double value);

    // Copy from another Matrix
    void copy (const Matrix* A);

    // Transpose Matrix
    void transpose();

    // Randomise Matrix
    void randomise();

    // Print Matrix
    void printMatrix();

    // Save to file
    void save (const std::string& filename);

    // Load from file
    void load (const std::string& filename);

    // Comparison function
    bool isEqualTo (const Matrix* A);
    bool isEqualTo (double a);

    // Matrix arithmetic
    [[nodiscard]] Matrix add (const Matrix* A) const;
    [[nodiscard]] Matrix add (double a) const;
    [[nodiscard]] Matrix subtract (const Matrix* A) const;
    [[nodiscard]] Matrix subtract (double a) const;
    [[nodiscard]] Matrix dot (const Matrix* A) const ;
    [[nodiscard]] Matrix multiply (double a) const ;

protected:
    double* matrixData;                                     // Linear array storing Matrix data
    int rows, cols, elements;                               // Total number of rows, columns and elements
    [[nodiscard]] int flatten(int row, int col) const;     // Converts (rows, columns) to (index)
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

// CONSTRUCTOR (empty)
Matrix::Matrix(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new double[elements];
}

// CONSTRUCTOR (fill)
Matrix::Matrix(int nRows, int nCols, double value) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = value;
    }
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
Matrix::Matrix(Matrix* A) {
    rows = A->getRows();
    cols = A->getCols();
    elements = rows * cols;
    matrixData = new double[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = A->getElement(i);
    }
}

// DESTRUCTOR
Matrix::~Matrix() {
    delete[] matrixData;
}


// GETTER (element from row/column)
double Matrix::getElement(int row, int col) const {
    int index = flatten(row, col);
    return getElement(index);
}

// GETTER (element from index)
double Matrix::getElement(int index) const {
    if (index >= 0) {
        return matrixData[index];
    } else {
        std::cout << "get failed, matrixData not yet initialised" << std::endl;
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
    if (matrixData != nullptr) {
        matrixData[index] = value;
    } else {
        std::cout << "set failed, matrixData not yet initialised" << std::endl;
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
bool Matrix::isEqualTo(const Matrix* A) {

    // Checks if matrices have the same dimension
    if (rows != A->getRows() || cols != A->getCols())
        return false;

    // Checks if elements are the same
    bool isEqual = true;
    for (int i = 0; i < elements; ++i) {
        if (matrixData[i] != A->getElement(i)) {
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
Matrix Matrix::add(const Matrix* A) const {
    Matrix sum = Matrix(rows, cols, 0.0);
    for (int i = 0; i < elements; ++i) {
        sum.setElement(i, getElement(i) + A->getElement(i));
    }
    return sum;
}

// Matrix + scalar
Matrix Matrix::add(double a) const {
    Matrix sum = Matrix(rows, cols, 0.0);
    for (int i = 0; i < elements; ++i) {
        sum.setElement(i, getElement(i) + a);
    }
    return sum;
}


// Matrix - Matrix
Matrix Matrix::subtract(const Matrix* A) const {
    Matrix difference = Matrix(rows, cols, 0.0);
    for (int i = 0; i < elements; ++i) {
        difference.setElement(i, getElement(i) - A->getElement(i));
    }
    return difference;
}

// Matrix - scalar
Matrix Matrix::subtract(double a) const {
    Matrix difference = Matrix(rows, cols, 0.0);
    for (int i = 0; i < elements; ++i) {
        difference.setElement(i, getElement(i) - a);
    }
    return difference;
}


// Matrix * Matrix
Matrix Matrix::dot(const Matrix* A) const {
    int leftRows = rows;
    int leftCols = cols;
    int rightRows = A->getRows();
    int rightCols = A->getCols();

    Matrix dotProduct = Matrix(leftRows, rightCols, 0.0);

    if (leftCols == rightRows) {
        for (int i = 0; i < leftRows; ++i) {
            for (int j = 0; j < rightCols; ++j) {
                int dotProdIndex = i * rightCols + j;
                double sumOfProducts = 0.0;
                for (int k = 0; k < leftCols; ++k) {
                    int leftIndex = i * leftCols + k;
                    int rightIndex = k * rightCols + j;
                    sumOfProducts += getElement(leftIndex) * A->getElement(rightIndex);
                }
                dotProduct.setElement(dotProdIndex, sumOfProducts);
            }
        }
    } else {
        std::cout << "dot product failed, matrix dimensions invalid" << std::endl;
    }
    return dotProduct;
}

// Matrix * scalar
Matrix Matrix::multiply(double a) const {
    Matrix product = Matrix(rows, cols, 0.0);
    for (int i = 0; i < elements; ++i) {
        product.setElement(i, getElement(i) * a);
    }
    return product;
}


// Converts rows and columns to linear index
int Matrix::flatten(int row, int col) const {
    if (row < rows && col < cols && row >= 0 && col >= 0) {
        return row * cols + col;
    } else {
        std::cout << "conversion fail, coordinates out of bounds" << std::endl;
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
        std::cout << "print fail, matrixData not yet initialised" << std::endl;
    }
}

// Transposes the Matrix
void Matrix::transpose() {

    Matrix T(cols, rows, matrixData);

    if (matrixData != nullptr) {
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                T.setElement(j, i, getElement(i, j));
            }
        }
        copy(&T);
//        std::cout << "transpose success" << std::endl;
    } else {
        std::cout << "transpose fail, matrixData not yet initialised" << std::endl;
    }
}

// Saves the Matrix to a file
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
        std::cout << "save fail, matrixData not yet initialised" << std::endl;
    }

    mFile.close();

}

// Loads a Matrix from a file
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
        std::cout << "load fail, matrixData not yet initialised" << std::endl;
    }

    mFile.close();

}

// Copies the data from another Matrix
void Matrix::copy(const Matrix* A) {
    rows = A->getRows();
    cols = A->getCols();
    elements = rows * cols;

    matrixData = new double[elements];

    for (int i=0; i<elements; ++i) {
        setElement(i, A->getElement(i));
    }

}

// Fills the Matrix with a single value
void Matrix::fill(double value) {
    if (matrixData != nullptr) {
        for (int i=0; i<elements; ++i) {
            matrixData[i] = value;
        }
//        std::cout << "fill success" << std::endl;
    } else {
        std::cout << "fill fail, matrixData not yet initialised" << std::endl;
    }

}

// Randomises all elements of the Matrix
void Matrix::randomise() {
    double min = -1.0 / sqrt(rows);
    double max = 1.0 / sqrt(rows);
    for (int i = 0; i < elements; ++i) {
        matrixData[i] = ( rand() / ((double)RAND_MAX+1)) * (max-min) + min;
    }
}