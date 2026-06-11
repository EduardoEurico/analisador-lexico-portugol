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
    int i;
    for (i = 0; i < contagemSimbolos; i++) {
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
    int i;
    printf("Posicao | Lexema\n");
    printf("----------------\n");
    for (i = 0; i < contagemSimbolos; i++) {
        printf("%7d | %s\n", i, tabelaSimbolos[i]);
    }
}

// Retorna o nome amigável do Token
const char* nomeToken(TokenType type) {
    switch (type) {
        case TOKEN_INICIO: return "INICIO";
        case TOKEN_FIM: return "FIM";
        case TOKEN_INTEIRO: return "INTEIRO";
        case TOKEN_LEIA: return "LEIA";
        case TOKEN_IMPRIMA: return "IMPRIMA";
        case TOKEN_ESCREVA: return "ESCREVA";
        case TOKEN_SE: return "SE";
        case TOKEN_ENTAO: return "ENTAO";
        case TOKEN_SENAO: return "SENAO";
        case TOKEN_FIM_SE: return "FIM_SE";
        case TOKEN_PARA: return "PARA";
        case TOKEN_ATE: return "ATE";
        case TOKEN_PASSO: return "PASSO";
        case TOKEN_FIM_PARA: return "FIM_PARA";
        case TOKEN_E: return "OPERADOR_LOGICO_E";
        case TOKEN_OU: return "OPERADOR_LOGICO_OU";
        case TOKEN_NAO: return "OPERADOR_LOGICO_NAO";
        case TOKEN_SOMA: return "OPERADOR_SOMA";
        case TOKEN_SUB: return "OPERADOR_SUB";
        case TOKEN_MULT: return "OPERADOR_MULT";
        case TOKEN_DIV: return "OPERADOR_DIV";
        case TOKEN_ATRIBUICAO: return "OPERADOR_ATRIBUICAO";
        case TOKEN_MAIOR: return "OPERADOR_MAIOR";
        case TOKEN_MENOR: return "OPERADOR_MENOR";
        case TOKEN_MAIOR_IGUAL: return "OPERADOR_MAIOR_IGUAL";
        case TOKEN_MENOR_IGUAL: return "OPERADOR_MENOR_IGUAL";
        case TOKEN_IGUAL: return "OPERADOR_IGUAL";
        case TOKEN_DIFERENTE: return "OPERADOR_DIFERENTE";
        case TOKEN_ABRE_PAR: return "DELIMITADOR_ABRE_PAR";
        case TOKEN_FECHA_PAR: return "DELIMITADOR_FECHA_PAR";
        case TOKEN_PONTO_VIRGULA: return "PONTO_VIRGULA";
        case TOKEN_DOIS_PONTOS: return "DOIS_PONTOS";
        case TOKEN_ID: return "IDENTIFICADOR";
        case TOKEN_NUMERO: return "NUMERO";
        case TOKEN_STRING: return "STRING";
        case TOKEN_EOF: return "FIM_DE_ARQUIVO";
        case TOKEN_ERRO: return "ERRO";
        default: return "DESCONHECIDO";
    }
}
