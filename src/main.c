#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#define CHIMP 1682
#define DOG 820
#define HUMAN 4320
#define ZERO 0
#define CHIMPARC "./DNAs/chimpanzee.txt"
#define HUMANARC "./DNAs/dog.txt"
#define DOGARC "./DNAs/human.txt"

// função para ler um arquivo de tamanho n e retornar um vetor de char
void readFile(int n, char vector[n], char *filepath)
{
    FILE *file = fopen(filepath, "r");

    if (!file)
    {
        printf("Erro ao ler o arquivo %s, tente trocar o define de (../) para (./) ou vice-versa.", filepath);
        exit(1);
    }

    for (int i = 0; i < n; i++)
    {
        vector[i] = fgetc(file);
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
int randomLimited(int max_number, int minimum_number)
{

    int hold = 0;
    if (max_number < minimum_number)
    {
        hold = max_number;
        max_number = minimum_number;
        minimum_number = hold;
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
void randombases(int nmr_bases, int nmr_elements, char resp[nmr_elements][nmr_bases])
{
    char str[4][1] = {"A", "C", "T", "G"};

    for (int i = 0; i < nmr_elements; ++i)
    {
        for (int j = 0; j < nmr_bases - 1; ++j)
        {
            int ran = randomLimited(3, 0);
            resp[i][j] = str[ran][0];
        }
        int status = 0;
        // Evita Repetição de String
        for (int j = 0; j < i; ++j)
        {
            int match = 0;
            for (int k = 0; k < nmr_bases - 1; ++k)
            {
                if (resp[j][k] == resp[i][k])
                    match++;
            }
            if (match >= nmr_bases - 1)
            {
                i--;
                status = 1;
                break;
            }
        }
        if (status == 0)
        {
            resp[i][-1] = '\0';
        }
    }
    resp[nmr_elements][-1] = '\0';
}

/*
 * Function to calculate the fatorial of a given number
 * input:
 *      x int:
 */
int fat(int x)
{
    int fat = 1;
    for (int i = 1; i < x + 1; ++i)
    {
        fat = fat * i;
    }
    return fat;
}

// get number of pattern matching using boyer moore algorithm
int getPatternMatchingBoyerMoore(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i = m - 1;
    int j = m - 1;
    int count = 0;
    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            if (j == 0)
            {
                count++;
                i = i + m - j;
                j = m - 1;
            }
            else
            {
                i--;
                j--;
            }
        }
        else
        {
            i = i + m - j;
            j = m - 1;
        }
    }
    return count;
}

// get number of pattern matching using shift-and algorithm
int getPatternMatchingShiftAnd(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    int i = 0;
    int j = 0;
    int d[256];
    for (int k = 0; k < 256; k++)
    {
        d[k] = 0;
    }
    for (int k = 0; k < m; k++)
    {
        d[pattern[k]] = d[pattern[k]] | (1 << (m - 1 - k));
    }
    int r = 0;
    for (int k = 0; k < n; k++)
    {
        r = ((r << 1) | 1) & d[text[k]];
        if ((r & (1 << (m - 1))) != 0)
        {
            count++;
        }
    }
    return count;
}

// get number of pattern matching using kmp algorithm
int getPatternMatchingKMP(char *text, char *pattern)
{
    int n = strlen(text);
    int m = strlen(pattern);
    int count = 0;
    int i = 0;
    int j = 0;
    int *pi = (int *)malloc(m * sizeof(int));
    pi[0] = 0;
    for (int k = 1; k < m; k++)
    {
        pi[k] = 0;
        int q = pi[k - 1];
        while (q > 0 && pattern[k] != pattern[q])
        {
            q = pi[q - 1];
        }
        if (pattern[k] == pattern[q])
        {
            q++;
        }
        pi[k] = q;
    }
    while (i < n)
    {
        if (text[i] == pattern[j])
        {
            i++;
            j++;
            if (j == m)
            {
                count++;
                j = pi[j - 1];
            }
        }
        else if (j > 0)
        {
            j = pi[j - 1];
        }
        else
        {
            i++;
        }
    }
    free(pi);
    return count;
}

// sqrt
//  double sqrt(double x) {
//      double y = 1;
//      double e = 0.0000001;
//      while (x - y > e) {
//          x = (x + y) / 2;
//          y = x / y;
//      }
//      return x;
//  }

// cossine similarity function
double cossineSimilarity(int *a, int *b, int n)
{

    double sum = 0;
    double sumA = 0;
    double sumB = 0;
    for (int i = 1; i < n; i++)
    {
        sum += a[i-1] * b[i-1];
        sumA += pow(a[i-1], 2);
        sumB += pow(b[i-1], 2);
    }
    
    if (sqrt(sumA) * sqrt(sumB) == 0)
        return 0;
    double result = sum / (sqrt(sumA) * sqrt(sumB));
    return result;
}

int main(void)
{
    srand(time(NULL));

    //----------seleciona sequencia de dna aleatoria-----\\

    //----------inicializa os arquivos------------------\\


    //--------------ERRO, acha a permutacao(produto cartesiano + escolha aleatoria)------------------\\

    
    //------------------------Casamento de Padrões--------------------------\\

    printf("Escolha um dos 3 algoritmos para calcular o casamento de padrões de caracteres:\n");
    printf("1 - Boyer-Moore\n");
    printf("2 - Shift-And\n");
    printf("3 - KMP\n");
    int choice;
    scanf("%d", &choice);
    int contadorsim = 0;
    float sumHC = 0, sumHD = 0, sumCD = 0;
    int numeroSimulacoes;
    do{
        printf("Quantas simulações deseja fazer? (max 50)\n");
        scanf("%d", &numeroSimulacoes);
    } while (numeroSimulacoes > 50);
    for (int quantSim = 0; quantSim <= numeroSimulacoes; quantSim++){
        int vezesSim = randomLimited(800, 500);
        printf("Fazendo simulação para %d vezes.\n", vezesSim);
        for (int j = 0; j < vezesSim; j++)
        {
            
            int nmr_bases, nmr_elements;

            nmr_bases = randomLimited(6, 2);

            nmr_elements = randomLimited(fat(nmr_bases) * randomLimited(4, 1), 2);
            char strar[nmr_elements][nmr_bases + 1];
            randombases(nmr_bases + 1, nmr_elements, strar);

            int matchH[nmr_elements], matchC[nmr_elements], matchD[nmr_elements];

            int humanid = randomLimited(HUMAN - 1, ZERO);
            int chimpid = randomLimited(CHIMP - 1, ZERO);
            int dogid = randomLimited(DOG - 1, ZERO);

            char chimp[chimpid], human[humanid], dog[dogid];
            readFile(humanid, human, HUMANARC);
            readFile(chimpid, chimp, CHIMPARC);
            readFile(dogid, dog, DOGARC);

            for (int i = 0; i < nmr_elements; ++i)
            {
                if (choice == 1)
                {
                    matchH[i] = getPatternMatchingBoyerMoore(human, strar[i]);
                    matchC[i] = getPatternMatchingBoyerMoore(chimp, strar[i]);
                    matchD[i] = getPatternMatchingBoyerMoore(dog, strar[i]);
                }
                else if (choice == 2)
                {
                    matchH[i] = getPatternMatchingShiftAnd(human, strar[i]);
                    matchC[i] = getPatternMatchingShiftAnd(chimp, strar[i]);
                    matchD[i] = getPatternMatchingShiftAnd(dog, strar[i]);
                }
                else if (choice == 3)
                {
                    matchH[i] = getPatternMatchingKMP(human, strar[i]);
                    matchC[i] = getPatternMatchingKMP(chimp, strar[i]);
                    matchD[i] = getPatternMatchingKMP(dog, strar[i]);
                }
                else
                {
                    printf("Opção inválida!\n");
                    exit(1);
                }
            }

            //------------------------Similaridade de Pares---------------------------\\

            float simHC = cossineSimilarity(matchH, matchC, nmr_elements);
            float simHD = cossineSimilarity(matchH, matchD, nmr_elements);
            float simCD = cossineSimilarity(matchC, matchD, nmr_elements);
            sumCD += simCD;
            sumHD += simHD;
            sumHC += simHC;
        }

        float resCD = sumCD / 1000;
        float resHD = sumHD / 1000;
        float resHC = sumHC / 1000;

        printf("HC: %f,HD: %f,CD: %f\n", resHC, resHD, resCD);
    }
    

    //-------------------------Simulação---------------------------------------\\

}
