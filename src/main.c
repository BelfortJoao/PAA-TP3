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

/*
 * Generate a random number limited by to ints(the interval include the limits)
 *input:
 *      max_number int:
 *      minimum_number int:
 *output:
 *      int: random number generated
 */
int randomLimited(int max_number, int minimum_number){
    int hold =0;
    if (max_number<minimum_number){
        hold= max_number;
        max_number=minimum_number;
        minimum_number=hold;
    }
    return rand() % (max_number + 1 - minimum_number) + minimum_number;
}

/*
 * Generate a Matrix of char that are the random bases of the chosen length
 * input:
 *      nmr_bases int:
 *      nmr_elements int:
 *      resp[nmr_elements][nmr_bases]:
 * output:
 *      *:
 */
void randombases(int nmr_bases, int  nmr_elements, char resp[nmr_elements][nmr_bases]){
    char str[4][1]= {"A","C","T","G"};

    for (int i = 0; i < nmr_elements; ++i) {
        for (int j = 0; j < nmr_bases-1; ++j) {
            int ran=randomLimited(3,0);
            resp[i][j]=str[ran][0];
        }
        int status=0;
        // Evita Repetição de String
        for (int j = 0; j < i; ++j) {
            int match=0;
            for (int k = 0; k < nmr_bases-1; ++k) {
                if(resp[j][k]==resp[i][k])
                    match++;
            }
            if (match>=nmr_bases-1){
                i--;
                status=1;
                break;
            }
        }
        if(status==0) {
            resp[i][-1] = '\0';
        }
    }
    resp[nmr_elements][-1]='\0';
}

/*
 * Function to calculate the fatorial of a given number
 * input:
 *      x int:
 */
int fat(int x){
    int fat=1;
    for (int i = 1; i < x+1; ++i) {
        fat = fat * i;
    }
    return fat;
}

int main(void)
{
    //----------inicializa os arquivos-----\\

    srand((unsigned int)time(NULL));
    char* chimp[CHIMP],* human[HUMAN],* dog[DOG];
    openfile(chimp,CHIMPARC);
    openfile(human,HUMANARC);
    openfile(dog,DOGARC);

    //----------seleciona sequencia de dna aleatoria-----\\

    int rand_dog,rand_human, rand_chimp,rand_len;

    do{
        rand_human = randomLimited(HUMAN-1,ZERO);
    } while (human[rand_human]==NULL);

    do{
        rand_chimp = randomLimited(CHIMP-1,ZERO);
    } while (chimp[rand_chimp]==NULL);

    do{
        rand_dog = randomLimited(DOG-1,ZERO);
    }while(dog[rand_dog]==NULL);

    //--------------ERRO, acha a permutacao(produto cartesiano + escolha aleatoria)------------------\\

    int nmr_bases,nmr_elements;

    printf("Numero de bases:");
    scanf("%d", &nmr_bases);

    nmr_elements = randomLimited(fat(nmr_bases)*randomLimited(4,1),2);
    char strar[nmr_elements][nmr_bases + 1];
    randombases(nmr_bases + 1,nmr_elements, strar);

    for (int i = 0; i < nmr_elements; ++i) {
            printf("\n%s",strar[i]);
    }
    //------------------------Casamento de Padrões--------------------------\\


    //------------------------Similaridade de Pares---------------------------\\

    //-------------------------Simulação---------------------------------------\\

}

