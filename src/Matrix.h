//
// Created by alex on 12/06/2022.
//

#include <iostream>
#include <fstream>
#include <iomanip>
#include <utility>
#include <vector>
#include <random>

#pragma once

class Matrix {
public:
    // Declare constructors
    Matrix();
    Matrix(int nRows, int nCols);
    Matrix(int nRows, int nCols, const std::string& random);
    Matrix(int nRows, int nCols, double fillValue);
    Matrix(int nRows, int nCols, const double* inputData);
    Matrix(int nRows, int nCols, std::vector<double> inputData);
    Matrix(const Matrix& A);

    // Getters/Setters
    [[nodiscard]] int getRows() const;
    [[nodiscard]] int getCols() const;
    [[nodiscard]] double getValue(int row, int col) const;
    [[nodiscard]] double getValue(int index) const;
    void setValue(int row, int col, double value);
    void setValue(int index, double value);

    // Print Matrix
    void printMatrix() const;

    // Save to file
    void save(const std::string& filename) const;

    // Load from file
    void load (const std::string& filename);

    // Comparison function
    [[nodiscard]] bool hasSameDimensionsAs (const Matrix& A) const;

    // Matrix arithmetic
    [[nodiscard]] Matrix plus (const Matrix& A) const;
    [[nodiscard]] Matrix plus (double a) const;
    [[nodiscard]] Matrix minus (const Matrix& A) const;
    [[nodiscard]] Matrix minus (double a) const;
    [[nodiscard]] Matrix dot (const Matrix& A) const;
    [[nodiscard]] Matrix times (const Matrix& A) const;
    [[nodiscard]] Matrix times (double a) const;
    [[nodiscard]] Matrix toThePowerOf (int a) const;
    [[nodiscard]] Matrix apply (double (&func)(double)) const;

    // Transpose
    [[nodiscard]] Matrix transpose() const;

    // Flatten
    [[nodiscard]] Matrix flatten() const;

private:
    std::vector<double> matrixData;                         // Linear array storing Matrix data
    int rows, cols, size;                                   // Total number of rows, columns and size
    [[nodiscard]] int rcToIndex(int row, int col) const;    // Converts (rows, columns) to (index)
};


// CONSTRUCTOR (default: 1x1 containing 0)
Matrix::Matrix() {
    rows = 1;
    cols = 1;
    size = rows * cols;
    matrixData = std::vector<double>(1, 0);
    matrixData[0] = 0;
}

// CONSTRUCTOR (empty)
Matrix::Matrix(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    size = rows * cols;
    matrixData = std::vector<double>(size, 0.0);
}

// CONSTRUCTOR (randomise)
Matrix::Matrix(int nRows, int nCols, const std::string& random) {
    if (random == "random") {
        std::random_device rd;
        std::default_random_engine eng(rd());
        std::uniform_real_distribution<float> dist(-1, 1);
        rows = nRows;
        cols = nCols;
        size = rows * cols;
        matrixData = std::vector<double>(size);
        for (int i = 0; i < size; ++i) {
            matrixData[i] = dist(eng);
        }
    } else {
        Matrix(nRows, nCols);
    }
}

// CONSTRUCTOR (fill)
Matrix::Matrix(int nRows, int nCols, double fillValue) {
    rows = nRows;
    cols = nCols;
    size = rows * cols;
    matrixData = std::vector<double>(size, fillValue);
}

// CONSTRUCTOR (input from array)
Matrix::Matrix(int nRows, int nCols, const double* inputData) {
    rows = nRows;
    cols = nCols;
    size = rows * cols;
    matrixData = std::vector<double>(size);
    for (int i=0; i < size; ++i) {
        matrixData[i] = inputData[i];
    }
}

// CONSTRUCTOR (input from vector)
Matrix::Matrix(int nRows, int nCols, std::vector<double> inputData) {
    rows = nRows;
    cols = nCols;
    size = rows * cols;
    matrixData = std::move(inputData);
}

// CONSTRUCTOR (copy)
Matrix::Matrix(const Matrix& A) {
    rows = A.getRows();
    cols = A.getCols();
    size = rows * cols;
    matrixData = std::vector<double>(size);
    for (int i=0; i < size; ++i) {
        matrixData[i] = A.getValue(i);
    }
}


