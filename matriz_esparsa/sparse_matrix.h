#include <stdlib.h>
//#include <malloc.h>
#include <stdio.h>

///Struct No para criar os nos da matriz
struct no{
    int row, col, dataValue;
    struct no *prox_col, *prox_row;
};
typedef struct no ElementNode;

/// Função para iniciar matriz
ElementNode *initMatrix();
ElementNode *allocHeader(int i, int j);
void insertElement(ElementNode *matrix, int value, int i, int j);