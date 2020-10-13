//
//  sparse_matrix.cpp
//  template
//
//  Created by lvhb on 2020/10/12.
//  Copyright © 2020 lvhb. All rights reserved.
//

#include<iostream>
#include<set>
#include "sparse_matrix.h"
using namespace::std;

SparseMatrix::SparseMatrix():rowNum(0),colNum(0){
    matrix.clear();
}

SparseMatrix::SparseMatrix(int rowNum, int colNum):rowNum(rowNum),colNum(colNum){
    matrix.clear();
}

SparseMatrix::~SparseMatrix(){
    /**直接clear就可以了，根据我在Xcode上的测试结果，直接clear和交换空map释放的内存一样多*/
    matrix.clear();
}

SparseMatrix::SparseMatrix(const SparseMatrix& B){
    rowNum = B.getRowNum();
    colNum = B.getColNum();
    matrix.clear();
    for(auto &it : B.getMatrix()){
        matrix[it.first] = vector<PII>(it.second);
    }
}

SparseMatrix& SparseMatrix::operator= (const SparseMatrix& B){
    if (this == &B){
        return *this;
    }
    this->rowNum = B.getRowNum();
    this->colNum = B.getColNum();
    this->matrix.clear();
    for(auto &it : B.getMatrix()){
        this->matrix[it.first] = vector<PII>(it.second);
    }
    return *this;
}

int SparseMatrix::getValue(int rowIndex, int colIndex){
    if(!isValidRowAndCol(rowIndex, colIndex)){
        cout<<"输入的行或者列不对，获取失败"<<endl;
        return INT_MIN;
    }
    
    if(matrix.find(colIndex) == matrix.end()){
        return DEFAULT_VALUE;
    }
    
    //获取矩阵的colIndex列
    vector<PII>& colVec = matrix[colIndex];
    int targetIndex = getElementIndex(colVec, rowIndex);

    if(targetIndex >= 0 && colVec[targetIndex].index == rowIndex){
        return colVec[targetIndex].value;
    }
    else{
        return DEFAULT_VALUE;
    }
}

void SparseMatrix::setValue(int rowIndex, int colIndex, int newVal){
    if(!isValidRowAndCol(rowIndex, colIndex)){
        cout<<"输入的行或者列不对，获取失败"<<endl;
        return;
    }
    
    if(matrix.find(colIndex) == matrix.end()){
        matrix[colIndex] = vector<PII>();
    }
    vector<PII>& colVec = matrix[colIndex];
    int targetIndex = getElementIndex(colVec, rowIndex);
    PII newPII = make_pair(rowIndex, newVal);
    
    if(targetIndex == FLAG_NOT_FOUND){
        colVec.push_back(newPII);
    }
    //说明在colVec中没找到比rowIndex还要小的的index
    else if(targetIndex == -1){
        colVec.insert(colVec.begin(), newPII);
    }
    //说明在colVec中没找到和rowIndex一样的index
    else if(colVec[targetIndex].index < rowIndex){
        colVec.insert(colVec.begin()+targetIndex+1, newPII);
    }
    else{
        colVec[targetIndex] = newPII;
    }
}

SparseMatrix* SparseMatrix::multiply(const SparseMatrix* A, const SparseMatrix* B){
    if(A->colNum != B->rowNum){
        cout<<"矩阵维度错误，无法相乘"<<endl;
        return new SparseMatrix();
    }
    int n = A->rowNum;
    int m = A->colNum;
    int p = B->colNum;
    if(n==0 || m==0 || p==0){
        cout<<"存在维度为零的矩阵，无法相乘"<<endl;
        return new SparseMatrix();
    }
    
    //n*m的矩阵 乘以 m*p的矩阵 得到 n*p的矩阵
    SparseMatrix* res = new SparseMatrix(n, p);
    
    map<int, vector<PII>> rowFirstMatrix = A->getMatrixByRowFirst();
    for(int aRowIndex = 0; aRowIndex < n; aRowIndex++){
        if(rowFirstMatrix.find(aRowIndex) == rowFirstMatrix.end()){
            continue;
        }
        vector<PII>& rowVec = rowFirstMatrix.at(aRowIndex);
        
        for(int bColIndex = 0; bColIndex < p; bColIndex++){
            if(B->matrix.find(bColIndex) == B->matrix.end()){
                continue;
            }
            const vector<PII>& colVec = B->matrix.at(bColIndex);
            
            int elementValue = sparseVectorMultiply(rowVec, colVec);
            if(elementValue > 0){
                res->setValue(aRowIndex, bColIndex, elementValue);
            }
        }
    }
    return res;
};

