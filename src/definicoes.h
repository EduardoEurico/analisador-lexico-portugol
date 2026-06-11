#ifndef DEFINICOES_H
#define DEFINICOES_H

#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Definição de códigos únicos para os tokens
typedef enum {
    // Palavras reservadas
    TOKEN_INICIO, TOKEN_FIM, TOKEN_INTEIRO, TOKEN_LEIA, TOKEN_IMPRIMA, TOKEN_ESCREVA,
    TOKEN_SE, TOKEN_ENTAO, TOKEN_SENAO, TOKEN_FIM_SE,
    TOKEN_PARA, TOKEN_ATE, TOKEN_PASSO, TOKEN_FIM_PARA,
    
    // Operadores lógicos
    TOKEN_E, TOKEN_OU, TOKEN_NAO,
    
    // Operadores e Pontuação
    TOKEN_SOMA, TOKEN_SUB, TOKEN_MULT, TOKEN_DIV, 
    TOKEN_ATRIBUICAO, 
    TOKEN_MAIOR, TOKEN_MENOR, TOKEN_MAIOR_IGUAL, TOKEN_MENOR_IGUAL, TOKEN_IGUAL, TOKEN_DIFERENTE, // >, <, >=, <=, =, <>
    TOKEN_ABRE_PAR, TOKEN_FECHA_PAR, 
    TOKEN_PONTO_VIRGULA, TOKEN_DOIS_PONTOS, 
    
    // Tipos dinâmicos
    TOKEN_ID,        
    TOKEN_NUMERO,    
    TOKEN_STRING,    
    TOKEN_EOF,      
    TOKEN_ERRO
} TokenType;

// Estrutura para retornar o token e a posição na tabela
typedef struct {
    TokenType code;
    int tablePosition; 
    char lexema[100];
} Token;

// Variáveis globais
extern FILE *arquivo_fonte;

// Protótipos de funções
Token getToken();
const char* nomeToken(TokenType type);
int verificaPalavraReservada(char* lexema);
int inserirTabelaSimbolos(char* lexema);
void imprimirTabelaSimbolos();

#endif 
