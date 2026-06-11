#include "definicoes.h"

int main(int argc, char* argv[]) {
    char* caminho_arquivo = NULL;

    if (argc > 1) {
        caminho_arquivo = argv[1];
        arquivo_fonte = fopen(caminho_arquivo, "r");
    } else {
        caminho_arquivo = "src/programa.txt";
        arquivo_fonte = fopen(caminho_arquivo, "r");
        if (arquivo_fonte == NULL) {
            caminho_arquivo = "src/portugol.txt";
            arquivo_fonte = fopen(caminho_arquivo, "r");
        }
    }

    if (arquivo_fonte == NULL) {
        printf("Erro ao abrir arquivo de entrada (tentado 'src/programa.txt' e 'src/portugol.txt').\n");
        return 1;
    }

    // Variável global para armazenar o token atual
    Token tokenAtual;
    int ordem = 1;
    printf("Iniciando Analisador Lexico usando o arquivo: %s\n", caminho_arquivo);
    printf("--------------------------------------------------------------------------------\n");
    printf("%6s | %-29s | %-20s | %s\n", "Ordem", "Token (Enum)", "Lexema (Texto)", "Pos. Tabela");
    printf("--------------------------------------------------------------------------------\n");

    // Loop para ler os tokens
    do {
        tokenAtual = getToken();  
        
        char posStr[10] = "-";
        if (tokenAtual.tablePosition != -1) {
            sprintf(posStr, "%d", tokenAtual.tablePosition);
        }

        // Se o token for uma string com aspas/quebras, podemos escapar ou apenas imprimir de forma limpa
        printf("%6d | %-29s | %-20s | %s\n", 
               ordem++, 
               nomeToken(tokenAtual.code), 
               tokenAtual.lexema, 
               posStr);
    } while (tokenAtual.code != TOKEN_EOF);

    fclose(arquivo_fonte);

    printf("\n--------------------------------------------------------------------------------\n");
    printf("--- Tabela de Simbolos ---\n");
    printf("--------------------------------------------------------------------------------\n");
    imprimirTabelaSimbolos();

    return 0;
}
