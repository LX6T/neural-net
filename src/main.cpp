#include <iostream>
#include "matrix.h"


int main() {
    double valuesA[4] = {1, 2, 3, 4};
    matrix A(2, 2, valuesA);
    A.printMatrix();

    double valuesB[4] = {1, 1, 1, 1};
    matrix B(2, 2, valuesB);
    B.printMatrix();

    A.transpose();
    A.printMatrix();

    A.save("A.txt");

    matrix C;
    C.load("A.txt");
    C.printMatrix();

    return 0;
}
