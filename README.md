# ICEVOS
Simulador de Escalonador de Processos (Simulador de SO)

## Integrantes

| Nome                      | Nick GitHub       |
|---------------------------|-------------------|
| Eric Santos Moura Lima     | **ZpexLakip**     |
| Carlos Benedito Maciel II  | **SkylerZdev**    |
| Rodrigo Tavares Bezerra    | **lb_Rodrigo_dl** |


**Repositório GitHub:** [SkylerZdev/iCEVOS](https://github.com/SkylerZdev/iCEVOS)

## Descrição do Projeto

Este projeto implementa um escalonador de processos em linguagem C, simulando o gerenciamento de processos em um sistema operacional.


O escalonador possibilita:

- Carregar processos a partir de um arquivo (`Processos/processos`).
- Executar um ciclo único de escalonamento, mostrando qual processo foi executado.
- Rodar o escalonador completo até o término de todos os processos.
- Bloquear processos com recurso **“DISCO”** e retornar posteriormente à fila correta.
- Implementar **Anti-inanição**: após 5 execuções seguidas na fila Alta, força execução de Média ou Baixa.
- Exibir mensagens de validação quando não há processos disponíveis.

## Funcionalidades do Menu

```text
[1] Carregar Processos
[2] Executar Ciclo Único
[3] Executar até Terminar
[4] Impressão de Filas
[5] Voltar ao Menu Principal
```

## Como Compilar e Executar

1. Abra o terminal na pasta do projeto.
2. Compile com:
   ```bash
   gcc main.c -o programa.exe -std=c11 -Wall -Wextra
   ```
3. Execute com:
   ```bash
   Start-Process ./programa.exe
   ```
 ### | AVISO | 
Tenha Certeza que seu compilador esta na versão mais recente.

## Estrutura do Projeto

```text
Projeto
|
├── main.c        → Arquivo principal (menu do programa)
├── MyLib.h       → Estruturas e funções do escalonador
├── Processos/    → Pasta com arquivos de entrada
│   └── processos → Arquivo de entrada com os processos
└── README.md     → Documentação do projeto
```


## Exemplo de Arquivo de Entrada

O arquivo `Processos/processos` deve ter **um processo por linha**, no formato:

```text
id nome prioridade ciclos recurso
```

### Significado de cada campo

| Campo       | Descrição                                                    |
|-------------|--------------------------------------------------------------|
| **id**      | Identificador numérico único do processo                      |
| **nome**    | Nome ou rótulo do processo (sem espaços)                      |
| **prioridade** | 1 (Alta), 2 (Média), 3 (Baixa)                            |
| **ciclos**  | Número de ciclos de CPU que o processo precisa                |
| **recurso** | Nome do recurso solicitado (`DISCO`) ou `-` se nenhum recurso |

### Exemplo prático

```text
1 P1 1 5 -
2 P2 2 3 DISCO
3 P3 3 4 -
```

Nesse exemplo:

- O **P1** é prioridade **Alta**, precisa de 5 ciclos e não usa recurso.
- O **P2** é prioridade **Média**, precisa de 3 ciclos e usa o recurso `DISCO`.
- O **P3** é prioridade **Baixa**, precisa de 4 ciclos e não usa recurso.


## Status do Projeto

- [x] Estruturas de dados (Processo, Fila, Escalonador)
- [x] Leitura de processos de arquivo
- [x] Execução de ciclo único
- [x] Execução até terminar
- [x] Bloqueio/Desbloqueio de processos com “DISCO”
- [x] Anti-inanição implementada
