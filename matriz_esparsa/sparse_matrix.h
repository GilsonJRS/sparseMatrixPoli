#include <stdlib.h>
#include <stdio.h>

struct no{
    int row, col, dataValue;
    struct no *prox_col, *prox_row;
};
typedef struct no ElementNode;

ElementNode *initMatrix();

ElementNode *allocHeader(int i, int j);

void insertElement(ElementNode *matrix, int value, int i, int j);

void removeElement(ElementNode *matrix, int i, int j);

void printarMatriz(ElementNode *matriz, ElementNode *ref, int row, FILE **file);

void printarCol(ElementNode *col, ElementNode *ref);

ElementNode *isInMatrix(ElementNode *matrix, int col, int row);
void removeZero(ElementNode *matrix, int i);