// GETTER (element from row/column)
double Matrix::getValue(int row, int col) const {
    int index = rcToIndex(row, col);
    return getValue(index);
}

// GETTER (element from index)
double Matrix::getValue(int index) const {
    if (index >= 0 and index < size) {
        return matrixData[index];
    } else {
        std::cout << "get failed, index out of range" << std::endl;
        return 0.0;
    }
}

// SETTER (element from row/column)
void Matrix::setValue(int row, int col, double value) {
    int index = rcToIndex(row, col);
    setValue(index, value);
}

// SETTER (element from index)
void Matrix::setValue(int index, double value) {
    if (index >= 0 and index < size) {
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


// Matrix has same dimensions as Matrix
bool Matrix::hasSameDimensionsAs(const Matrix &A) const {

    // Checks if matrices have the same dimension
    if (rows != A.getRows() || cols != A.getCols())
        return false;

    return true;
}


// Matrix + Matrix
Matrix Matrix::plus(const Matrix &A) const {
    Matrix result = Matrix(rows, cols);
    if (hasSameDimensionsAs(A)) {
        for (int i = 0; i < size; ++i) {
            result.setValue(i, getValue(i) + A.getValue(i));
        }
    } else {
        std::cout << "plus failed, inconsistent dimensions: "
                  << rows << "x" << cols << " "
                  << A.getRows() << "x" << A.getCols() << std::endl;
    }
    return result;
}

// Matrix + scalar
Matrix Matrix::plus(double a) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < size; ++i) {
        result.setValue(i, getValue(i) + a);
    }
    return result;
}


// Matrix - Matrix
Matrix Matrix::minus(const Matrix &A) const {
    Matrix result = Matrix(rows, cols);
    if (hasSameDimensionsAs(A)) {
        for (int i = 0; i < size; ++i) {
            result.setValue(i, getValue(i) - A.getValue(i));
        }
    } else {
        std::cout << "minus failed, inconsistent dimensions: "
                  << rows << "x" << cols << " "
                  << A.getRows() << "x" << A.getCols() << std::endl;
    }
    return result;
}

// Matrix - scalar
Matrix Matrix::minus(double a) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < size; ++i) {
        result.setValue(i, getValue(i) - a);
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
                    sum += getValue(leftIndex) * A.getValue(rightIndex);
                }
                result.setValue(dpIndex, sum);
            }
        }
    } else {
        std::cout << "dot product failed, matrix dimensions invalid: "
                  << lr << "x" << lc << " "
                  << rr << "x" << rc << std::endl;
    }
    return result;
}

// Matrix * Matrix (value-wise)
Matrix Matrix::times(const Matrix &A) const {
    Matrix result = Matrix(rows, cols);
    if (hasSameDimensionsAs(A)) {
        for (int i = 0; i < size; ++i) {
            result.setValue(i, getValue(i) + A.getValue(i));
        }
    } else {
        std::cout << "times failed, inconsistent dimensions: "
                  << rows << "x" << cols << " "
                  << A.getRows() << "x" << A.getCols() << std::endl;
    }
    return result;
}

// Matrix * scalar
Matrix Matrix::times(double a) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < size; ++i) {
        result.setValue(i, getValue(i) * a);
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

// Apply a function to all values of the matrix
Matrix Matrix::apply(double (&func)(double)) const {
    Matrix result = Matrix(rows, cols);
    for (int i = 0; i < size; ++i) {
        result.setValue(i, func(getValue(i)));
    }
    return result;
}


// Converts rows and columns to linear index
int Matrix::rcToIndex(int row, int col) const {
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
            std::cout << std::fixed << std::setprecision(3) << getValue(i, j) << ' ';
        }
        std::cout << std::endl;
    }
}

Matrix Matrix::transpose() const {

    Matrix transposedMatrix(cols, rows);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            transposedMatrix.setValue(j, i, getValue(i, j));
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
            mFile << getValue(i, j) << ' ';
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
        size = rows * cols;
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                double value;
                mFile >> value;
                setValue(i, j, value);
            }
        }
    } else {
        std::cout << "load fail, file is empty" << std::endl;
    }

    mFile.close();

}

Matrix Matrix::flatten() const {
    return {size, 1, matrixData};
}
