#include "sparse_matrix.h"

/*
    initialize a matrix
*/
ElementNode *initMatrix(){
    ElementNode *head = (ElementNode *)malloc(sizeof(ElementNode));
    head->col = -1;
    head->row = -1;
    head->dataValue = -1;
    head->prox_row = head;
    head->prox_col = head;
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
    //first ad
    if(matrix->prox_row == matrix && matrix->prox_col == matrix){
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
        ElementNode *aux_col = matrix, *aux_col_2 = matrix;
        //aux_row_colum used for rows
        ElementNode *aux_row, *aux_row_colum;
        do{
            //colum exist
            if(aux_col->col == j){
                aux_row_colum = matrix;
                do{
                    //row exists
                    if(aux_row_colum->row == i){
                        ElementNode *aux_col_3 = aux_row_colum;
                        while(aux_col_3->col <= j && aux_col_3->prox_col != aux_row_colum){
                            aux_col_3=aux_col_3->prox_col;
                        }
                        if(aux_col_3->col == j){
                            aux_col_3->dataValue = value;    
                        }else{
                            ElementNode *new_node = allocElement(value, i, j),
                            *node_aux_col = aux_col;
                            while(node_aux_col->prox_row->row < i && node_aux_col->prox_row!=aux_col){
                                node_aux_col=node_aux_col->prox_row;
                            }
                            new_node->prox_row = node_aux_col->prox_row;
                            node_aux_col->prox_row = new_node;
                            new_node->prox_col = aux_col_3->prox_col;
                            aux_col_3->prox_col = new_node;
                        }
                        break;
                    }
                    //add between two nodes
                    else if(aux_row_colum->prox_row->row > i){
                        
                        ElementNode *new_element = allocElement(value, i, j), *new_row_1 = allocHeader(i, -1);
        
                        new_element->prox_row = aux_col->prox_row;
                        aux_col->prox_row = new_element;
                        new_row_1->prox_row = aux_row_colum->prox_row;
                        aux_row_colum->prox_row = new_row_1;
                        new_row_1->prox_col = new_element;
                        new_element->prox_col = new_row_1;
                        break;
                    }
                    //else if desnecessario? pensar depois
                    else if(aux_row_colum->prox_row == matrix){
                        ElementNode *new_row_1 = allocHeader(i, -1), *new_element = allocElement(value, i, j),
                        *aux_col_3=aux_col;
                        while(aux_col_3->prox_row!=aux_col){
                            aux_col_3=aux_col_3->prox_row;
                        }
                        aux_col_3->prox_row = new_element;
                        new_element->prox_row = aux_col;
                        aux_row_colum->prox_row = new_row_1;
                        new_row_1->prox_row = matrix;
                        new_row_1->prox_col = new_element;
                        new_element->prox_col = new_row_1;

                        break;
                    }
                    aux_row_colum = aux_row_colum->prox_row;
                }while(aux_row_colum!=matrix);
                break;
            }
            /*
                colum don't exist and the aux reaches a node
                larger than the new 
            */
            else if(aux_col->prox_col->col > j){
                
                ElementNode *new_element = allocElement(value, i, j), *new_col=allocHeader(-1, j),
                *aux_row_col;

                new_col->prox_col = aux_col->prox_col;
                aux_col->prox_col = new_col;
                new_col->prox_row = new_element;
                new_element->prox_row = new_col;
                
                /*
                    verify if the line i exist in the matrix
                */
                aux_row_colum = matrix;
                do{;
                    if(aux_row_colum->row == i){
                        aux_row_col = aux_row_colum;
                        while(aux_row_col->prox_col->col < j){
                            aux_row_col = aux_row_col->prox_col;
                        };
                        new_element->prox_col = aux_row_col->prox_col;
                        aux_row_col->prox_col = new_element;
                        break;
                    }
                    else if(aux_row_colum->prox_row->row > i){
                        ElementNode *new_row_1 = allocHeader(i, -1);

                        new_row_1->prox_col = new_element;
                        new_row_1->prox_row = aux_row_colum->prox_row;
                        aux_row_colum->prox_row = new_row_1;
                        new_element->prox_col = new_row_1;
                        break;
                    }
                    else if(aux_row_colum->prox_row == matrix){
                        ElementNode *new_row_1 = allocHeader(i, -1);

                        new_row_1->prox_row = matrix;
                        new_row_1->prox_col = new_element;
                        aux_row_colum->prox_row = new_row_1;
                        new_element->prox_col = new_row_1;
                        break;
                    }
                    aux_row_colum=aux_row_colum->prox_row;
                }while(aux_row_colum!=matrix);
                break;
            }
            
            /*
                reaches the end of the col list
            */
            else if(aux_col->prox_col == matrix){
                
                ElementNode *new_element = allocElement(value, i, j), *new_col = allocHeader(-1, j),
                *aux_row_1 = matrix;
                
                new_col->prox_col = matrix;
                aux_col->prox_col = new_col;
                new_col->prox_row = new_element;
                new_element->prox_row = new_col;
                /*
                    verify the existence of the row i
                */
                do{
                    //row exist, so link with new element
                    if(aux_row_1->row == i){
                        ElementNode *aux_row_2 = aux_row_1;
                        while(aux_row_2->col < j && aux_row_2->prox_col != aux_row_1){
                            aux_row_2=aux_row_2->prox_col;
                        }
                        aux_row_2->prox_col = new_element;
                        new_element->prox_col = aux_row_1;
                        break;
                    }
                    /*
                        finds a row bigger than i
                    */
                    else if(aux_row_1->prox_row->row > i){
                        ElementNode *new_row = allocHeader(i, -1);
                        aux_row_1->prox_row = new_row;
                        new_row->prox_row = aux_row_1;
                        new_row->prox_col = new_element;
                        new_element->prox_col = new_row;
                        break;
                    }
                    /*
                        reaches the end of row's list and don't find i
                    */
                    else if(aux_row_1->prox_row == matrix){
                        ElementNode *new_row = allocHeader(i, -1);
                        aux_row_1->prox_row = new_row;
                        new_row->prox_row = matrix;
                        new_row->prox_col = new_element;
                        new_element->prox_col = new_row;
                        break;
                    }
                    aux_row_1 = aux_row_1->prox_row;
                }while(aux_row_1 != matrix);
                break;
            }

            //go to next col
            aux_col = aux_col->prox_col;
        }while(aux_col!=matrix);
    }
}
/*
ElementNode *isInMatrix(ElementNode *matrix,int col, int row){
    ElementNode *aux_col;
    if(row == 0){
        aux_col = matrix->prox_row->prox_col;
        while(aux_col!=matrix->prox_row && aux_col->col!=col){
            aux_col=aux_col->prox_col;
        }
        if(aux_col==matrix->prox_row) return NULL;
        if(aux_col->col == col){
            
            return aux_col->prox_row;
        }
        return NULL;
    }else if(row == 1){
        aux_col = matrix->prox_row->prox_row->prox_col;
        while(aux_col!=matrix->prox_row->prox_row && aux_col->col!=col){
            aux_col=aux_col->prox_col;
        }
        if(aux_col==matrix->prox_row->prox_row) return NULL;
        if(aux_col->col == col){
            return aux_col->prox_row->prox_row;
        }
        return NULL;
    }
}*/

