#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Processo {
    int id;
    char nome[40];
    int prioridade; // 1 para alta, 2 para média, 3 para baixa.
    int ciclos;
    char recurso[12]; // Definir como DISCO ou "" no programa.
    int prioridadeOriginal;
    bool jaBloqueado;
} Processo;

typedef struct Node{
    Processo data;
    struct Node *prox;
} Node;

typedef struct Fila{
    Node *inicio;
    Node *final;
    int size;
} Fila;

typedef struct Escalonador {
    Fila Alta, Media, Baixa, Bloqueados;
    int contadorAlta;
} Escalonador;



// Filas Organizadas no Escalonador
Escalonador escalonador;

void iniciar_fila(Fila *f) { 
    f->inicio = f->final = NULL; 
    f->size = 0; 
}


int fila_adicionar(Fila *f, const Processo *p) {
    Node *novo = (Node*) malloc(sizeof(Node)); //Malloc reserva um espaço na memoria heap do tamanho de um Node // o Ponteiro novo é definido pra conter o endereço gerado pelo Malloc 
    if (!novo) return 0;                       // o If checa se tudo correu bem

    novo->data = *p;    
    novo->prox = NULL; 

    if (!f->final) { //Checa se a fila a qual o processo vai entrar é vazia (Se tem um Node Final) 
        f->inicio = f->final = novo; // Se for vazia, atribui que o Node é agora tanto o primeiro quanto o ultimo Node da Lista
    } else {
        f->final->prox = novo; //Indexa o ultimo Node ao novo
        f->final = novo; // Define que o Node em *novo agora é o "novo" ultimo da lista
    }

    f->size++;
    return 1; 
}

int fila_remover(Fila *f, Processo *saida) {
    if (!f->inicio) return 0; // Checa pra ver se a fila é valida

    Node *prim = f->inicio; // Cria um ponteiro "Prim" que indica Node, e define que ele guarda o endereço do atual Node Inicial da fila
    if (saida) *saida = prim->data; // Copia as informações do processo removido para o endereço de Saida

    f->inicio = prim->prox; //Define o proximo processo como sendo o primeiro da fila
    if (!f->inicio) f->final = NULL; //se o processo era o ultimo, declara a fila como vazia

    free(prim);
    f->size--; 
    return 1;
}

inline bool estaVazia(Fila *f){ //Checa se a fila está vazia
    return (f->inicio == NULL); 
}

bool todasListasVazias(Escalonador *e){ //Checa se todas as filas estão vazias
    return (estaVazia(&e->Alta) && estaVazia(&e->Media) && estaVazia(&e->Baixa) && estaVazia(&e->Bloqueados));
}

inline int fila_tamanho(Fila *f) { //Retorna o tamanho da fila
    return f->size;
}

Node *Get(Fila *f, int i){ //Retorna o nó da posição i da fila
    if(i >= f->size || i < 0) return NULL;
    if(i == 0) return f->inicio;
    if(i == f->size - 1) return f->final;
    Node *atual = f->inicio;
    int c = 0;

    while (atual && c < i) {
        atual = atual->prox;
        c++;
    }
    return atual;
}

void carregarProcessos() {  //Parte da Leitura de Arquivo
    FILE *f = fopen("Processos/processos","r"); //Abre o Diretoório do arquivo 
    if (!f) { printf("Erro ao abrir processos.txt\n"); 
    }
    int id, pri, cic; char nome[40], recurso[12];
    char linha[128]; //Tamanho de caracteres que pode ser lido por linha
    while (fgets(linha, sizeof(linha), f)) { //Lê linha por linha do arquivo, melhor que fscanf
        if (sscanf(linha, "%d %39s %d %d %11s", &id, nome, &pri, &cic, recurso) == 5) {
            Processo p;
            p.id = id;
            strcpy(p.nome, nome);
            p.prioridade = (pri < 1 || pri > 3) ? 3 : pri;
            p.ciclos = cic;
            if (strcmp(recurso, "-") == 0) recurso[0] = '\0'; // Se o recurso for "-", define como string vazia
            strcpy(p.recurso, recurso);
            p.prioridadeOriginal = p.prioridade;
            p.jaBloqueado = false;
            switch (p.prioridade) {
                case 1:
                    fila_adicionar(&escalonador.Alta, &p);
                    break;
                case 2:
                    fila_adicionar(&escalonador.Media, &p);
                    break;
                case 3:
                default:
                    fila_adicionar(&escalonador.Baixa, &p);
                    break;
            }
        }
    }
    fclose(f);
    printf("Processos carregados com sucesso!\n");
}

// Função de Executar um Unico Ciclo
void executarCicloUnico(Escalonador *e) {
    // Implementar lógica para executar um ciclo único do escalonador
}

// Função de Rodar Escalonador
void rodarEscalonador(Escalonador *e) {
    if (todasListasVazias) { // Verifica se todas as listas estão vazias antes de iniciar
        printf("Nenhum processo para executar.\n");
        return;
    }
    while (!todasListasVazias(e)) { // Enquanto ainda houver processos em alguma fila
        executarCicloUnico(e); // Executa um ciclo de CPU simulando escalonamento
    }
    printf("Escalonamento concluído!\n");
}
