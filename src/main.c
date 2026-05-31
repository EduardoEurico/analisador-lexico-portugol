#include "definicoes.h"

int main() {
    // Abre o arquivo fonte
    arquivo_fonte = fopen("src/programa.txt", "r");
    if (arquivo_fonte == NULL) {
        printf("Erro ao abrir arquivo.\n");
        return 1;
    }

    // Variável global para armazenar o token atual
    Token tokenAtual;
    printf("Iniciando Analisador Lexico...\n");

    // Loop para ler os tokens
    do {
        tokenAtual = getToken();  
        printf("Token Encontrado: %d | Posicao na Tabela: %d\n", tokenAtual.code, tokenAtual.tablePosition);
    } while (tokenAtual.code != TOKEN_EOF);

    fclose(arquivo_fonte);

    printf("\n--- Tabela de Simbolos ---\n");
    imprimirTabelaSimbolos();

    return 0;
}