ElementNode *isInMatrix(ElementNode *matrix,int col, int row){
    ElementNode *aux_col = matrix->prox_col;
    while(aux_col!=matrix && aux_col->col!=col){
        aux_col=aux_col->prox_col;
    }
    if(aux_col==matrix) return NULL;
    if(row == 0){
        if(aux_col->prox_row->row == 0){
            return aux_col->prox_row;
        }
        return NULL;
    }else if(row == 1){
        if(aux_col->prox_row->prox_row->row == 1){ 
            return aux_col->prox_row->prox_row;
        }else if(aux_col->prox_row->row == 1){
            return aux_col->prox_row;
        }
        return NULL;
    }
    
}

void printarMatriz(ElementNode *matriz, ElementNode *ref, int row, FILE **file){
    if(matriz == ref || matriz == NULL){
        //printf("\n");
        fprintf(*file, "\n");
        return;
    }else{
        printarMatriz(matriz->prox_col, ref, row, file);
        if(row == 0){
            if(matriz->prox_row->row == 0){
                //printf("%d %d ",matriz->prox_row->dataValue, matriz->col);
                fprintf(*file, "%d %d ", matriz->prox_row->dataValue, matriz->col);
            }
        }else{
            if(matriz->prox_row->prox_row->row == 1){
                //printf("%d %d ",matriz->prox_row->prox_row->dataValue, matriz->col);
                fprintf(*file, "%d %d ", matriz->prox_row->prox_row->dataValue, matriz->col);
            }else if(matriz->prox_row->row == 1){
                //printf("%d %d ",matriz->prox_row->dataValue, matriz->col);
                fprintf(*file, "%d %d ", matriz->prox_row->dataValue, matriz->col);
            }
        }
    }
}

