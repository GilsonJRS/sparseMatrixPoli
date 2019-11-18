#include <stdio.h>
#include "sparse_matrix.h"
int main(){
    ElementNode *matriz = initMatrix();
    FILE *file;
    file = fopen("files/parametros3.txt", "r");
    int a, coeficiente, grau, u=0;
    char c;
    ElementNode *is;
    fscanf(file,"%d", &a);
    for(int i=0;i<a;i++){
        if(i == 0){
            do{
                fscanf(file,"%d %d", &coeficiente, &grau);
                //printf("%d %d\n", coeficiente, grau);
                insertElement(matriz, coeficiente, 0, grau);
                insertElement(matriz, coeficiente, 1, grau);
            }while((c = fgetc(file))!='\n');
        }else{
            do{
                fscanf(file,"%d %d", &coeficiente, &grau);
                is = isInMatrix(matriz, grau, 0);
                if(is!=NULL){
                    is->dataValue += coeficiente; 
                    is->prox_row->dataValue -= coeficiente;    
                }else{
                    insertElement(matriz, coeficiente, 0, grau);
                    insertElement(matriz, (-1)*coeficiente, 1, grau);
                }
            }while((c = fgetc(file))!='\n');
        }
    }
    printarMatriz(matriz->prox_col, matriz, 0);
    printf("\n");
    printarMatriz(matriz->prox_col, matriz, 1);
    printf("\n");
}
