#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Element{
    int index;
    int value;
} Element;


int** initMatrix(int size){
    int ** matrix;
        matrix = (int **) malloc (sizeof(int *) * size);
    for(int i = 0; i < size; i++){
        matrix[i] = (int *) malloc (sizeof(int) * size);
        for (int j = 0; j < size; j++){ 
            matrix[i][j] = 0;
       }
    }
    return matrix;
}

int getElementIndex(Element *element, int value, int size){
    
    for(int i=0; i<size; i++){
        if(element[i].value == value) {
            return element[i].index;}
    }
}


int checkIfIsReflexive(int **matrix, Element *nodes, int size){
    int isReflexive = 1;
    printf("Reflexiva: ");
    for(int i = 0; i < size; i++){
        if(matrix[i][i] == 0){
            if(isReflexive == 1){
                printf("F\n");
                isReflexive = 0;
            }
            printf("(%d,%d); ", nodes[i].value, nodes[i].value);
        }
    }

    if(isReflexive){
        printf("V");
    }
    printf("\n");
    return isReflexive;
}

int checkIfIsIreflexive(int **matrix, Element *nodes, int size){
    int isIreflexive = 1;
    printf("Irreflexiva: ");
    for(int i = 0; i < size; i++){
        if(matrix[i][i] == 1){
            if(isIreflexive) {
                printf("F\n");
                isIreflexive = 0;
            }
            printf("(%d,%d); ", nodes[i].value, nodes[i].value);
        }
    }
    if(isIreflexive){
        printf("V");
    }
    printf("\n");
    return isIreflexive;
}

int checkIfIsSimetric(int **matrix, Element *nodes, int size){
    int isSimetric = 1;
    printf("Simetrica: ");
    for(int i = 0; i < size; i++){
        for(int j=0; j<=i; j++){
            if(matrix[i][j] && !matrix[j][i]){
                if(isSimetric){
                    printf("F\n");
                    isSimetric = 0;
                }
                printf("(%d,%d); ", nodes[j].value, nodes[i].value);
            }
            if(matrix[j][i] && !matrix[i][j]){
                if(isSimetric){
                    printf("F\n");
                    isSimetric = 0;
                }
                printf("(%d,%d); ", nodes[i].value, nodes[j].value);
            }
        }
    }
    if(isSimetric){
        printf("V");
    }
    printf("\n");
    return isSimetric;
}

int checkIfIsAntiSimetric(int **matrix, Element *nodes, int size){
    int isAntiSimetric = 1;
    printf("Anti-simetrica: ");
    for(int i = 0; i < size; i++){
        for(int j=0; j<i; j++){
            if(matrix[i][j] && (matrix[i][j] == matrix[j][i])){
                if(isAntiSimetric){
                    printf("F\n");
                    isAntiSimetric = 0;
                }
                printf("(%d,%d); ", nodes[i].value, nodes[j].value);
                printf("(%d,%d); ", nodes[j].value, nodes[i].value);
            }
        }
    }
    if(isAntiSimetric){
        printf("V");
    }
    printf("\n");
    return isAntiSimetric;
}

int checkIfIsAsimetric(int **matrix, Element *nodes, int size){
    int isAsimetric = 1;
    printf("Assimetrica: ");
    for(int i = 0; i < size; i++){
        for(int j=0; j<=i; j++){
            if(matrix[i][j] == matrix[j][i]){
                if(isAsimetric){
                    printf("F\n");
                    isAsimetric = 0;
                }
                printf("(%d,%d); ", nodes[i].value, nodes[j].value);
                printf("(%d,%d); ", nodes[j].value, nodes[i].value);
        }
        }
        
    }
    if(isAsimetric){
        printf("V");
    }
    printf("\n");
    return isAsimetric;
}

int checkIfIsTransitive(int **matrix, Element *nodes, int size, int willPrint){
    int isTransitive = 1;
    willPrint && printf("Transitiva: ");
    for(int i = 0; i < size; i++){
        for(int j = 0; j< size; j++){
            for(int k=0; k<size; k++){
                if(matrix[i][j] && matrix[j][k] && !matrix[i][k]){
                    if(isTransitive){
                         willPrint && printf("F\n");
                        isTransitive = 0;
                    }
                    printf("(%d,%d); ", nodes[i].value, nodes[k].value);
                    j=size-1;
                }
            }
        }
    }
    if(isTransitive){
         willPrint && printf("V");
    }
    printf("\n");
    return isTransitive;
}

void printTransitiveClosure(int** matrix,Element *nodes, int size, int isTransitive){
    printf("Fecho transitivo da relacao = ");
    for(int i=0; i<size; i++){
        for(int j=0; j<=i; j++){
            matrix[i][j] && printf("(%d,%d); ", nodes[i].value, nodes[j].value);
            (matrix[j][i] && i!=j) && printf("(%d,%d); ", nodes[j].value, nodes[i].value);
        }
    }
    !isTransitive && checkIfIsTransitive(matrix, nodes, size, 0);
}


int main() {
    FILE* input = fopen("SUBSTITUA AQUI", "r");
    char *line= malloc(50);
    fgets(line, 50, input);
    
      
    int size = line[0] - '0';
    Element *nodes = (Element *)malloc(sizeof(Element) * size);
    char *ElementValue = strtok(line, " ");
    ElementValue = strtok(NULL, " ");
    for(int i=0; ElementValue; i++){
        nodes[i].value = atoi(ElementValue);
        nodes[i].index = i;
        ElementValue = strtok(NULL, " ");
    }

    int ** matrix = initMatrix(size);


    char *source, *destiny;
    while(fgets(line, 50, input) !=NULL ) {
        source = strtok(line, " ");
        destiny = strtok(NULL, " ");
        matrix[ getElementIndex(nodes, atoi(source), size) ][  getElementIndex(nodes, atoi(destiny), size) ] = 1;
    }
    
    int isReflexive = checkIfIsReflexive(matrix, nodes, size);
    int isIreflexive = checkIfIsIreflexive(matrix, nodes, size);
    int isSimetric = checkIfIsSimetric(matrix, nodes, size);
    int isAntiSimetric = checkIfIsAntiSimetric(matrix, nodes, size);
    int isAssimetric = 1;
    if (!isIreflexive || !isAntiSimetric){
        printf("Assimetrica: F\n");
    } else {
        isAssimetric = checkIfIsAsimetric(matrix, nodes, size);
    }
    int isTransitive = checkIfIsTransitive(matrix, nodes, size, 1);
    printf("\n");
    printf("Relacao de equivalencia: ");
    (isReflexive && isSimetric && isTransitive) ? printf("V\n") : printf("F\n");
    printf("Relacao de ordem parcial: ");
    (isReflexive && isAntiSimetric && isTransitive) ? printf("V\n") : printf("F\n");
    printf("\n");

    printTransitiveClosure(matrix, nodes, size, isTransitive);

    fclose(input);
    free(input);
    free(matrix);
    return 1;
}