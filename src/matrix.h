//
// Created by alex on 12/06/2022.
//

#pragma once

template <typename T>
class matrix {
public:
    // Declare constructors
    matrix();
    matrix(int rows, int cols);
    matrix(int rows, int cols, const T* inputData);
    matrix(const matrix<T>& rhs);

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


// CONSTRUCTOR (default)
template<typename T>
matrix<T>::matrix() {
    rows = 1;
    cols = 1;
    elements = rows * cols;
    matrixData = new T[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = 0;
    }
}

// CONSTRUCTOR (zeros)
template<typename T>
matrix<T>::matrix(int nRows, int nCols) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new T[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = 0;
    }
}

// CONSTRUCTOR (input)
template<typename T>
matrix<T>::matrix(int nRows, int nCols, const T* inputData) {
    rows = nRows;
    cols = nCols;
    elements = rows * cols;
    matrixData = new T[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = inputData[i];
    }
}

// CONSTRUCTOR (copy)
template<typename T>
matrix<T>::matrix(const matrix<T>& rhs) {
    rows = rhs.getRows();
    cols = rhs.getCols();
    elements = rows * cols;
    matrixData = new T[elements];
    for (int i=0; i<elements; ++i) {
        matrixData[i] = rhs.getElement(i);
    }
}

// DESTRUCTOR
template<typename T>
matrix<T>::~matrix() {
    delete[] matrixData;
}


// GETTER (element)
template<typename T>
T matrix<T>::getElement(int row, int col) {
    int index = subToInd(row, col);
    if (index >= 0) {
        return matrixData[index];
    } else {
        return 0.0;
    }
}

// SETTER (element)
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

// GETTER (#rows)
template<typename T>
int matrix<T>::getRows() {
    return rows;
}

// GETTER (#columns)
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
    int rows = lhs.rows;
    int cols = lhs.cols;
    int elements = lhs.elements;
    U* tempSum = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempSum[i] = lhs.matrixData[i] + rhs.matrixData[i];
    }
    matrix<U> sum(rows, cols, tempSum);
    delete[] tempSum;
    return sum;
}

// scalar + matrix
template<class U>
matrix<U> operator+(const U &lhs, const matrix<U> &rhs) {
    int rows = rhs.rows;
    int cols = rhs.cols;
    int elements = rhs.elements;
    U* tempSum = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempSum[i] = lhs + rhs.matrixData[i];
    }
    matrix<U> sum(rows, cols, tempSum);
    delete[] tempSum;
    return sum;
}

// matrix + scalar
template<class U>
matrix<U> operator+(const matrix<U> &lhs, const U &rhs) {
    int rows = lhs.rows;
    int cols = lhs.cols;
    int elements = lhs.elements;
    U* tempSum = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempSum[i] = lhs.matrixData[i] + rhs;
    }
    matrix<U> sum(rows, cols, tempSum);
    delete[] tempSum;
    return sum;
}


// matrix - matrix
template<class U>
matrix<U> operator-(const matrix<U> &lhs, const matrix<U> &rhs) {
    int rows = lhs.rows;
    int cols = lhs.cols;
    int elements = lhs.elements;
    U* tempDiff = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempDiff[i] = lhs.matrixData[i] - rhs.matrixData[i];
    }
    matrix<U> diff(rows, cols, tempDiff);
    delete[] tempDiff;
    return diff;
}

// scalar - matrix
template<class U>
matrix<U> operator-(const U &lhs, const matrix<U> &rhs) {
    int rows = rhs.rows;
    int cols = rhs.cols;
    int elements = rhs.elements;
    U* tempDiff = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempDiff[i] = lhs - rhs.matrixData[i];
    }
    matrix<U> diff(rows, cols, tempDiff);
    delete[] tempDiff;
    return diff;
}

// matrix - scalar
template<class U>
matrix<U> operator-(const matrix<U> &lhs, const U &rhs) {
    int rows = lhs.rows;
    int cols = lhs.cols;
    int elements = lhs.elements;
    U* tempDiff = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempDiff[i] = lhs.matrixData[i] - rhs;
    }
    matrix<U> diff(rows, cols, tempDiff);
    delete[] tempDiff;
    return diff;
}


// matrix * matrix
template<class U>
matrix<U> operator*(const matrix<U> &lhs, const matrix<U> &rhs) {
    int leftRows = lhs.rows;
    int leftCols = lhs.cols;
    int rightRows = rhs.rows;
    int rightCols = rhs.cols;

    if (leftCols != rightRows) {
        matrix<U> dotProduct(1, 1);
        return dotProduct;
    }

    int prodRows = leftRows;
    int prodCols = rightCols;
    int prodElements = leftRows * rightCols;

    U* tempProd = new U[prodElements];
    for (int i = 0; i < leftRows; ++i) {
        for (int j = 0; j < rightCols; ++j) {
            int prodIndex = rhs.subToInd(prodRows, prodCols);
            U sumOfProducts = 0.0;
            for (int k = 0; k < leftCols; ++k) {
                int leftIndex = lhs.subToInd(i, k);
                int rightIndex = rhs.subToInd(k, j);
                sumOfProducts += lhs.matrixData[leftIndex] * rhs.matrixData[rightIndex];
            }
            tempProd[prodIndex] = sumOfProducts;
        }
    }

    matrix<U> dotProduct(prodRows, prodCols, tempProd);
    delete[] tempProd;
    return dotProduct;
}

// scalar * matrix
template<class U>
matrix<U> operator*(const U &lhs, const matrix<U> &rhs) {
    int rows = rhs.rows;
    int cols = rhs.cols;
    int elements = rhs.elements;
    U* tempProd = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempProd[i] = lhs - rhs.matrixData[i];
    }
    matrix<U> prod(rows, cols, tempProd);
    delete[] tempProd;
    return prod;
}

// matrix * scalar
template<class U>
matrix<U> operator*(const matrix<U> &lhs, const U &rhs) {
    int rows = lhs.rows;
    int cols = lhs.cols;
    int elements = lhs.elements;
    U* tempProd = new U[elements];
    for (int i = 0; i < elements; ++i) {
        tempProd[i] = lhs.matrixData[i] - rhs;
    }
    matrix<U> prod(rows, cols, tempProd);
    delete[] tempProd;
    return prod;
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