void SparseMatrix::setColumnOpposite(int oriColumn, int oppositeColumn){
    if(0 <= oriColumn && oriColumn < colNum && 0 <= oppositeColumn && oppositeColumn < colNum){
        matrix.erase(oppositeColumn);
        
        if(matrix.find(oriColumn) != matrix.end()){
            matrix[oppositeColumn] = vector<PII>();
            for(auto pii : matrix[oriColumn]){
                matrix[oppositeColumn].push_back(make_pair(pii.index, -pii.value));
            }
        }
    }
};

void SparseMatrix::setColumnZero(int colIndex){
    matrix.erase(colIndex);
};

void SparseMatrix::printMatrix() const{
    map<int, vector<PII>> rowMatrix = getMatrixByRowFirst();
    for(int rowIndex = 0; rowIndex < rowNum; rowIndex++){
        vector<PII>& rowVec = rowMatrix[rowIndex];
        int preIndex = -1;
        for(auto pii : rowVec){
            for(int colIndex = preIndex + 1; colIndex < pii.index; colIndex++){
                cout<<0<<" ";
            }
            cout<<pii.value<<" ";
            preIndex = pii.index;
        }
        for(int colIndex = preIndex + 1; colIndex < colNum; colIndex++){
            cout<<0<<" ";
        }
        cout<<endl;
    }
}


int SparseMatrix::getElementIndex(const vector<PII>& vec, int targetIndex){
    if(vec.size()==0){
        return FLAG_NOT_FOUND;
    }
    
    int ansIndex = -1;
    int L = 0;
    int R = vec.size()-1;
    while(L<=R){
        int mid = (L+R)/2;
        if(vec[mid].index <= targetIndex){
            ansIndex = mid;
            L = mid + 1;
        }
        else{
            R = mid - 1;
        }
    }
    
    return ansIndex;
}

map<int, vector<PII>> SparseMatrix::getMatrixByRowFirst() const{
    map<int, vector<PII>> res;
    for(int colIndex = 0; colIndex < colNum; colIndex++){
        if(matrix.find(colIndex) == matrix.end()){
            continue;
        }
        
        const vector<PII>& colVec = matrix.at(colIndex);
        for(auto pii:colVec){
            int rowIndex = pii.index;
            if(res.find(rowIndex) == res.end()){
                res[rowIndex] = vector<PII>();
            }
            //因为是colIndex是从小到大增长，所以直接push_back就行了
            res[rowIndex].push_back(make_pair(colIndex, pii.value));
        }
    }
    return res;
}

int SparseMatrix::sparseVectorMultiply(const vector<PII>& aVec, const vector<PII>& bVec){
    set<int>oriAIndex;
    set<int>intersectIndex;
    for(auto pii:aVec){
        oriAIndex.insert(pii.index);
    }
    for(auto pii:bVec){
        if(oriAIndex.find(pii.index) != oriAIndex.end()){
            intersectIndex.insert(pii.index);
        }
    }
    
    vector<PII> newA;
    for(auto pii:aVec){
        if(intersectIndex.find(pii.index) != intersectIndex.end()){
            newA.push_back(pii);
        }
    }
    vector<PII> newB;
    for(auto pii:bVec){
        if(intersectIndex.find(pii.index) != intersectIndex.end()){
            newB.push_back(pii);
        }
    }
    
    int res = 0;
    for(int i = 0 ; i < newA.size(); i++){
        res += newA[i].value * newB[i].value;
    }
    return res;
}
