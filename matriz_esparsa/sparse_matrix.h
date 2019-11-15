#include <stdlib.h>
//#include <malloc.h>
#include <stdio.h>

///Struct No para criar os nos da matriz
struct no{
    int row, col, dataValue;
    struct no *prox_col, *prox_row;
};
typedef struct no ElementNode;
struct sparse{
    int rowNum, colNum;
    ElementNode *prox_col, *prox_row;
};
typedef struct sparse SparseMatrix;

/// Função para iniciar matriz
SparseMatrix *initMatrix();
void insertElement(SparseMatrix *matrix, int value, int i, int j);