/*
void removeElement(ElementNode *matrix, int i, int j){
    ElementNode *percorre = matrix;

    while(percorre->prox_col->col < j)
        percorre = percorre->prox_col;
    while(percorre->prox_row->row < i)
        percorre = percorre->prox_row;

    ElementNode *remove = percorre->prox_col->prox_row;

    //verifica se o remover é realmente o elemento a ser removido, pq as vezes após remover algum elemento ele pode "bugar". Então,
    //se o método de busca padrão nao funcionar (caminhar pela coluna e depois pela linha), ele faz o inverso, caminha pela linha e depois coluna. 
 
    if(remove->col != j || remove->row != i){
        percorre = matrix;
        while(percorre->prox_row->row < i)
            percorre = percorre->prox_row;
        while(percorre->prox_col->col < j)
            percorre = percorre->prox_col;
        remove = percorre->prox_row->prox_col;
    }

    percorre->prox_row->prox_col = remove->prox_col;
    percorre->prox_col->prox_row = remove->prox_row;
    free(remove);
    //eliminando coluna j se estiver vázia
    percorre = matrix;
    while(percorre->prox_col->col < j)
        percorre = percorre->prox_col;
    //verifica o header da coluna j aponta para ele mesmo
    if(percorre->prox_col->prox_row == percorre->prox_col){
        remove = percorre->prox_col;
        percorre->prox_col = remove->prox_col;
        free(remove);
    }
    //eliminando a linha i se estiver vázia
    percorre = matrix;
    while(percorre->prox_row->row < i)
        percorre = percorre->prox_row;
    //verifica o header da linha i aponta para ele mesmo
    if(percorre->prox_row->prox_col == percorre->prox_row){
        remove = percorre->prox_row;
        percorre->prox_row = remove->prox_row;
        free(remove);
    }
}



          |
    C -> [0] - > [1] -> [2]
    |     |       |      |
   [0]-> [ ] - > [X] -> [ ]
    |     |       |      |
   [1]-> [ ] - > [X] -> [ ]
*/
/*
void removeElement(ElementNode *matrix, int i, int j){
    ElementNode *aux_col = matrix, *general_aux, *remove;
    while(aux_col->prox_col->col < j){
        aux_col = aux_col->prox_col;
    }
    
    if(i == 0){
        general_aux = matrix->prox_row;
        while(general_aux->prox_col->col != j){
            general_aux=general_aux->prox_col;
        }
        remove = general_aux->prox_col;
        general_aux->prox_col = remove->prox_col;
        aux_col->prox_col->prox_row = remove->prox_row;
        free(remove);
    }else{
        general_aux = matrix->prox_row->prox_row;
        while(general_aux->prox_col->col != j){
            general_aux=general_aux->prox_col;
        }
        remove = general_aux->prox_col;
        if(aux_col->prox_col->prox_row != remove){
            aux_col->prox_col->prox_row->prox_row = aux_col->prox_col;
        }
        general_aux->prox_col = remove->prox_col;
        free(remove);
    }
}*/

void removeZero(ElementNode *matrix, int i){
    ElementNode *aux_col = (i==0) ? matrix->prox_row : matrix->prox_row->prox_row,
    *aux_col_2 = matrix, *remove;
    if(i == 0){
        while(aux_col->prox_col != matrix->prox_row){
            if(aux_col->prox_col->dataValue == 0){
                remove = aux_col->prox_col;
                aux_col->prox_col = remove->prox_col;
                aux_col_2->prox_col->prox_row = remove->prox_row;
                free(remove);
                if(aux_col_2->prox_col->prox_row == aux_col_2->prox_col){
                    remove = aux_col_2->prox_col;
                    aux_col_2->prox_col = aux_col_2->prox_col->prox_col;
                    free(remove);
                }
            }
            aux_col = aux_col->prox_col;
            aux_col_2 = aux_col_2->prox_col;
        }
    }else{
        while(aux_col->prox_col != matrix->prox_row->prox_row){
            if(aux_col->prox_col->dataValue == 0){
                remove = aux_col->prox_col;
                aux_col->prox_col = remove->prox_col;
                if(aux_col_2->prox_col->prox_row->row == 0){
                    aux_col_2->prox_col->prox_row->prox_row = aux_col_2->prox_col;
                }else if(aux_col_2->prox_col->prox_row->row == 1){
                    aux_col_2->prox_col->prox_row = aux_col_2->prox_col;
                }
                free(remove);
                if(aux_col_2->prox_col->prox_row == aux_col_2->prox_col){
                    remove = aux_col_2->prox_col;
                    aux_col_2->prox_col = aux_col_2->prox_col->prox_col;
                    free(remove);
                }
            }
            aux_col = aux_col->prox_col;
            aux_col_2 = aux_col_2->prox_col;
        }
    }
    
}