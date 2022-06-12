//
// Created by alex on 12/06/2022.
//

#pragma once

template <typename T>
class matrix {
public:
    // Declare constructor
    matrix(int rows, int cols, const T* inputData);

    // Declare destructor
    ~matrix();

    // Getters and Setters
    T getElement(int row, int col);
    bool setElement(int row, int col, T value);
    int getRows();
    int getCols();

    // Overload "==" operator
    bool operator== (const matrix<T>& rhs);

    // Overload "+", "-" and "*" operators
    // Supports matrix-matrix, scalar-matrix, matrix-scalar
    template <class U> friend matrix<U> operator+ (const matrix<U>& lhs, const matrix<U>& rhs);
    template <class U> friend matrix<U> operator+ (const U& lhs, const matrix<U>& rhs);
    template <class U> friend matrix<U> operator+ (const matrix<U>& lhs, const U& rhs);

    template <class U> friend matrix<U> operator- (const matrix<U>& lhs, const matrix<U>& rhs);
    template <class U> friend matrix<U> operator- (const U& lhs, const matrix<U>& rhs);
    template <class U> friend matrix<U> operator- (const matrix<U>& lhs, const U& rhs);

    template <class U> friend matrix<U> operator* (const matrix<U>& lhs, const matrix<U>& rhs);
    template <class U> friend matrix<U> operator* (const U& lhs, const matrix<U>& rhs);
    template <class U> friend matrix<U> operator* (const matrix<U>& lhs, const U& rhs);

private:
    T *matrixData;                      // Linear array storing matrix data
    int rows, cols, elements;           // Total number of rows, columns and elements
    int subToInd(int row, int col);     // Converts (rows, columns) to (index)
};

// Define constructor
template<typename T>
matrix<T>::matrix(int rows, int cols, const T* inputData) {
    this->rows = rows;
    this->cols = cols;
    elements = rows * cols;
    matrixData = new T[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = inputData[i];
    }
}

// Define destructor
template<typename T>
matrix<T>::~matrix() {
    delete[] matrixData;
}

// Element Getter
template<typename T>
T matrix<T>::getElement(int row, int col) {
    int index = subToInd(row, col);
    if (index >= 0) {
        return matrixData[index];
    } else {
        return 0.0;
    }
}

// Element Setter
template<typename T>
bool matrix<T>::setElement(int row, int col, T value) {
    int index = subToInd(row, col);
    if (matrixData != nullptr) {
        matrixData[index] = value;
        return true;
    } else {
        return false;
    }
}

// Getter for number of rows
template<typename T>
int matrix<T>::getRows() {
    return rows;
}

// Getter for number of columns
template<typename T>
int matrix<T>::getCols() {
    return cols;
}


// matrix == matrix
template<typename T>
bool matrix<T>::operator==(const matrix<T> &rhs) {

    // Checks if matrices have the same dimension
    if (this->rows != rhs.rows || this->cols != rhs.cols)
        return false;

    // Checks if elements are the same
    bool isEqual = true;
    for (int i = 0; i < elements; ++i) {
        if (this->elements[i] != rhs.elements[i]) {
            isEqual = false;
        }
    }
    return isEqual;
}


// matrix + matrix
template<class U>
matrix<U> operator+(const matrix<U> &lhs, const matrix<U> &rhs) {

    return matrix<U>(0, 0);
}

// scalar + matrix
template<class U>
matrix<U> operator+(const U &lhs, const matrix<U> &rhs) {
    return matrix<U>(0, 0);
}

// matrix + scalar
template<class U>
matrix<U> operator+(const matrix<U> &lhs, const U &rhs) {
    return matrix<U>(0, 0);
}


// matrix - matrix
template<class U>
matrix<U> operator-(const matrix<U> &lhs, const matrix<U> &rhs) {
    return matrix<U>(0, 0);
}

// scalar - matrix
template<class U>
matrix<U> operator-(const U &lhs, const matrix<U> &rhs) {
    return matrix<U>(0, 0);
}

// matrix - scalar
template<class U>
matrix<U> operator-(const matrix<U> &lhs, const U &rhs) {
    return matrix<U>(0, 0);
}


// matrix * matrix
template<class U>
matrix<U> operator*(const matrix<U> &lhs, const matrix<U> &rhs) {
    return matrix<U>(0, 0);
}

// scalar * matrix
template<class U>
matrix<U> operator*(const U &lhs, const matrix<U> &rhs) {
    return matrix<U>(0, 0);
}

// matrix * scalar
template<class U>
matrix<U> operator*(const matrix<U> &lhs, const U &rhs) {
    return matrix<U>(0, 0);
}


// Converts rows and columns to linear index
template<typename T>
int matrix<T>::subToInd(int row, int col) {
    if (row < rows && col < cols && row >= 0 && col >= 0) {
        return row * cols + col;
    } else {
        return -1;
    }
}

