#include <stdlib.h>
//#include <malloc.h>
#include <stdio.h>

///Struct No para criar os nos da matriz
struct no{
    int row, col, dataValue;
    struct no *prox_col, *prox_row;
};
typedef struct no ElementNode;
typedef struct no SparseMatrix;
///Struct para nó cabeça
typedef struct{
    int IndexValue;
    ElementNode *prox_col, *prox_row;
}HeaderNode;

/// Função para iniciar matriz
SparseMatrix *initMatrix();
void insertElement(SparseMatrix *matrix, int value, int i, int j);