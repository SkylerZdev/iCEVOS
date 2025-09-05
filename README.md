#ICEVOS
Simulador de Escalonador de Processos (Simulador de SO)

Integrantes

- Eric Santos Moura Lima
- Carlos Benedito Maciel II 
- Rodrigo Tavares Bezerra 

Repositório GitHub: https://github.com/SkylerZdev/iCEVOS

Descrição do Projeto

Este projeto implementa um escalonador de processos em linguagem C, simulando o gerenciamento de processos em um sistema operacional.  


O escalonador possibilita:

- Carregar processos a partir de um arquivo texto (`Processos/processos`).
- Executar um ciclo único** de escalonamento, mostrando qual processo foi executado.  
- Rodar o escalonador completo** até o término de todos os processos.
- Bloqueio de processos com recurso “DISCO”** e retorno posterior à fila correta.  
- Anti-inanição: após 5 execuções seguidas na fila Alta, força execução de Média ou Baixa.  
- Validações: mensagens quando não há processos disponíveis.


Funcionalidades do Menu

[1] Carregar Processos
[2] Executar Ciclo Único
[3] Executar até Terminar
[4] Voltar ao Menu Principal


Como Compilar e Executar
-Abra o terminal na pasta do projeto.
-Compile com-> gcc main.c MyLib.h -o escalonador
-Execute com-> ./escalonador


Estrutura do Projeto

 Projeto
| 
├── main.c → Arquivo principal (menu do programa)
├── MyLib.h → Estruturas e funções do escalonador
├── Processos/ → Pasta com arquivos de entrada
│ └── processos → Arquivo de entrada com os processos
└── README.md → Documentação do projeto


Exemplo de Arquivo de Entrada

O arquivo `Processos/processos` deve ter um processo por linha, no formato: (id nome prioridade ciclos recurso)

O que significa cada campo

- `id` -> Identificador numérico único do processo.  
- `nome` -> Nome ou rótulo do processo.  
- `prioridade` -> 1 (Alta), 2 (Média), 3 (Baixa).  
- `ciclos` -> Número de ciclos de CPU que o processo precisa.  
- `recurso` -> Nome do recurso solicitado (ex.: `DISCO`) ou `-` se nenhum.  

Exemplo prático

1 P1 1 5 -
2 P2 2 3 DISCO
3 P3 3 4 -

Nesse exemplo
- O P1 é prioridade alta, precisa de 5 ciclos e não usa recurso.  
- O P2 é prioridade média, precisa de 3 ciclos e usa o recurso `DISCO`.  
- O P3 é prioridade baixa, precisa de 4 ciclos e não usa recurso.  


Status do Projeto
- [x] Estruturas de dados (Processo, Fila, Escalonador)
- [x] Leitura de processos de arquivo  
- [x] Execução de ciclo único  
- [x] Execução até terminar  
- [x] Bloqueio/Desbloqueio de processos com “DISCO”  
- [x] Anti-inanição implementada  
