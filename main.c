#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

#define MAX_PALAVRA 20
#define MAX_TENTATIVA 8
#define NUM_TEMAS 3

void limpaTela() {
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
void exibirTentativasRestantes(int tentativas){
    printf("Tentativas restantes: %d\n", MAX_TENTATIVA - tentativas);
}

void exibirErros(const char* letrasErradas,int numeroLetrasErradas){

    printf("Letras erradas: ");
    for (int i = 0; i < numeroLetrasErradas; ++i) {
        printf("%c",letrasErradas[i]);

    }
    printf("\n");

}

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

    for (int i = 0; i <= palavraAleatoria; i++) {
        fgets(palavraSecreta, sizeof(palavraSecreta), arquivo);
    }

    tamanhoPalavra = strlen(palavraSecreta);
    if (palavraSecreta[tamanhoPalavra - 1] == '\n'){
        palavraSecreta[tamanhoPalavra - 1] = '\0';
        tamanhoPalavra--;
    }
    fclose(arquivo);

    char palavraEscondida[MAX_PALAVRA];
    for (int i = 0; i < tamanhoPalavra; i++) {
        palavraEscondida[i] = '_';
    }
    palavraEscondida[tamanhoPalavra] = '\0';


    char letraErrada[MAX_TENTATIVA];
    int numeroLetrasErradas = 0;


    while (tentativas < MAX_TENTATIVA && letrasDescobertas < tamanhoPalavra){
        limpaTela();
        exibirPalavra(palavraEscondida, tamanhoPalavra);
        exibirTentativasRestantes(tentativas);
        exibirErros(letraErrada, numeroLetrasErradas);

        printf("Informe uma letra: ");
        scanf("%c", &letra);
        letra = toupper(letra);


        int letrasEncontradas = 0;

        for (i = 0; i < tamanhoPalavra; ++i) {
            if(toupper(palavraSecreta[i]) == letra && palavraEscondida[i] == '_'){
                palavraEscondida[i] = palavraSecreta[i];
                letrasDescobertas++;
                letrasEncontradas = 1;
            }

        }

        if (!letrasEncontradas){
            int letraJaTentada = 0;
            for (int i = 0; i < numeroLetrasErradas; ++i) {
                if(letraErrada[i] == letra){
                    letraJaTentada = 1;
                    break;
                }

            }
            if(!letraJaTentada){
                letraErrada[numeroLetrasErradas] = letra;
                numeroLetrasErradas++;
                tentativas++;
            }
        }

    }
    limpaTela();
    exibirPalavra(palavraEscondida, tamanhoPalavra);


    if (letrasDescobertas == tamanhoPalavra) {
        printf("Parabéns, você acertou a palavra secreta!");
    }else{
        printf("Você perdeu, meu camaradaaaaaaa! A palavra secreta era %s\n", palavraSecreta);
    }
    return 0;
}


