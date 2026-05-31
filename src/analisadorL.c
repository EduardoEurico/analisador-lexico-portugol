#include "definicoes.h"

FILE *arquivo_fonte;

Token getToken() {
    Token t;
    t.tablePosition = -1;
    char c = fgetc(arquivo_fonte);

    // Ignorar espaços em branco e quebras de linha
    while (c == ' ' || c == '\n' || c == '\t' || c == '\r') {
        c = fgetc(arquivo_fonte);
    }

    // Identificar Fim de Arquivo
    if (c == EOF) {
        t.code = TOKEN_EOF;
        return t;
    }

    // Identificar constantes literais (strings) com aspas retas
    if (c == '"') {
        char lexema[100];
        int i = 0;
        c = fgetc(arquivo_fonte);
        while (c != '"' && c != EOF) {
            if (i < 99) {
                lexema[i++] = c;
            }
            c = fgetc(arquivo_fonte);
        }
        lexema[i] = '\0';
        if (c == EOF) {
            t.code = TOKEN_ERRO;
        } else {
            t.code = TOKEN_STRING;
        }
        return t;
    }
    
    // Identificar constantes literais (strings) com aspas curvas
    if ((unsigned char)c == 0xE2) {
        char next1 = fgetc(arquivo_fonte);
        char next2 = fgetc(arquivo_fonte);
        if ((unsigned char)next1 == 0x80 && ((unsigned char)next2 == 0x9C || (unsigned char)next2 == 0x9D)) {
            char lexema[100];
            int i = 0;
            while (1) {
                char ch = fgetc(arquivo_fonte);
                if (ch == EOF) {
                    t.code = TOKEN_ERRO;
                    return t;
                }
                if ((unsigned char)ch == 0xE2) {
                    char n1 = fgetc(arquivo_fonte);
                    char n2 = fgetc(arquivo_fonte);
                    if ((unsigned char)n1 == 0x80 && ((unsigned char)n2 == 0x9C || (unsigned char)n2 == 0x9D)) {
                        break;
                    } else {
                        if (i < 97) {
                            lexema[i++] = ch;
                            lexema[i++] = n1;
                            lexema[i++] = n2;
                        }
                    }
                } else {
                    if (i < 99) {
                        lexema[i++] = ch;
                    }
                }
            }
            lexema[i] = '\0';
            t.code = TOKEN_STRING;
            return t;
        } else {
            ungetc(next2, arquivo_fonte);
            ungetc(next1, arquivo_fonte);
        }
    }

    // Identificar letras (Identificadores e Palavras Reservadas)
    if (isalpha(c) || (unsigned char)c >= 128) {
        char lexema[100];
        int i = 0;
        
        // Enquanto for letra, número ou caractere acentuado UTF-8 (byte >= 128)
        while (isalnum(c) || c == '_' || (unsigned char)c >= 128) {
            if (i < 99) {
                lexema[i++] = c;
            }
            c = fgetc(arquivo_fonte);
        }
        lexema[i] = '\0';
        ungetc(c, arquivo_fonte);

        int codReservada = verificaPalavraReservada(lexema);
        if (codReservada != -1) {
            t.code = codReservada;
        } else {
            t.code = TOKEN_ID; 
            t.tablePosition = inserirTabelaSimbolos(lexema);
        }
        return t;
    }
    
    // Identificar números
    if (isdigit(c)) {
        char lexema[100];
        int i = 0;
        while (isdigit(c)) {
            if (i < 99) {
                lexema[i++] = c;
            }
            c = fgetc(arquivo_fonte);
        }
        lexema[i] = '\0';
        ungetc(c, arquivo_fonte);
        t.code = TOKEN_NUMERO;
        return t;
    }

    // Identificar operadores e pontuação
    switch (c) {
        case '+': t.code = TOKEN_SOMA; return t;
        case '-': t.code = TOKEN_SUB; return t;
        case '*': t.code = TOKEN_MULT; return t;
        case '/': t.code = TOKEN_DIV; return t;
        case '(': t.code = TOKEN_ABRE_PAR; return t;
        case ')': t.code = TOKEN_FECHA_PAR; return t;
        case ';': t.code = TOKEN_PONTO_VIRGULA; return t;
        case ':': t.code = TOKEN_DOIS_PONTOS; return t;
        case '=': t.code = TOKEN_IGUAL; return t;
        case '>': {
            char next = fgetc(arquivo_fonte);
            if (next == '=') {
                t.code = TOKEN_MAIOR_IGUAL;
            } else {
                ungetc(next, arquivo_fonte);
                t.code = TOKEN_MAIOR;
            }
            return t;
        }
        case '<': {
            char next = fgetc(arquivo_fonte);
            if (next == '=') {
                t.code = TOKEN_MENOR_IGUAL;
            } else if (next == '>') {
                t.code = TOKEN_DIFERENTE;
            } else if (next == '-') {
                t.code = TOKEN_ATRIBUICAO;
            } else {
                ungetc(next, arquivo_fonte);
                t.code = TOKEN_MENOR;
            }
            return t;
        }
    }

    t.code = TOKEN_ERRO;
    return t;
}
