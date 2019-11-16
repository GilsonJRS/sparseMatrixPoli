#include <stdio.h>
#include "sparse_matrix.h"
int main(){
    ElementNode *matriz = initMatrix();
    
    insertElement(matriz, 9, 0,0);    
    insertElement(matriz, 8, 3,1);
    insertElement(matriz, 10, 1, 3);
    //insertElement(matriz, 7, 3,0);
    //insertElement(matriz, 24, 2,0);
    printf("%d\n", matriz->prox_col->prox_col->prox_col->prox_row->dataValue);




    /*FILE *file;
    file = fopen("files/parametros.txt", "r");
    int a, coeficiente, grau;
    char c;
    fscanf(file,"%d", &a);
    for(int i=0;i<a;i++){
        do{
            fscanf(file,"%d %d", &coeficiente, &grau);
            printf("%d %d ", coeficiente, grau);
        }while((c = fgetc(file))!='\n');  
        printf("\n");       
    }*/
}
/*

                ElementNode *new_element = allocElement(value, i, j), *new_col=allocHeader(-1, j),
                *aux_row_col;
                new_col->prox_col = aux_col->prox_col;
                
                aux_col->prox_col = new_col;
                
                new_col->prox_row = new_element;
                
                //verify if the line i exist in the matrix
                //aux_row_colum = matrix;
                while(aux_row_colum!=matrix){
                    if(aux_row_colum->row == i){
                        aux_row_col = aux_row_colum;
                        while(aux_row_col->prox_col->col < j){
                            aux_row_col = aux_row_col->prox_col;
                        }
                        aux_row_col->prox_col = new_element;
                        new_element->prox_col = aux_row_colum;
                        break;
                    }
                    else if(aux_row_colum->prox_row->row > i){
                        ElementNode *new_row_1 = allocHeader(i, -1);

                        new_row_1->prox_col = new_element;
                        new_row_1->prox_row = aux_row->prox_row;
                        aux_row->prox_row = new_row_1;
                        new_element->prox_col = new_row_1;
                    }//mudar == matrix
                    else if(aux_row_colum->prox_row == aux_row){
                        ElementNode *new_row_1 = allocHeader(i, -1);

                        new_row_1->prox_row = matrix;
                        new_row_1->prox_col = new_element;
                        aux_row->prox_row = new_row_1;
                    }
                    aux_row_colum=aux_row_colum->prox_row;
                }
                */