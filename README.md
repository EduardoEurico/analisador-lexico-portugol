# Analisador Léxico - Compiladores

Este é um projeto de um **Analisador Léxico** simples implementado na linguagem C. O programa lê um arquivo contendo código-fonte, processa caractere por caractere para reconhecer os *tokens* (palavras reservadas, identificadores, números, operadores e delimitadores) com base nas regras léxicas definidas e exibe cada token identificado no terminal.

---

## 📂 Estrutura do Projeto e Organização

O projeto está organizado em subpastas para manter a área de trabalho limpa e profissional. Apenas os arquivos de documentação e scripts de automação ficam na raiz do projeto:

*   📂 **`src/`** (Pasta de códigos fontes principais):
    *   **`definicoes.h`**: Cabeçalho global contendo enums para `TokenType`, a estrutura de dados `Token`, importações de bibliotecas e protótipos de funções.
    *   **`main.c`**: Ponto de entrada do programa. Responsável por abrir o arquivo de entrada (`src/programa.txt`), ler iterativamente todos os tokens e exibir os resultados.
    *   **`analisadorL.c`**: Implementa a função principal `getToken()`, contendo toda a lógica do autômato léxico.
    *   **`tabela.c`**: Contém funções utilitárias auxiliares, como a identificação e diferenciação de palavras reservadas de identificadores normais.
    *   **`programa.txt`**: O arquivo contendo o código na linguagem de teste que será submetido à análise léxica.
*   📂 **`build/`** (Pasta gerada de forma automatizada):
    *   **`compilador.exe`**: Executável gerado após a compilação.
    *   **`*.obj`**: Arquivos de compilação intermediários gerados pelo MSVC (`main.obj`, `analisadorL.obj`, `tabela.obj`).
*   📄 **`compilar.bat`**: Script de lote (batch) para Windows que prepara o ambiente do MSVC, cria a pasta `build`, compila os arquivos de `src` para `build`, limpa e executa o analisador.
*   📄 **`README.md`**: Este arquivo de documentação.

---

## 🛠️ Pré-requisitos e Instalação de Dependências

Para compilar o projeto, você precisa de um compilador C. Escolha uma das opções abaixo:

### Opção 1: Usando o Compilador MSVC (Windows - Recomendado)

O script `compilar.bat` já está pronto para usar o compilador **MSVC (Microsoft Visual C++)** através do Visual Studio Build Tools.

