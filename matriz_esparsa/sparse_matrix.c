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
                        ElementNode *new_element = allocElement(value, i, j), *aux_row_1 = aux_row, *new_row_1 = allocHeader(i, -1);
                        new_element->prox_row = aux_row->prox_row;
                        aux_row->prox_row = new_element;
                        while(aux_row_1->prox_col!=-1){
                            aux_row_1 = aux_row_1->prox_col;
                        }
                        new_row_1->prox_row = aux_row_1->prox_row;
                        aux_row_1->prox_row = new_row_1;
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
                ElementNode *new_element = allocElement(value, i, j), *new_col=allocHeader(-1, j),
                *aux_row=matrix->prox_row;
                new_col->prox_col = aux_col->prox_col;
                aux_col->prox_col = new_col;
                new_col->prox_row = new_element;

                //verify if the line i exist in the matrix
                while(aux_row!=matrix){
                    if(aux_row->row == i){
                        while(aux_row->prox_col!=aux_row){
                            
                            aux_row = aux_row->prox_col;
                        }
                    }
                    else if(aux_row->prox_row->row > i){
                        ElementNode *new_row_1 = allocHeader(i, -1);
                        new_row_1->prox_col = new_element;
                        new_row_1->prox_row = aux_row->prox_row;
                        aux_row->prox_row = new_row_1;
                        new_element->prox_col = new_row_1;
                    }
                    else if(aux_row->prox_row == aux_row){
                        ElementNode *new_row_1 = allocHeader(i, -1);
                        new_row_1->prox_row = matrix;
                        new_row_1->prox_col = new_element;
                        aux_row->prox_row = new_row_1;
                    }
                    aux_row = aux_row->prox_row;
                }

            }

            /*
                reaches the end of the col list
            */
            else if(aux_col->prox_col == matrix){
                ElementNode *new_element = allocElement(value, i, j), *new_col = allocHeader(-1, j);
                new_col->prox_col = matrix;
                aux_col->prox_col = new_col;

            }

            //go to next col
            aux_col = aux_col->prox_col;
        }
    }
}

void removeElement(ElementNode *matrix, int i, int j){
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

char* first_equation_to_string(){
    FILE *arq = fopen("equacoes.txt", "r");

    if(arq == NULL)
        exit(1);
    int tam_equacao = 0;
    char *equacao = NULL, c;
    //percorre o arquivo até o primeiro /n
    do{
        c = fgetc(arq);
        if(c != '\n'){
            tam_equacao++;  
            equacao = realloc(equacao, tam_equacao*sizeof(char));
            if(equacao == NULL)
                exit(1);
            *(equacao+(tam_equacao-1)) = c;
        }
    }while(c != '\n');
    
    equacao = realloc(equacao, (tam_equacao+1)*sizeof(char));
    *(equacao+tam_equacao) = '\0';
    fclose(arq);

    return equacao;
}

int Pot10(int i){
    if(i == 0)
        return 1;
    int potencia10=1;
    while(i>0){
        potencia10 = potencia10*10;
        i--;
    }
    return potencia10;
}

void Store_Values_MatrizEsparsa(char *equacao, int *size_from_start){
    int posicao = 0, num, pot10, coeficiente;
    //percorre a string até achar '\0'
    while(*(equacao+*(size_from_start)) != '\0'){
        //reset das variaveis
        num = 0;
        coeficiente = 0;
        posicao = 0;
        pot10 = 0;
        //Percorre a string até achar o proximo espaço para transformar o valor em inteiro
        while(*(equacao+posicao+*(size_from_start)) != ' ' && *(equacao+posicao+*(size_from_start)) != '\0'){
            posicao++;
        }
        //para transformar o valor em uma posicao valida dentro do vetor
        for(int aux = (posicao-1); aux >= 0; aux--){    
            num = num + (*(equacao+aux+*(size_from_start))-'0')*Pot10(pot10);
            pot10++;
            //printf("NUM = %d\n", num);
        }
        //Pular a posicao do espaco que pode aparecer no posicao = posicao+1;
        if(*(equacao+posicao+*(size_from_start)) == ' ')
            posicao++;
        *(size_from_start) = *(size_from_start) + posicao;

        posicao = 0;
        pot10 = 0;

        //Percorre a string até achar o proximo espaço para transformar o valor em inteiro
        while(*(equacao+posicao+*(size_from_start)) != ' ' && *(equacao+posicao+*(size_from_start)) != '\0')
            posicao++;
        //printf("posicao = %d\n", posicao);
        //para transformar o valor em uma posicao valida dentro do vetor
        for(int aux = (posicao-1); aux >= 0; aux--){    
            coeficiente = coeficiente + (*(equacao+aux+*(size_from_start))-'0')*Pot10(pot10);
            pot10++;
            //printf("NUM = %d\n", num);
        }
        //Pular a posicao do espaco que pode aparecer no posicao = posicao+1;
        if(*(equacao+posicao+*(size_from_start)) == ' ')
            posicao++;
        *(size_from_start) = *(size_from_start) + posicao;

        printf("NUM = %d, COEFICIENTE = %d\n", num, coeficiente);
        //size_from_start vai até o \0 da string e retorna na main para usar o fseek.
        //funcao inserir
    }
}                                                                           

void read_equations(){
    FILE *arq = fopen("equacoes.txt", "r");
    char *equacao = first_equation_to_string();
    int size_equacao=0, num, coeficiente;

    //GUARDAR EQUACAO NA MATRIZ ESPARSA
    Store_Values_MatrizEsparsa(equacao, &size_equacao);
    fseek(arq, size_equacao+1, SEEK_SET);//size_equacao+1 para ele pular a linha   
    do{
        fscanf(arq,"%d %d",&num,&coeficiente);
        printf("\nOS VALORES SAO: %d e %d\n", num, coeficiente);
        //soma e subtracao
    }while(!(feof(arq)));


    //
    //converter string em numero

        /*PARA SOMA E SUBTRAÇÃO MELHOR LOGICA BY GILSON DAS MÃES MAGICAS.
        fscanf(arq, "%d %d", &num, &coeficiente);
    }while(feof(arq) == 0);*/
}