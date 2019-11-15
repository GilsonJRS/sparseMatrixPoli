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
            if(aux_col->col == j){
                aux_row = aux_col;
                while(aux_row!=aux_col){
                    //row exists
                    if(aux_row->row == i){
                        aux_row->dataValue = value;
                    }
                    //add between two nodes
                    else if(aux_row->prox_row->row > i){
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
                        new_row_1->prox_row = aux_row_1->prox_row;
                        aux_row_1->prox_row = new_row_1;

                    }
                    aux_row = aux_row->prox_row;
                }   
            }
            /*
                colum don't exist and the aux reaches a node
                larger than the new 
            */
            else if(aux_col->prox_col->col > j){
                ElementNode()
            }
            //go to next col
            aux_col = aux_col->prox_col;
            aux_col_prev = aux_col;
        }
    }
}


void removeElement(SparseMatrix *matrix, int i, int j){
    ElementNode *percorre = matrix;

    while(percorre->col < j)
        percorre = percorre->prox_col;
    //verifica se a linha existe
    if(percorre->col == j){
        //percorre a matriz verticalmente
        while(percorre->row < i)
            percorre = percorre->prox_row;
            //verifica se a coluna existe e remove o elemento
        if((percorre->prox_row)->row == i){
            ElementNode *remove = percorre->prox_row;
            percorre->prox_row = (percorre->prox_row)->prox_row;
            free(remove);
            //verifica se a linha está vazia. (se o header aponta para si próprio)
            if(percorre->prox_col == percorre){
                //remove aquela linha, pois tem mais nenhum elemento
                percorre = matrix;
                //encontra linha i
                while((percorre->prox_row)->row != i)
                    percorre = percorre->prox_row;
                ElementNode *remove = percorre->prox_row;
                percorre->prox_row = (percorre->prox_row)->prox_row;
                free(remove);                
            }
            percorre = matrix;
            //encontra coluna j
            while((percorre->prox_col)->col != j)
                percorre = percorre->prox_col;
            //se tiver sem elementos remove a coluna
            if((percorre->prox_col)->prox_row == percorre->prox_col){
                ElementNode *remove = percorre->prox_col;
                percorre->prox_col = (percorre->prox_col)->prox_col;
                free(remove);
            }
        }
    }
}

void read_equations(){
    FILE *arq = fopen("equacoes.txt", "r");
    int i=0;
    if(fp == NULL)
        exit(1);
    do{
        char equacao[]
        fscanf(arq, "%s", equacao);
        i++;
        printf("O valor de i eh: %d", i);
    }while(EOF(arq));
}
