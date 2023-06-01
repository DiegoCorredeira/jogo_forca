#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>



#define MAX_PALAVRA 20
#define MAX_TENTATIVA 8
#define NUM_TEMAS 3

void limpaTela(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}
void exibirPalavra(const char* palavraSecreta, int tamanhoPalavra){
    printf("Palavra: ");
    for (int i = 0; i < tamanhoPalavra; i++){
        printf("%c", palavraSecreta[i]);
    }
    printf("\n");

}

// 3 temas - País, Frutas, Animais
int main(){
    char temas[NUM_TEMAS][MAX_PALAVRA] = {
        "paises",
        "frutas",
        "animais"
    };

    char palavraSecreta[MAX_PALAVRA];
    int tamanhoPalavra;
    int tentativas = 0;
    int letrasDescobertas = 0;
    char letra;
    int i;


    int temaEscolhido;
    for(i = 0; i< NUM_TEMAS; i++){
        printf("%d. %s\n", i + 1, temas[i]);
    }
    printf("Informe o número do tema escolhido: ");
    scanf("%d", &temaEscolhido);
    temaEscolhido--;


    char nomeArquivo[MAX_PALAVRA + 4];
    snprintf(nomeArquivo, sizeof(nomeArquivo), "%s.txt", temas[temaEscolhido]);
    FILE* arquivo = fopen(nomeArquivo, "r");
    if (arquivo == NULL){
        printf("Erro ao abrir o arquivo de palavras\n");
        return 1;
    }

    int numPalavras = 0;
    char linha[MAX_PALAVRA];
    while (fgets(linha, sizeof(linha), arquivo) != NULL){
        numPalavras++;
    }

    rewind(arquivo);
    srand(time(NULL));
    int palavraAleatoria = rand() % numPalavras;

    for (int i = 0; i <= palavraAleatoria; ++i) {
        fgets(palavraSecreta, sizeof(palavraSecreta), arquivo);
    }

    tamanhoPalavra = strlen(palavraSecreta);
    if (palavraSecreta[tamanhoPalavra - 1] == "\n"){
        palavraSecreta[tamanhoPalavra - 1] = "\0";
        tamanhoPalavra--;
    }
    fclose(arquivo);



    return 0;
}


