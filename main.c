#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "inventario.h"

// gcc main.c inventario.c util.c -o programa
// ./programa

int main(){
    int opcao;
    int qtd_opcao;
    char *lst_opc[] = {
        "Cadastro",
        "Listagem Total",
        "Busca Rapida",
        "Atualizar Estoque",
        "Relatorio Estoque",
        "Sair"
    };
    qtd_opcao = sizeof(lst_opc) / sizeof(lst_opc[0]);
    while(1){
        opcao = mostra_menu(lst_opc, qtd_opcao);
        switch(opcao)
        {
        case 1:
            cadastro();
            break;
        case 2:
            listagem_itens();
            break;
        case 3:
            busca_item();
            break;
        case 4:
            atualiza_estq();
            break;
        case 5:
            relatorio_estq();
            break;
        case 6:
            printf("\nSaindo do sistema. Ate mais!\n");
            return 0;
        }
    }
    return 0;
}
