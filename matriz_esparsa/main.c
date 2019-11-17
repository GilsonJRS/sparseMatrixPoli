#include <stdio.h>
#include "sparse_matrix.h"
int main(){
    ElementNode *matriz = initMatrix();
    
    insertElement(matriz, 8, 0, 91234);
    insertElement(matriz, 2, 0, 67);
    insertElement(matriz, 3, 0, 45);
    insertElement(matriz, 3, 0, 9);
    insertElement(matriz, 56, 0, 3);
    insertElement(matriz, 1, 0, 0);
    
    insertElement(matriz, 34, 1, 91234);
    insertElement(matriz, 78, 1, 6754);
    insertElement(matriz, -8, 1, 45);
    printf("%d\n", matriz->prox_col->prox_col->prox_col->prox_col->prox_row->prox_row->dataValue);
    //printarMatriz(matriz->prox_col, matriz);
    /*
   
    FILE *file;
    file = fopen("files/parametros.txt", "r");
    int a, coeficiente, grau, u=0;
    char c;
    fscanf(file,"%d", &a);
    for(int i=0;i<a;i++){
        do{
            fscanf(file,"%d %d", &coeficiente, &grau);
            printf("%d %d\n", coeficiente, grau);
            insertElement(matriz, coeficiente, u, grau);
        }while((c = fgetc(file))!='\n');  
        printf("\n");
        u++;
    }*/
}
