#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define CHIMP 1682
#define DOG 820
#define HUMAN 4320
#define ZERO 0
#define PATH_ARQUIVO "../DNAs/"
#define CHIMPARC "chimpanzee.txt"
#define HUMANARC "dog.txt"
#define DOGARC "human.txt"

/*
 * Open a file to and makes etch line a string inserting it into a string array
 * Input:
 *      dna char**:
 *      file char*:
 */
void openfile(char** dna, char* file){
    FILE * fp;
    char * line = NULL;
    size_t len = ZERO;
    ssize_t read;

    char caminhoArquivo[strlen(PATH_ARQUIVO) + strlen(file) + 1];

    strcpy(caminhoArquivo, PATH_ARQUIVO);
    strcat(caminhoArquivo, file);
    fp = fopen(caminhoArquivo, "r");
    if (fp == NULL) {
        exit(EXIT_FAILURE);
    }
    int numb = ZERO;
    while ((read = getline(&line, &len, fp)) != -1) {
        dna[numb]=line;
        numb++;
    }

    fclose(fp);
    if (line) {
        free(line);
    }
}

int randomLimited(int max_number, int minimum_number){
    return rand() % (max_number + 1 - minimum_number) + minimum_number;
}

char ** randombases(int nmr_bases, int * nm_str){
    char str[]= "ACTG";
    int nmr_elements = randomLimited(nmr_bases*nmr_bases,ZERO);

    char ** resp=(char **) malloc(sizeof (char *)*nmr_elements);
    for (int i = 0; i < nmr_elements; ++i) {
        resp[i]= (char *) malloc(sizeof (char )*nmr_bases);
    }

    for (int i = 0; i < nmr_elements; ++i) {
        for (int j = 0; j < nmr_bases; ++j) {

            int ran=randomLimited(3,0);
            resp[i][j]=str[ran];
        }
    }
    printf("%d",nmr_elements);
    *nm_str=nmr_elements;
    return resp;
}

int main(void)
{
    srand((unsigned int)time(NULL));
    char* chimp[CHIMP],* human[HUMAN],* dog[DOG];
    openfile(chimp,CHIMPARC);
    openfile(human,HUMANARC);
    openfile(dog,DOGARC);

    int rand_dog,rand_human, rand_chimp,rand_len;
    rand_dog = randomLimited(DOG-1,ZERO);
    rand_chimp = randomLimited(CHIMP-1,ZERO);
    rand_human = randomLimited(HUMAN-1,ZERO);
    if(human[rand_human]==NULL){
        printf("\nFAIL\n");
    }
    //acha a permutacao
    int nmr_bases,nmr_elements;
    int *nm_ele = (int *) malloc(sizeof (int));
    *nm_ele=0;
    char** strar;
    printf("Numero de bases:");
    scanf("%d", &nmr_bases);
    strar = randombases(nmr_bases,nm_ele);
    printf("%d",*nm_ele);
    for (int i = 0; i < *nm_ele; ++i) {
        for (int j = 0; j < nmr_bases; ++j) {
            printf("%c", strar[i][j]);
        }
        printf("\n");
    }

    //PERMUTAÇÂO
}


