#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Processo {
    int id;
    char nome[40];
    int prioridade; // 1 para alta, 2 para média, 3 para baixa.
    int ciclos;
    char recurso[12]; // Definir como DISCO ou "" no programa.
    int prioridadeOriginal;
    int jaBloqueado;
    struct Processo *prox;
} Processo;

// Filas globais para simplificação (Ini io do processo Fazer os arq.
Processo *filaAlta = NULL, *filaMedia = NULL, *filaBaixa = NULL, *filaBloqueados = NULL;
int contadorAlta = 0, cicloAtual = 0;

void carregarProcessos() {  //Parte da Leitura de Arquivo
    FILE *f = fopen("Processos/processos","r");
    if (!f) { printf("Erro ao abrir processos.txt\n"); return; }

    int id, pri, cic; char nome[40], recurso[12];
    while (fscanf(f,"%d %39s %d %d %11s", &id,nome,&pri,&cic,recurso)==5) {
        Processo *p = (Processo*) malloc(sizeof(Processo));
        p->id=id;
        strcpy(p->nome,nome);
        p->prioridade=(pri<1||pri>3)?3:pri;
        p->ciclos=cic;
        if (strcmp(recurso,"-")==0) recurso[0]='\0';
        strcpy(p->recurso,recurso);
        p->prioridadeOriginal=p->prioridade;
        p->jaBloqueado=0;
        p->prox=NULL;

        if (p->prioridade==1) enfileirar(&filaAlta,p);
        else if (p->prioridade==2) enfileirar(&filaMedia,p);
        else enfileirar(&filaBaixa,p);
    }
    fclose(f);
    printf("Processos carregados com sucesso!\n");
}
