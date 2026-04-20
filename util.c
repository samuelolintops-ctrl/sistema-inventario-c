#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "util.h"

void limpa_buffer(){
    /*
    Funcao para limpar o buffer do teclado.
    */
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void limpa_tela(){
    /*
    Funcao para limpar a tela do terminal. Portável para outros sistemas operacionais.
    */
    #ifdef _WIN32 //Windows
        system("cls");
    #else
        system("clear"); // Linux/MacOS/Unix
    #endif
}

void espera_enter(){
    /*
    Funcao para congelar a tela e esperar confirmacao do usuario para prosseguir.
    */
    printf("\nAperte \033[33mENTER\033[m para continuar...");
    getchar();
}

int recebe_inteiro_pos(char texto[]){
    /*
    Funcao para validar um numero inteiro positivo digitado pelo usuario.
    (limpa o buffer do teclado apos leitura)
    param texto: Frase para o usuario.
    return: retorna o valor validado.
    */
   int num, valida;
   while(1){
    printf("\n%s", texto);
    valida = scanf("%d", &num);
    limpa_buffer();
    if(valida == 1 && num >= 0) break;
    printf("\n\033[31mValor digitado invalido! Digite novamente.\033[m");
   }
   return num;
}

float recebe_float_pos(char texto[]){
    /*
    Funcao para validar um numero real positivo digitado pelo usuario.
    (limpa o buffer do teclado apos leitura)
    param texto: Frase para o usuario.
    return: retorna o valor validado.
    */
   float num;
   int valida;
   while(1){
    printf("\n%s", texto);
    valida = scanf("%f", &num);
    limpa_buffer();
    if(valida == 1 && num >= 0) break;
    printf("\n\033[31mValor digitado invalido! Digite novamente.\033[m");
   }
   return num;
}

void le_string(char mensagem[], char variavel[], size_t tam){
    /*
    Funcao que exibe um comando ao usuario e captura uma string digitada pelo usuario.
    param mensagem: string comando ao usuario.
    param variavel: vetor a ser manipulado.
    param tam: tamanho do vetor de char de 'variavel'.
    */
    printf("\n%s", mensagem);
    if(fgets(variavel, tam, stdin) != NULL){
        variavel[strcspn(variavel, "\n")] = '\0';
    }
}

int mostra_menu(char **lista_opcoes, int tam_list){
    /*
    Funcao para exibir um menu na tela enumerado.
    param lista_opcoes: lista com as opcoes do menu.
    param tam_list: quantidade de itens na lista.
    return: retorna um int definindo a opcao digitada pelo usuario.
    */
    int opc;
    while(1){
        limpa_tela();
        for(int i = 0; i < tam_list; i++){
            printf("\n%d. %s", i + 1, lista_opcoes[i]);
        }
        opc = recebe_inteiro_pos("Digite sua opcao: ");
        if(opc >= 1 && opc <= tam_list) break;
        printf("\033[31mOpcao invalida! Digite novamente.\033[m");
        espera_enter();
    }
    return opc;
}
