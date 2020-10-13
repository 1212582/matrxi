//
//  sparse_matrix_test.h
//  template
//
//  Created by lvhb on 2020/10/13.
//  Copyright © 2020 lvhb. All rights reserved.
//

#ifndef sparse_matrix_test_h
#define sparse_matrix_test_h

#include "sparse_matrix.h"

//专用于测试SparseMatrix的类
class SparseMatrixTest{
public:
    SparseMatrixTest();
    SparseMatrixTest(SparseMatrix* A);
    void setTestSparseMatrix(SparseMatrix* A);
    void testPrintMatrix();
    void testGetVal(int getNums);
    void testSetVal(int setNums);
    void testMultiply(SparseMatrix* B);
    void testSetColumnOpposite(int oriColumn, int oppositeColumn);
    void testSetColumnZero(int colIndex);
    static void testAssignmentConstructor(const SparseMatrix & B);
    static void testCopyConstructor(const SparseMatrix & B);

private:
    SparseMatrix* A;
    SparseMatrix* B;
};

#endif /* sparse_matrix_test_h */
