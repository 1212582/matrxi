//
//  sparse_matrix_test.cpp
//  template
//
//  Created by lvhb on 2020/10/13.
//  Copyright © 2020 lvhb. All rights reserved.
//

#include<iostream>
#include "sparse_matrix_test.h"
using namespace::std;

SparseMatrixTest::SparseMatrixTest(){
    A = nullptr;
}

SparseMatrixTest::SparseMatrixTest(SparseMatrix* A){
    this->A = A;
}

void SparseMatrixTest::setTestSparseMatrix(SparseMatrix *A){
    this->A = A;
}

void SparseMatrixTest::testPrintMatrix(){
    cout<<"打印矩阵:"<<endl;
    A->printMatrix();
}

void SparseMatrixTest::testGetVal(int getNums){
    if(getNums <= 0){
        return;
    }
    srand(unsigned(time(0)));
    while(getNums--){
        int rowIndex = rand() % A->getRowNum();
        int colIndex = rand() % A->getColNum();
        cout<<"获取("<<rowIndex<<", "<<colIndex<<")"<<"处的元素为: "<<A->getValue(rowIndex, colIndex)<<endl;
    }
}

void SparseMatrixTest::testSetVal(int setNums){
    if(setNums <= 0){
        return;
    }
    srand(unsigned(time(0)));
    while(setNums--){
        int rowIndex = rand() % A->getRowNum();
        int colIndex = rand() % A->getColNum();
        int newVal = rand() % 100;
        cout<<"设置("<<rowIndex<<", "<<colIndex<<")"<<"处的元素为: "<<newVal<<endl;
        A->setValue(rowIndex, colIndex, newVal);
    }
    cout<<"更新后的矩阵是："<<endl;
    A->printMatrix();
};

void SparseMatrixTest::testCopyConstructor(const SparseMatrix & B){
    cout<<"拷贝的源矩阵："<<endl;
    B.printMatrix();
    cout<<"拷贝后的目的矩阵变为："<<endl;
    SparseMatrix* C = new SparseMatrix(B);
    C->printMatrix();
}


void SparseMatrixTest::testAssignmentConstructor(const SparseMatrix & B){
    cout<<"赋值的源矩阵："<<endl;
    B.printMatrix();
    cout<<"赋值后的目的矩阵变为："<<endl;
    //C必须先完成初始化再赋值，这样调用的才是赋值构造函数，否则调用的是拷贝构造函数
    SparseMatrix C;
    C = B;
    C.printMatrix();
}


void SparseMatrixTest::testMultiply(SparseMatrix* B){
    cout<<"乘以矩阵B: "<<endl;
    B->printMatrix();
    cout<<"结果是: "<<endl;
    SparseMatrix* C = SparseMatrix::multiply(this->A, B);
    C->printMatrix();
}

void SparseMatrixTest::testSetColumnOpposite(int oriColumn, int oppositeColumn){
    cout<<"将第"<<oppositeColumn<<"列中的所有元素，设成第"<<oriColumn<<"列中对应元素的相反数"<<endl;
    A->setColumnOpposite(oriColumn, oppositeColumn);
    A->printMatrix();
}

void SparseMatrixTest::testSetColumnZero(int colIndex){
    cout<<"将第"<<colIndex<<"列中的所有元素清零"<<endl;
    A->setColumnZero(colIndex);
    A->printMatrix();
}


