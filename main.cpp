#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <map>
using namespace std;

#define PB push_back
#define MP make_pair
#define PII pair<int,int>
#define index first
#define value second
#define OO INT_MAX

#include "sparse_matrix.h"
#include "sparse_matrix_test.h"

SparseMatrix* createSparseMatrixA(){
    SparseMatrix* A = new SparseMatrix(3, 4);
    A->setValue(1, 1, 12);
    A->setValue(1, 3, 51);
    A->setValue(0, 1, 11);
    A->setValue(2, 2, 3);
    A->setValue(2, 0, 6);
    return A;
}

SparseMatrix* createSparseMatrixB(){
    SparseMatrix* B = new SparseMatrix(4, 3);
    B->setValue(1, 1, 12);
    B->setValue(0, 0, 3);
    B->setValue(3, 2, 10);
    B->setValue(3, 0, 7);
    return B;
}

void testCopyConstructor(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest::testCopyConstructor(*A);
}

void testAssignmentConstructor(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest::testAssignmentConstructor(*A);
}

void testGetVal(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest* testInstance = new SparseMatrixTest(A);
    testInstance->testPrintMatrix();
    testInstance->testGetVal(10);
}

void testSetVal(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest* testInstance = new SparseMatrixTest(A);
    testInstance->testPrintMatrix();
    testInstance->testSetVal(6);
}

void testSetColumnOpposite(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest* testInstance = new SparseMatrixTest(A);
    testInstance->testPrintMatrix();
    testInstance->testSetColumnOpposite(0, 1);
    testInstance->testSetColumnOpposite(3, 2);
}

void testSetColumnZero(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest* testInstance = new SparseMatrixTest(A);
    testInstance->testPrintMatrix();
    testInstance->testSetColumnZero(0);
    testInstance->testSetColumnZero(3);
}


void testMultiply(){
    SparseMatrix* A = createSparseMatrixA();
    SparseMatrixTest* testInstance = new SparseMatrixTest(A);
    testInstance->testPrintMatrix();
    SparseMatrix* B = createSparseMatrixB();
    testInstance->testMultiply(B);
}


int main() {
//    testCopyConstructor();
//    testAssignmentConstructor();
//    testGetVal();
//    testSetVal();
//    testSetColumnOpposite();
//    testSetColumnZero();
    testMultiply();
    return 0;
}
