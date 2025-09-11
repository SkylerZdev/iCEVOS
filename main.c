#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "MyLib.h"


int opMenuPrincipal, opMenuEscalonador;

int main() {
    setlocale(LC_ALL, "Portuguese");
	system("color A");

    do {
        system("cls");
        printf("|====== MENU PRINCIPAL ======|\n");
        printf("|1 - Escalonador de Processos|\n");
        printf("|         2 - Sair           |\n");
        printf("|==========================  |\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opMenuPrincipal);

        switch(opMenuPrincipal) {
            case 1: {
                do {
                    system("cls");
                    printf("|========= ESCALONADOR ===========|\n");
                    printf("|1 - Carregar processos do arquivo|\n");
                    printf("|2 - Executar ciclo unico         |\n");
                    printf("|3 - Executar ate terminar        |\n");
                    printf("|4 - Impressao de Filas           |\n");
                    printf("|5 - Voltar ao menu principal     |\n");
					printf("|=================================|\n");
                    printf("Escolha: ");
                    scanf("%d", &opMenuEscalonador);

                    switch(opMenuEscalonador) {
                        case 1:
                            carregarProcessos();
                            system("pause");
                            break;
                        case 2:
   						 if (todasListasVazias(&escalonador)) {
        					 printf("Nenhum processo carregado!\n");
   						 } else {
        					 rodarEscalonadorUnico(&escalonador);
       						 imprimirFilasTodas(&escalonador);
    					 }
   						 system("pause");
    					 break;
                        case 3:	{
 							int Escolha;
 							printf("|Aviso| Deseja imprimir as filas apos cada ciclo?\n");
							printf("Essa opção resultara em muitas saidas no console e pode deixar a execucao mais lenta.\n");
							printf("Digite 1 para SIM ou 0 para NAO: "); scanf("%d", &Escolha);
     					 if(Escolha == 1) {
    					 //rodarEscalonadorImp(&escalonador); Implementação no proximo commit
    					 } else {
      					   rodarEscalonador(&escalonador);
    					 }
   						 system("pause");
  						 break;
						}
                        case 4:
                            do {
                                system("cls");
                                printf("|======= IMPRESSAO DE FILAS =======|\n");
                                printf("|1 - Imprimir fila de alta prioridade|\n");
                                printf("|2 - Imprimir fila de media prioridade|\n");
                                printf("|3 - Imprimir fila de baixa prioridade|\n");
                                printf("|4 - Imprimir fila de bloqueados      |\n");
                                printf("|5 - Imprimir todas as filas          |\n");
                                printf("|6 - Voltar ao menu anterior          |\n");
                                printf("|====================================|\n");
                                printf("Escolha: ");
                                scanf("%d", &opMenuImpressao);
                                switch(opMenuImpressao) {
                                    case 1:
                                        imprimirFila(&escalonador.Alta, "Alta Prioridade");
                                        system("pause");
                                        break;
                                    case 2:
                                        imprimirFila(&escalonador.Media, "Media Prioridade");
                                        system("pause");
                                        break;
                                    case 3:
                                        imprimirFila(&escalonador.Baixa, "Baixa Prioridade");
                                        system("pause");
                                        break;
                                    case 4:
                                        imprimirFila(&escalonador.Bloqueados, "Bloqueados");
                                        system("pause");
                                        break;
                                    case 5:
                                        imprimirFilasTodas(&escalonador);
                                        system("pause");
                                        break;
                                    case 6:
                                        printf("Voltando ao menu anterior...\n");
                                        break;
                                    default:
                                        printf("Opcao invalida!\n");
                                        system("pause");
                                        break;
                                  }
                                } while (opMenuImpressao != 6);
                            break; 
                        case 5:
                            break;
                        default:
                            printf("Opcao invalida!\n");
                            system("pause");
                            break;
                    }
                 } while (opMenuEscalonador != 5);
                 break;
            }
    return 0 ;
}

