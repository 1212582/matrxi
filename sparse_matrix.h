//
//  sparse_matrix.h
//  template
//
//  Created by lvhb on 2020/10/12.
//  Copyright © 2020 lvhb. All rights reserved.
//

#ifndef sparse_matrix_h
#define sparse_matrix_h

#include <map>
#include <vector>
using namespace::std;

#define PII pair<int,int>
#define index first
#define value second

/**
 稀疏矩阵
 */
class SparseMatrix{
private:
    /**矩阵的行数*/
    int rowNum;
    /**矩阵的列数*/
    int colNum;
    
    /**
     实际存储矩阵元素的数据结构
     matrix[i]是vector<PII>的类型，存储了矩阵第i列的所有元素
     PII是pair<int,int>类型的数据，first存储了矩阵元素的行坐标，second存储了矩阵元素的值
     */
    map<int, vector<PII>>matrix;
    
    /**
     判断坐标(rowIndex,colIndex)是不是有效的矩阵坐标
     */
    inline bool isValidRowAndCol(int rowIndex, int colIndex){
        return (0 <= rowIndex && rowIndex < rowNum && 0 <= colIndex && colIndex < colNum);
    }
    
    /**
     成员变量matrix是按照列优先来存储元素的
     对matrix进行转换，得到的新matrix是按照行优先来存储元素的，即map[i]存储的是第i行的所有元素
     */
    map<int, vector<PII>> getMatrixByRowFirst() const;
    
    /**
     vec中的元素是PII类型，PII的first是index，second是value
     获取vec中这样的元素（实际上获取的是元素在vec中的下标），它的index在满足<=targetIndex的前提下尽量大
     */
    static int getElementIndex(const vector<PII>& vec, int targetIndex);
    
    /**
     计算稀疏向量aVec和bVec的点乘
     */
    static int sparseVectorMultiply(const vector<PII>& aVec, const vector<PII>& bVec);

public:
    /**矩阵元素的默认值*/
    static const int DEFAULT_VALUE = 0;
    /**没有找到对应元素的标志*/
    static const int FLAG_NOT_FOUND = -2;
    
    SparseMatrix();
    SparseMatrix(int rowNum, int colNum);
    ~SparseMatrix();
    /**拷贝构造函数*/
    SparseMatrix(const SparseMatrix & B);
    /**赋值构造函数*/
    SparseMatrix& operator= (const SparseMatrix& B);
    
    int getValue(int rowIndex, int colIndex);
    void setValue(int rowIndex, int colIndex, int newVal);
    
    //计算两个稀疏矩阵A和B的乘积
    static SparseMatrix* multiply(const SparseMatrix* A, const SparseMatrix* B);
    
    //将oppositeColumn这一列中的所有元素，设成oriColumn中对应元素的相反数
    void setColumnOpposite(int oriColumn, int oppositeColumn);
    
    //将colIndex这一列中的所有元素设为0
    void setColumnZero(int colIndex);
    
    //将稀疏矩阵按照正常形式打印出来
    void printMatrix()const;
    
    int getRowNum() const { return rowNum; }
    int getColNum() const { return colNum; }
    map<int, vector<PII>> getMatrix() const { return matrix; }
};
#endif /* sparse_matrix_h */
