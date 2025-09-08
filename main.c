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
                    printf("|4 - Voltar ao menu principal     |\n");
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
                                printf("--------------------------------------------------\n");
                            }
                            system("pause");
                            break;
                        case 3:
                            rodarEscalonador(&escalonador);
                            system("pause");
                            break;
                        case 4:
                            break;
                        default:
                            printf("Opção inválida!\n");
                            system("pause");
                            break;
                    }
                } while (opMenuEscalonador != 4);
                break;
            }
            case 2:
                printf("Sair\n");
                break;
            default:
                printf("Opção inválida!\n");
                system("pause");
                break;
        }
    } while (opMenuPrincipal != 2);

    return 0 ;
}

