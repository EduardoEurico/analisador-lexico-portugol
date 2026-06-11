@echo off
echo ===================================================
echo Iniciando compilacao do Analisador Lexico...
echo ===================================================

:: Tenta encontrar um compilador disponivel
set COMPILADOR=
set METODO_COMPILACAO=

:: 1. Verifica se 'gcc' ja esta no PATH do sistema
where gcc >nul 2>nul
if not errorlevel 1 (
    set COMPILADOR=gcc
    set METODO_COMPILACAO=gcc_path
    goto COMPILADOR_ENCONTRADO
)

:: 2. Verifica se o GCC do Dev-Cpp existe
if exist "C:\Dev-Cpp\bin\gcc.exe" (
    set COMPILADOR="C:\Dev-Cpp\bin\gcc.exe"
    set METODO_COMPILACAO=gcc_direto
    goto COMPILADOR_ENCONTRADO
)

:: 3. Verifica se o GCC do MSYS2 existe
if exist "C:\msys64\mingw64\bin\gcc.exe" (
    set COMPILADOR="C:\msys64\mingw64\bin\gcc.exe"
    set METODO_COMPILACAO=gcc_direto
    goto COMPILADOR_ENCONTRADO
)

:: 4. Verifica MSVC (Visual Studio 2022 Community)
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS_PATH="C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
    set METODO_COMPILACAO=msvc
    goto COMPILADOR_ENCONTRADO
)

:: 5. Verifica MSVC (Visual Studio 2022 Build Tools)
if exist "C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS_PATH="C:\Program Files\Microsoft Visual Studio\2022\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    set METODO_COMPILACAO=msvc
    goto COMPILADOR_ENCONTRADO
)

:: 6. Verifica MSVC (Visual Studio 2019 Build Tools)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"
    set METODO_COMPILACAO=msvc
    goto COMPILADOR_ENCONTRADO
)

:: 7. Verifica MSVC (Visual Studio 2019 Community)
if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat" (
    set VCVARS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvars64.bat"
    set METODO_COMPILACAO=msvc
    goto COMPILADOR_ENCONTRADO
)

echo [ERRO] Nenhum compilador C compativel (GCC ou MSVC) foi encontrado no sistema.
echo Certifique-se de ter o GCC instalado (via MinGW, MSYS2 ou Dev-Cpp) ou o Visual Studio Build Tools.
pause
exit /b 1

:COMPILADOR_ENCONTRADO
if not exist build mkdir build

if "%METODO_COMPILACAO%"=="gcc_path" goto COMPILAR_GCC_PATH
if "%METODO_COMPILACAO%"=="gcc_direto" goto COMPILAR_GCC_DIRETO
if "%METODO_COMPILACAO%"=="msvc" goto COMPILAR_MSVC

echo [ERRO] Metodo de compilacao desconhecido.
pause
exit /b 1

:COMPILAR_GCC_PATH
echo [DETECTADO] GCC disponivel no PATH. Compilando...
gcc -o build\compilador.exe src\main.c src\analisadorL.c src\tabela.c
goto COMPILACAO_CONCLUIDA

:COMPILAR_GCC_DIRETO
echo [DETECTADO] GCC encontrado em %COMPILADOR%. Compilando...
%COMPILADOR% -o build\compilador.exe src\main.c src\analisadorL.c src\tabela.c
if not errorlevel 1 goto COMPILACAO_CONCLUIDA

echo [AVISO] Compilacao direta falhou. Tentando compilar arquivos de objeto separados e linkar diretamente com ld.exe...
%COMPILADOR% -c src\main.c -o build\main.o
%COMPILADOR% -c src\analisadorL.c -o build\analisadorL.o
%COMPILADOR% -c src\tabela.c -o build\tabela.o

if not exist build\main.o goto COMPILACAO_CONCLUIDA

echo [LINKANDO] Executando linker direto (ld.exe)...
"C:\Dev-Cpp\bin\ld.exe" -Bdynamic -o build\compilador.exe "C:\Dev-Cpp\lib\crt2.o" "C:\Dev-Cpp\lib\gcc\mingw32\3.4.2\crtbegin.o" -L"C:\Dev-Cpp\lib\gcc\mingw32\3.4.2" -L"C:\Dev-Cpp\lib" -L"C:\Dev-Cpp\mingw32\lib" build\main.o build\analisadorL.o build\tabela.o -lmingw32 -lgcc -lmoldname -lmingwex -lmsvcrt -luser32 -lkernel32 -ladvapi32 -lshell32 -lmingw32 -lgcc -lmoldname -lmingwex -lmsvcrt "C:\Dev-Cpp\lib\gcc\mingw32\3.4.2\crtend.o"
goto COMPILACAO_CONCLUIDA

:COMPILAR_MSVC
echo [DETECTADO] MSVC encontrado em %VCVARS_PATH%.
echo Configurando variaveis do MSVC e compilando...
call %VCVARS_PATH% > nul
cl.exe /nologo /W3 /D_CRT_SECURE_NO_WARNINGS /Fobuild\ /Febuild\compilador.exe src\main.c src\analisadorL.c src\tabela.c
goto COMPILACAO_CONCLUIDA

:COMPILACAO_CONCLUIDA
if errorlevel 1 (
    echo.
    echo [ERRO] Ocorreu um erro durante a compilacao.
    pause
    exit /b 1
)

echo.
echo ===================================================
echo Compilacao Concluida! Executando o analisador...
echo ===================================================
echo.

build\compilador.exe

echo.
echo ===================================================
echo Execucao finalizada.
echo ===================================================
pause
