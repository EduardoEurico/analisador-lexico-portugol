#include "definicoes.h"

int verificaPalavraReservada(char* lexema) {
    // Palavras reservadas
    if (strcmp(lexema, "inicio") == 0 || strcmp(lexema, "INICIO") == 0) return TOKEN_INICIO;
    if (strcmp(lexema, "fim") == 0 || strcmp(lexema, "FIM") == 0) return TOKEN_FIM;
    if (strcmp(lexema, "inteiro") == 0 || strcmp(lexema, "INTEIRO") == 0) return TOKEN_INTEIRO;
    if (strcmp(lexema, "leia") == 0 || strcmp(lexema, "LEIA") == 0) return TOKEN_LEIA;
    if (strcmp(lexema, "imprima") == 0 || strcmp(lexema, "IMPRIMA") == 0) return TOKEN_IMPRIMA;
    if (strcmp(lexema, "escreva") == 0 || strcmp(lexema, "ESCREVA") == 0) return TOKEN_ESCREVA;
    if (strcmp(lexema, "se") == 0 || strcmp(lexema, "SE") == 0) return TOKEN_SE;
    if (strcmp(lexema, "entao") == 0 || strcmp(lexema, "então") == 0 || strcmp(lexema, "ENTAO") == 0 || strcmp(lexema, "ENTÃO") == 0) return TOKEN_ENTAO;
    if (strcmp(lexema, "senao") == 0 || strcmp(lexema, "senão") == 0 || strcmp(lexema, "SENAO") == 0 || strcmp(lexema, "SENÃO") == 0) return TOKEN_SENAO;
    if (strcmp(lexema, "fim_se") == 0 || strcmp(lexema, "FIM_SE") == 0) return TOKEN_FIM_SE;
    if (strcmp(lexema, "para") == 0 || strcmp(lexema, "PARA") == 0) return TOKEN_PARA;
    if (strcmp(lexema, "ate") == 0 || strcmp(lexema, "até") == 0 || strcmp(lexema, "ATE") == 0 || strcmp(lexema, "ATÉ") == 0) return TOKEN_ATE;
    if (strcmp(lexema, "passo") == 0 || strcmp(lexema, "PASSO") == 0) return TOKEN_PASSO;
    if (strcmp(lexema, "fim_para") == 0 || strcmp(lexema, "FIM_PARA") == 0) return TOKEN_FIM_PARA;
    
    // Operadores lógicos textuais
    if (strcmp(lexema, "e") == 0 || strcmp(lexema, "E") == 0) return TOKEN_E;
    if (strcmp(lexema, "ou") == 0 || strcmp(lexema, "OU") == 0) return TOKEN_OU;
    if (strcmp(lexema, "nao") == 0 || strcmp(lexema, "não") == 0 || strcmp(lexema, "NAO") == 0 || strcmp(lexema, "NÃO") == 0) return TOKEN_NAO;
    
    return -1; 
}

// Tabela de símbolos
#define MAX_SIMBOLOS 100
#define MAX_COMPRIMENTO_LEXEMA 100

char tabelaSimbolos[MAX_SIMBOLOS][MAX_COMPRIMENTO_LEXEMA];
int contagemSimbolos = 0;

int inserirTabelaSimbolos(char* lexema) {

    for (int i = 0; i < contagemSimbolos; i++) {
        if (strcmp(tabelaSimbolos[i], lexema) == 0) {
            return i; 
        }
    }
    
    if (contagemSimbolos < MAX_SIMBOLOS) {
        strcpy(tabelaSimbolos[contagemSimbolos], lexema);
        int posicao = contagemSimbolos;
        contagemSimbolos++;
        return posicao;
    }
    
    return -1; 
}

// Função para imprimir a tabela de símbolos
void imprimirTabelaSimbolos() {
    printf("Posicao | Lexema\n");
    printf("----------------\n");
    for (int i = 0; i < contagemSimbolos; i++) {
        printf("%7d | %s\n", i, tabelaSimbolos[i]);
    }
}