1.  Faça o download do [Visual Studio Build Tools](https://visualstudio.microsoft.com/visual-cpp-build-tools/).
2.  No instalador, marque a opção **Desenvolvimento para Desktop com C++** e conclua a instalação.
3.  **Nota sobre a versão:** O script `compilar.bat` busca por padrão o caminho do **Visual Studio 2019 Build Tools**:
    `C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat`
    *Se você estiver utilizando outra versão (como o Visual Studio 2022) ou outra edição (como Community ou Professional), abra o arquivo `compilar.bat` em um editor e altere a linha 8 com o caminho correto do `vcvars64.bat` ou `vcvarsall.bat` da sua máquina.*

### Opção 2: Usando o GCC (MinGW no Windows, nativo no Linux/macOS)

*   **Windows (MinGW):**
    1. Instale o [MinGW-w64](https://www.mingw-w64.org/).
    2. Adicione a pasta `bin` do MinGW (ex: `C:\msys64\mingw64\bin`) ao PATH das variáveis de ambiente do Windows.
*   **Linux (Ubuntu/Debian):**
    ```bash
    sudo apt update
    sudo apt install build-essential
    ```
*   **macOS:**
    ```bash
    xcode-select --install
    ```

---

## 🚀 Como Compilar e Rodar

### Método A: Usando o Script Automatizado (Windows)

1. Dê dois cliques no arquivo **`compilar.bat`** ou abra o PowerShell/Prompt de Comando na pasta do projeto e digite:
   ```cmd
   .\compilar.bat
   ```
2. O script se encarrega de criar a pasta `build/`, compilar os arquivos dentro de `src/`, colocar todos os temporários e o executável em `build/` e executar o analisador para você.

### Método B: Compilação Manual via Terminal (GCC)

Se preferir utilizar o compilador GCC:

1. Abra o terminal na pasta raiz do projeto.
2. Execute o comando para compilar e salvar o executável na pasta `build` (crie a pasta com `mkdir build` antes, se necessário):
   *   **Windows:**
       ```bash
       gcc -o build/compilador.exe src/main.c src/analisadorL.c src/tabela.c
       ```
   *   **Linux / macOS:**
       ```bash
       gcc -o build/compilador src/main.c src/analisadorL.c src/tabela.c
       ```
3. Execute o compilador gerado:
   *   **Windows:**
       ```cmd
       .\build\compilador.exe
       ```
   *   **Linux / macOS:**
       ```bash
       ./build/compilador
       ```

---

## 📝 Como Testar Outros Códigos

O analisador léxico lê o código de entrada contido em **`programa.txt`**.

Para realizar novos testes:
1. Abra o arquivo `programa.txt` em um editor de texto de sua preferência.
2. Modifique o código escrito, respeitando a sintaxe esperada (ex: `inicio`, `inteiro x;`, `leia x;`, `fim`).
3. Salve o arquivo `programa.txt`.
4. Execute o compilador novamente através do método de sua preferência (Método A ou Método B) para ver a nova saída da análise léxica.

## 🧠 Explicação Detalhada do Funcionamento do Código

O analisador léxico funciona como um leitor sequencial inteligente de caracteres. Abaixo está o detalhamento técnico do fluxo e lógica de cada parte do projeto:

```
                  ┌──────────────────────────┐
                  │     src/programa.txt     │
                  └─────────────┬────────────┘
                                │ (Fluxo de caracteres)
                                ▼
 ┌────────────┐   Chamadas   ┌──────────────────────────┐   Validação   ┌────────────┐
 │ src/main.c ├─────────────>│    src/analisadorL.c     ├──────────────>│src/tabela.c│
 │ (Loop)     │<────────────┤ (Lógica do Autômato)     │<──────────────┤ (Keywords) │
 └──────┬─────┘  Retorno de  └───────────┬──────────────┘ Retorna código └────────────┘
        │          Tokens                │
        │                                │ Inserção de Identificadores (Variáveis)
        │                                ▼
        │                        ┌──────────────┐
        │                        │ Tabela de    │
        └───────────────────────>│ Símbolos     │
             Exibição Final      └──────────────┘
```

### 1. Modelagem de Dados (`src/definicoes.h`)
Para que o compilador compreenda a categoria de cada elemento, definimos a enumeração `TokenType`. Ela mapeia palavras-chave e símbolos da linguagem para códigos numéricos estáticos. O analisador encapsula os dados reconhecidos na estrutura `Token`:
*   `TokenType code`: O código representativo daquele tipo de token (ex: `TOKEN_INICIO` para a palavra `inicio`, `TOKEN_NUMERO` para literais inteiros).
*   `int tablePosition`: Indica a posição onde o valor ou nome do token foi armazenado na **Tabela de Símbolos** (útil para identificadores/variáveis). Retorna `-1` se o token não necessitar de inserção em tabela.

O arquivo também define a proteção `#ifndef _CRT_SECURE_NO_WARNINGS` para silenciar avisos de funções de arquivos nativas no compilador MSVC.

### 2. Leitura e Loop de Análise (`src/main.c`)
*   O fluxo começa em `main()`, que abre o arquivo fonte `"src/programa.txt"` em modo de leitura (`fopen`).
*   Ele entra em um laço de repetição (`do-while`) que invoca consecutivamente a função `getToken()` do analisador.
*   Cada token extraído é impresso com seu respectivo código numérico no terminal.
*   O loop é interrompido no momento em que o token com código `TOKEN_EOF` (fim do arquivo) é retornado por `getToken()`.
*   **Listagem da Tabela:** Logo após fechar o arquivo fonte com `fclose`, o `main.c` invoca a função `imprimirTabelaSimbolos()` para exibir de forma organizada no terminal todas as variáveis que foram identificadas e guardadas na Tabela de Símbolos durante o processo de compilação.

### 3. A Lógica do Autômato Léxico (`src/analisadorL.c`)
A função principal `getToken()` é o coração do projeto. Ela opera seguindo as regras de transição de um **Autômato Finito**:

1.  **Descarte de Espaços e Quebras:** 
    A função lê caracteres um por um usando `fgetc`. Espaços em branco (` `), quebras de linha (`\n`, `\r`) e tabulações (`\t`) são apenas consumidos e descartados até que um caractere significativo seja encontrado.
2.  **Identificando o Fim do Arquivo (EOF):**
    Ao ler a constante especial `EOF` do arquivo, retorna um Token com código `TOKEN_EOF`, sinalizando a parada ao `main.c`.
3.  **Capturando Constantes Literais (Strings):**
    *   **Aspas Retas (`"`):** Ao encontrar `"`, consome todos os caracteres seguintes até achar o fechamento `"`, salvando-os como um lexema com token `TOKEN_STRING`.
    *   **Aspas Curvas (`“` e `”`):** Se ler o byte inicial `0xE2`, verifica se os seguintes correspondem às aspas curvas comuns em textos copiados de PDFs. Se sim, processa o bloco de texto de forma idêntica à string comum, retornando `TOKEN_STRING` de maneira transparente e livre de erros de digitação.
4.  **Capturando Palavras (Identificadores e Palavras Reservadas com UTF-8):**
    *   Ao ler uma letra inicial (`isalpha`) ou um caractere de controle de bit alto (`(unsigned char)c >= 128`), reconhece o início de uma palavra.
    *   Um loop lê e acumula os próximos caracteres enquanto forem alfanuméricos, sublinhados ou bytes de acentuação UTF-8 (`(unsigned char)c >= 128`), garantindo que palavras como `então`, `senão`, `não` e `até` sejam consumidas inteiramente como um único bloco.
    *   **Tratamento com `ungetc`:** Ao encontrar o primeiro caractere que não é válido (como um operador ou espaço), a função chama `ungetc(c, arquivo_fonte)` que o devolve ao buffer de leitura do arquivo para a próxima iteração.
    *   A string é enviada para `verificaPalavraReservada()`. Se corresponder a uma palavra-chave, o token recebe esse código e o campo `tablePosition` recebe `-1`. Se for uma variável, recebe o token `TOKEN_ID` e o campo `tablePosition` recebe o índice retornado por `inserirTabelaSimbolos(lexema)`.
5.  **Capturando Números:**
    *   Ao ler um dígito numérico inicial (`isdigit`), acumula dígitos válidos consecutivos, devolve o caractere delimitador final com `ungetc` e retorna o token `TOKEN_NUMERO`.
6.  **Reconhecimento de Operadores e Delimitadores (Simples e Compostos):**
    *   Um bloco `switch` avalia caracteres pontuais como `+` (`TOKEN_SOMA`), `-` (`TOKEN_SUB`), `*` (`TOKEN_MULT`), `/` (`TOKEN_DIV`), `(` (`TOKEN_ABRE_PAR`), `)` (`TOKEN_FECHA_PAR`), `:` (`TOKEN_DOIS_PONTOS`) e `;` (`TOKEN_PONTO_VIRGULA`).
    *   **Operadores Relacionais e Atribuição:** Ao encontrar `<` ou `>`, lê o caractere seguinte para decidir se é um operador composto:
      *   `>` seguido de `=` torna-se `TOKEN_MAIOR_IGUAL`; senão, devolve o caractere extra e torna-se `TOKEN_MAIOR`.
      *   `<` seguido de `=` torna-se `TOKEN_MENOR_IGUAL`.
      *   `<` seguido de `>` torna-se `TOKEN_DIFERENTE`.
      *   `<` seguido de `-` torna-se `TOKEN_ATRIBUICAO` (`<-`).
      *   Se for apenas `<`, devolve o caractere extra e torna-se `TOKEN_MENOR`.
7.  **Gerenciamento de Erros:**
    *   Qualquer caractere desconhecido que não atenda a nenhuma destas regras faz com que o analisador retorne `TOKEN_ERRO`, permitindo que o compilador acuse falha léxica.

### 4. Filtro de Palavras Reservadas e Tabela de Símbolos (`src/tabela.c`)
*   **Palavras Reservadas:**
    A função `verificaPalavraReservada()` recebe o lexema lido e o compara usando `strcmp` com as palavras nativas da linguagem de forma **insensível ao caso** (ex: aceita tanto `"inicio"` quanto `"INICIO"`) e dando suporte total a acentuações do Portugol (ex: aceita `"então"`, `"entao"`, `"ENTÃO"` e `"ENTAO"`).
*   **Tabela de Símbolos Estática:**
    A tabela é modelada como uma matriz estática de strings (`tabelaSimbolos[100][100]`) controlada por um contador (`contagemSimbolos`).
    A função `inserirTabelaSimbolos(lexema)`:
    1. Busca pelo lexema na tabela. Se encontrado, retorna o índice da posição existente.
    2. Se não encontrado e houver espaço disponível, realiza a cópia da string (`strcpy`), incrementa o contador e retorna o novo índice.
    3. Retorna `-1` se a tabela estiver cheia.

---

## 📝 Como Modificar e Testar Novos Programas

Para testar códigos personalizados no analisador léxico:
1. Abra o arquivo **`src/programa.txt`** em seu editor de texto.
2. Escreva o algoritmo que deseja testar (usando palavras reservadas como `inicio`, `inteiro`, `leia`, `imprima`, `fim`, operadores como `+`, `<-` e delimitadores como `;`).
3. Salve o arquivo.
4. Execute o script `.\compilar.bat` (ou execute a compilação e execução manual do GCC).
5. O console exibirá as categorias numéricas de todos os termos presentes no seu arquivo de teste, além de listar as variáveis salvas na Tabela de Símbolos.
