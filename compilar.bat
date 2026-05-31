@echo off
chcp 65001 > nul
echo ===================================================
echo Iniciando compilação do Analisador Léxico...
echo ===================================================

:: Configura o ambiente do compilador MSVC 2019 Build Tools
set VCVARS_PATH="C:\Program Files (x86)\Microsoft Visual Studio\2019\BuildTools\VC\Auxiliary\Build\vcvars64.bat"

if not exist %VCVARS_PATH% (
    echo [ERRO] Não foi possível encontrar o arquivo de configuração do compilador:
    echo %VCVARS_PATH%
    echo Verifique se o Visual Studio Build Tools 2019 está instalado corretamente.
    pause
    exit /b 1
)

echo [1/3] Configurando variáveis de ambiente do MSVC...
call %VCVARS_PATH% > nul

echo [2/3] Compilando arquivos C (src\main.c, src\analisadorL.c, src\tabela.c)...
if not exist build mkdir build
cl.exe /nologo /W3 /D_CRT_SECURE_NO_WARNINGS /Fobuild\ /Febuild\compilador.exe src\main.c src\analisadorL.c src\tabela.c

if %errorlevel% neq 0 (
    echo.
    echo [ERRO] Ocorreu um erro durante a compilação.
    pause
    exit /b %errorlevel%
)

echo.
echo ===================================================
echo [3/3] Compilação Concluída! Executando o analisador...
echo ===================================================
echo.

build\compilador.exe

echo.
echo ===================================================
echo Execução finalizada.
echo ===================================================
pause
