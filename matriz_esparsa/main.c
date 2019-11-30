#include <stdio.h>
#include "sparse_matrix.h"
int main(){
    ElementNode *matriz = initMatrix();
  /*
    FILE *file;
    insertElement(matriz, 10, 0, 10);
    insertElement(matriz, 20, 0, 20);
    insertElement(matriz, 0, 1, 10);
    insertElement(matriz, 1, 1, 20);

    removeZero(matriz, 1);
    printarMatriz(matriz->prox_col, matriz, 0, &file);
    printf("\n");
    printarMatriz(matriz->prox_col, matriz, 1, &file);
    printf("\n");
    //           
    //    C->  [10]-> [20]
    //     |    |     |     
    //    [0]-> 1 -> 20
    //     |    |     |     
    //    [1]-> 30 -> 40
    
    */
   
    FILE *file;
    char c, arquivo[22] = "files/parametros3.txt";
    file = fopen(arquivo, "r");
    int a, coeficiente, grau, u=0;
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
                    if(is->row!=-1){
                        is->dataValue += coeficiente;
                    }
                }else{
                    insertElement(matriz, coeficiente, 0, grau);
                }
                is = isInMatrix(matriz, grau, 1);
                if(is!=NULL){
                    if(is->row!=-1){
                        is->dataValue -= coeficiente;
                    }
                }else{
                    insertElement(matriz, (-1)*coeficiente, 1, grau);
                }
            }while((c = fgetc(file))!='\n');
        }
    }
    removeZero(matriz, 0);
    removeZero(matriz, 1);
    fclose(file);
    file = fopen(arquivo, "a");
    printarMatriz(matriz->prox_col, matriz, 0, &file);
    printarMatriz(matriz->prox_col, matriz, 1, &file);
    fclose(file);
}
