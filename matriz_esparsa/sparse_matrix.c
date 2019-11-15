#include "sparse_matrix.h"

/*
    initialize a matrix
*/
ElementNode *initMatrix(){
    ElementNode *head = (ElementNode *)malloc(sizeof(ElementNode));
    head->col = -1;
    head->row = -1;
    head->dataValue = -1;
    head->prox_row = NULL;
    head->prox_col = NULL;
    return head;
}

/*
    alloc a element, with value value, at (x,y) = (i,j)
*/

ElementNode *allocElement(int value, int i, int j){
    ElementNode *newElement = (ElementNode *)malloc(sizeof(ElementNode));
    newElement->dataValue = value;
    newElement->row = i;
    newElement->col = j;
    return newElement;
}

/*
    alloc a header element, (x,y) = (i, j)
    header of colum = (-1, j)
    header of rows = (i, -1)
*/
ElementNode *allocHeader(int i, int j){
    ElementNode *newElement = (ElementNode *)malloc(sizeof(ElementNode));
    newElement->dataValue = -1;
    newElement->row = i;
    newElement->col = j;
    newElement->prox_col = NULL;
    newElement->prox_row = NULL;
    return newElement;
}

void insertElement(ElementNode *matrix, int value, int i, int j){

    //first add
    if(matrix->prox_row == NULL && matrix->prox_col == NULL){
        ElementNode *new_row = allocHeader(i, -1),*new_col = allocHeader(-1, j), 
        *new_element = allocElement(value, i , j);
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

    }
    else{//another adds or replace
        ElementNode *aux_col = matrix->prox_col;
        ElementNode *aux_row;

        while(aux_col!=matrix){
            //colum exist
            if(aux_col->col == i){
                aux_row = aux_col;
                while(aux_row!=aux_col){
                    //row exists
                    if(aux_row->row == j){
                        aux_row->dataValue = value;
                    }
                    //add between two nodes
                    else if(aux_row->prox_row->row > j){
                        ElementNode *new_element = allocElement(value, i, j);
                        new_element->prox_row = aux_row->prox_row;
                        aux_row->prox_row = new_element;

                    }
                    //else if desnecessauro? pensar depois
                    else if(aux_row->prox_row == aux_row){
                        ElementNode *new_row_1 = allocHeader(i, -1), *new_element = allocElement(value, i, j), *aux_row_1 = aux_row;
                        new_element->prox_row = aux_row->prox_row;
                        aux_row->prox_row = new_element;
                        while(aux_row_1->prox_col!=-1){
                            aux_row_1 = aux_row_1->prox_col;
                        }
                    }

                    aux_row = aux_row->prox_row;
            }
                break;
            }
            /*
                colum don't exist and the aux reaches a node
                larger than the new 
            */
            else if(aux_col->IndexValue > i){
                
            }
            //go to next col
            aux_col = aux_col->prox_col;
            aux_col_prev = aux_col;
        }
    }
}