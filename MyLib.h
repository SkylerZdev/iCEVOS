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

static inline bool estaVazia(Fila *f){ //Checa se a fila está vazia
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
    if (!f) { printf("Erro ao abrir processos\n");
			 return;
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

void desbloquearProcesso(Escalonador *e) {
    Processo p;
    if (fila_remover(&e->Bloqueados, &p)) {
        if (p.prioridadeOriginal == 1) {
		fila_adicionar(&e->Alta,  &p);
		printf("Processo %s desbloqueado e voltou para lista de prioridade Alta\n", p.nome);
		}
        else if (p.prioridadeOriginal == 2) {
		fila_adicionar(&e->Media, &p);
		printf("Processo %s desbloqueado e voltou para lista de prioridade Media\n", p.nome);
		}
        else {
		fila_adicionar(&e->Baixa, &p);
		printf("Processo %s desbloqueado e voltou para lista de prioridade Baixa\n", p.nome);
		}
    }
}

// Função de Executar um Único Ciclo do Escalonador
int executarCicloUnico(Escalonador *e, Fila *origem) {
    Processo temp;

    // 1) Tenta remover do início da fila 'origem'
    if (!fila_remover(origem, &temp)) {
        return 0; // fila vazia: nada a fazer neste ciclo
    }

    // 2) Bloqueio por DISCO (primeira vez não executa CPU)
    if (!temp.jaBloqueado && strcmp(temp.recurso, "DISCO") == 0) {
        temp.jaBloqueado = true;
        fila_adicionar(&e->Bloqueados, &temp);
        printf("Processo %s foi bloqueado (Recurso:%s) \n", temp.nome, temp.recurso);
        return 0; // não consumiu CPU
    }

    // (Opcional) Se por algum motivo já veio com ciclos <= 0, descarte
    if (temp.ciclos <= 0) {
    	printf("Processo %s Finalizado\n", temp.nome);
        // processo "fantasma": não re-enfileira, não consome CPU
        return 0;
    }

    // 3) Executa 1 ciclo de CPU
    temp.ciclos--;
	printf("Executando processo %s (ciclos restantes: %d)\n", temp.nome, temp.ciclos);
           
    // 4) Pós-execução: se ainda restam ciclos, volta ao fim da fila de origem (pela prioridade original)
    if (temp.ciclos > 0) {
        if      (temp.prioridadeOriginal == 1) {
		fila_adicionar(&e->Alta,  &temp);
		printf("O Processo %s executou um ciclo e voltou pra fila Alta\n", temp.nome);
		}
        else if (temp.prioridadeOriginal == 2) {
			fila_adicionar(&e->Media, &temp);
			printf("O Processo %s executou um ciclo e voltou pra fila Media\n", temp.nome);
		}
        else {
		fila_adicionar(&e->Baixa, &temp);
		printf("O Processo %s executou um ciclo e voltou pra fila Baixa\n", temp.nome);	
		}
    }
    // Se ciclos chegar a 0, terminou: não volta pra nenhuma fila.

    return 1; // consumiu 1 ciclo de CPU
}


void rodarEscalonadorUnico (Escalonador *e){
	    if (todasListasVazias(e)) {
        printf("Nenhum processo para escalonar!\n");
        return;
    }
        desbloquearProcesso(e);

        // 2) Preferência normal: Alta (até 5 seguidas), depois Média, depois Baixa
        if (!estaVazia(&e->Alta) && e->contadorAlta < 5) {
            if(executarCicloUnico(e, &e->Alta)){
            e->contadorAlta++; // Conta apenas se consumiu CPU
            }
        }
        else if (e->contadorAlta >= 5) {
            // Anti-inanição: força Média; se não houver, força Baixa; se só houver Alta, executa Alta
            if (!estaVazia(&e->Media)) {
            	printf("Anti Inanicao : ");
                executarCicloUnico(e, &e->Media);
                e->contadorAlta = 0;
            } else if (!estaVazia(&e->Baixa)) {
            	printf("Anti Inanicao : ");
                executarCicloUnico(e, &e->Baixa);
                e->contadorAlta = 0;
            } else if (!estaVazia(&e->Alta)) {
                //Executa Alta se for a unica disponivel
                executarCicloUnico(e, &e->Alta);
                printf("Anti Inanicao Falhou : ");
                // Mantemos contador em 5 para continuar forçando quando Média/Baixa surgirem
            }
        }
        else if (!estaVazia(&e->Media)) {
            executarCicloUnico(e, &e->Media);
            e->contadorAlta = 0;
            printf("Processo de Media prioridade Executado\n");
        }
        else if (!estaVazia(&e->Baixa)) {
            executarCicloUnico(e, &e->Baixa);
            e->contadorAlta = 0; // <-- zerar também na baixa
            printf("Processo de Baixa Prioridade Executado\n");
        }
        // Caso contrário: todas vazias (ou apenas bloqueados aguardando próximo ciclo); o while reavalia.
    }


// Função de Rodar Escalonador
void rodarEscalonador(Escalonador *e) {
    if (todasListasVazias(e)) {
        printf("Nenhum processo para escalonar!\n");
        return;
    }

    while (!todasListasVazias(e)) {
    rodarEscalonadorUnico(e);    
    }
	printf("--------------------------------------------------\n");
    printf("Escalonamento concluido!\n");
}

void imprimirFila(Fila *f, const char *nome) {
    if (!f) {
        printf("Fila %s inválida.\n", nome ? nome : "(sem nome)");
        return;
    }

    printf(" Fila %s | Tamanho atual: %d\n", nome, f->size);
    printf("|-----------------------------------------------------------------------|\n");
    printf("| %-3s | %-15s | %-10s | %-6s | %-8s | %-12s |\n",
           "Id", "Nome", "Prioridade", "Ciclos", "Recurso", "Ja Bloqueado");
    printf("|-----------------------------------------------------------------------|\n");

    Node *atual = f->inicio;
    if (!atual) {
        printf("| %-69s |\n", "(Vazia)");
         printf("|-----------------------------------------------------------------------|\n");
        return;
    }

    while (atual) {
        Processo *p = &atual->data;

        const char *recurso = (p->recurso[0]) ? p->recurso : "-";

        printf("| %-3d | %-15.15s | %-10d | %-6d | %-8.8s | %-12s |\n",
               p->id,
               p->nome,
               p->prioridade,
               p->ciclos,
               recurso,
               p->jaBloqueado ? "SIM" : "NAO");

        atual = atual->prox;
    }

}


void imprimirFilasTodas(Escalonador *e) {
    imprimirFila(&e->Alta, "Alta Prioridade");
    printf("|-----------------------------------------------------------------------|\n");
    imprimirFila(&e->Media, "Media Prioridade");
    printf("|-----------------------------------------------------------------------|\n");
    imprimirFila(&e->Baixa, "Baixa Prioridade");
    printf("|-----------------------------------------------------------------------|\n");
    imprimirFila(&e->Bloqueados, "Bloqueados");
    printf("|-----------------------------------------------------------------------|\n");
}

void rodarEscalonadorImp(Escalonador *e) {
    if (todasListasVazias(e)) {
        printf("Nenhum processo para escalonar!\n");
        return;
    }

    while (!todasListasVazias(e)) {
    rodarEscalonadorUnico(e);
    imprimirFilasTodas(e); 
    }
	printf("--------------------------------------------------\n");
    printf("Escalonamento concluido!\n");
}
