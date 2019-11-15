#include "sparse_matrix.h"

SparseMatrix *initMatrix(){
    SparseMatrix *head = (SparseMatrix *)malloc(sizeof(SparseMatrix));
    head->col = 0;
    head->row = 0;
    head->prox_row = NULL;
    head->prox_col = NULL;
    return head;
}

HeaderNode *allocHeader(int index){
    HeaderNode *newRow = (HeaderNode *)malloc(sizeof(HeaderNode));
    newRow->IndexValue = index;
    newRow->prox_row = NULL;
    newRow->prox_col = NULL;
    return newRow;
}

ElementNode *allocElement(int value, int i, int j){
    ElementNode *newElement = (ElementNode *)malloc(sizeof(ElementNode));
    newElement->value = value;
    newElement->row = i;
    newElement->col = j;
    return newElement;
}

void insertElement(SparseMatrix *matrix, int value, int i, int j){
    //first add
    if(matrix->prox_row == NULL && matrix->prox_col == NULL){
        HeaderNode *new_row = allocHeader(i),*new_col = allocHeader(j);
        ElementNode *new_element = allocElement(value, i , j);
        //change header's pointers
        new_row->prox_row = matrix;
        new_row->prox_col = new_element;
        new_col->prox_col = matrix;
        new_col->prox_row = new_element;
        //change element's pointers
        new_element->prox_row = new_col;
        new_element->prox_col = new_row;
        //change matrix's pointers
        matrix->prox_col = new_col;
        matrix->prox_row = new_row;

    }else{//another adds or replace
        HeaderNode *aux_col = matrix->prox_col;
        ElementNode *aux_row;

        while(aux_col!=matrix){

            //colum exist
            if(aux_col->IndexValue == i){
                aux_row = aux_col;
                while(aux_row!=aux_col){

                    //row exists
                    if(aux_row->row == j){
                        aux_row->dataValue = value;
                    }

                    aux_row = aux_row->prox_row;
                }
                break;
            }
        }
    }
}