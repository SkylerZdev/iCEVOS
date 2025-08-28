#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "MyLib.h"

int opMenuPrincipal, opMenuEscalonador;

int main() {
    setlocale(LC_ALL, "Portuguese");

    do {
        system("cls");
        printf("|====== MENU PRINCIPAL ======|\n");
        printf("|1 - Escalonador de Processos|\n");
        printf("|         2 - Sair           |\n");
        printf("|==========================  |\n");
        printf("Escolha uma op��o: ");
        scanf("%d", &opMenuPrincipal);

        switch(opMenuPrincipal) {
            case 1: {
                do {
                    system("cls");
                    printf("|========= ESCALONADOR ===========|\n");
                    printf("|1 - Carregar processos do arquivo|\n");
                    printf("|2 - Executar ciclo �nico         |\n");
                    printf("|3 - Executar at� terminar        |\n");
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
                            if (todasListasVazias()) {
                                printf("Nenhum processo carregado!\n");
                            } else {
                                executarCiclo();
                            }
                            system("pause");
                            break;
                        case 3:
                            rodarEscalonador();
                            system("pause");
                            break;
                        case 4:
                            break;
                        default:
                            printf("Op��o inv�lida!\n");
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
                printf("Op��o inv�lida!\n");
                system("pause");
                break;
        }
    } while (opMenuPrincipal != 2);

    return 0;
}
