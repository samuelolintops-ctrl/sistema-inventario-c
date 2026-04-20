#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "inventario.h"
#include "util.h"

int verifica_arquivo(FILE *ponteiro_arquivo){
    /*
    Funcao que verifica a abertura de um arquivo.
    param ponteiro_arquivo: stream/ponteiro do arquivo aberto a se verificar.
    return: retorna 1 em caso de falha na abertura do arquivo ou 0 em caso de sucesso.
    */
    if(ponteiro_arquivo == NULL){
        perror("\nFalha na abertura do arquivo");
        espera_enter();
        return 1;
    }
    return 0;
}

long busca_id(int id_prod){
    /*
    Funcao que procura o produto pelo id.
    param id_prod: id a ser procurado.
    return: retorna um long da posicao (onde comeca) do produto em bytes ou -1L em caso de erro ou nao existencia do produto
    */
    long posicao = -1L;
    Produto p;
    FILE *ptr_arq;
    ptr_arq = fopen(NOME_ARQUIVO, "rb"); //abre
    if(verifica_arquivo(ptr_arq) == 1) return posicao;
    while(fread(&p, sizeof(Produto), 1, ptr_arq) == 1){
        if(p.id == id_prod){
            posicao = ftell(ptr_arq) - sizeof(Produto);
            break;
        }
    }
    fclose(ptr_arq); //fecha
    return posicao;
}

void cadastro(){
    /*
    Funcao para cadastro de novos produtos.
    */
    int verifica;
    Produto p;
    FILE *ptr_arq;
    limpa_tela();
    printf("\033[1m--- MODULO DE CADASTRO ---\033[m\nDigite os dados do produto:");
    //captura os dados da struct
    p.id = recebe_inteiro_pos("\nID do produto: ");
    le_string("\nNome do produto (limite 49 caracteres): ", p.nome, sizeof(p.nome));
    p.quantidade = recebe_inteiro_pos("\nQuantidade de itens: ");
    p.preco = recebe_float_pos("\nValor do produto (individual): ");
    p.ativo = 1;
    //abre arquivo e escreve a struct nele
    ptr_arq = fopen(NOME_ARQUIVO, "ab"); //abre
    if((verifica_arquivo(ptr_arq)) == 1) return;
    verifica = fwrite(&p, sizeof(Produto), 1, ptr_arq);
    if(verifica != 1){
        perror("\nFalha na escrita dos dados no arquivo");
        return;
    }
    fclose(ptr_arq); //fecha
    printf("\033[32mProduto registrado com sucesso!\033[m");
    espera_enter();
}

void listagem_itens(){
    /*
    Funcao que exibe na tela os produtos que estao no arquivo.
    */
    FILE *ptr_arq;
    Produto p;
    limpa_tela();
    printf("\033[1m--- MODULO DE LISTAGEM ---\033[m");
    ptr_arq = fopen(NOME_ARQUIVO, "rb"); //abre
    if(verifica_arquivo(ptr_arq) == 1) return;
    //exibicao dos produtos cadastrados
    while(fread(&p, sizeof(Produto), 1, ptr_arq) == 1){
        printf("\nId: %d", p.id);
        printf("\nNome: %s", p.nome);
        printf("\nQuantidade: %d", p.quantidade);
        printf("\nPreco: %.2f", p.preco);
        printf("\nAtivo? %d", p.ativo);
        printf("\n--------------------");
    }
    printf("\n(1 para ativo e 0 para inativo/excluido)");
    fclose(ptr_arq); //fecha
    espera_enter();
}

void busca_item(){
    /*
    Funcao que busca um produto pelo seu id e exibe sua descricao.
    */
    int id, verifica;
    long posicao_item;
    Produto p;
    FILE *ptr_arq;
    limpa_tela();
    printf("\033[1m--- MODULO DE BUSCA ---\033[m");
    id = recebe_inteiro_pos("\nDigite o id do produto para busca: ");
    posicao_item = busca_id(id);
    if(posicao_item == -1L){
        printf("\n\033[31mNenhum item com esse id!\033[m");
        espera_enter();
        return;
    }
    ptr_arq = fopen(NOME_ARQUIVO, "rb"); //abre
    if(verifica_arquivo(ptr_arq) == 1) return;
    fseek(ptr_arq, posicao_item, SEEK_SET);
    verifica = fread(&p, sizeof(Produto), 1, ptr_arq);
    if(verifica != 1){
    printf("\n\033[31mErro na leitura do produto.\033[m");
    fclose(ptr_arq);
    espera_enter();
    return;
    }
    printf("\n\033[1mDescricao do produto:\033[m");
    printf("\nId: %d", p.id);
    printf("\nNome: %s", p.nome);
    printf("\nQuantidade: %d", p.quantidade);
    printf("\nPreco: %.2f", p.preco);
    printf("\nAtivo? %d", p.ativo);
    printf("\n(1 para ativo e 0 para inativo/excluido)");
    printf("\n--------------------");
    fclose(ptr_arq); //fecha
    espera_enter();

}

void atualiza_estq(){
    /*
    Funcao que busca um item pelo seu id e opera para mudar a quantidade de itens daquele produto.
    */
    int id, nova_qtd, verifica;
    long posicao_item;
    Produto p;
    FILE *ptr_arq;
    limpa_tela();
    printf("\033[1m--- MODULO DE ATUALIZACAO DE ESTOQUE ---\033[m");
    //captura do id
    id = recebe_inteiro_pos("\nDigite o id do produto para busca: ");
    posicao_item = busca_id(id);
    if(posicao_item == -1L){
        printf("\n\033[31mNenhum item com esse id!\033[m");
        espera_enter();
        return;
    }
    ptr_arq = fopen(NOME_ARQUIVO, "r+b"); //abre
    if(verifica_arquivo(ptr_arq) == 1) return;
    //exibicao do produto a ser alterado
    fseek(ptr_arq, posicao_item, SEEK_SET);
    verifica = fread(&p, sizeof(Produto), 1, ptr_arq);
    if(verifica != 1){
        printf("\n\033[31mErro na leitura do produto.\033[m");
        fclose(ptr_arq);
        espera_enter();
        return;
    }
    printf("\n\033[1mDescricao do produto:\033[m");
    printf("\nId: %d", p.id);
    printf("\nNome: %s", p.nome);
    printf("\nQuantidade: %d", p.quantidade);
    printf("\nPreco: %.2f", p.preco);
    printf("\nAtivo? %d", p.ativo);
    printf("\n(1 para ativo e 0 para inativo/excluido)");
    printf("\n--------------------");
    //nova quantidade de estoque
    nova_qtd = recebe_inteiro_pos("\nDigite a nova quantidade de estoque do produto: ");
    p.quantidade = nova_qtd;
    fseek(ptr_arq, posicao_item, SEEK_SET);
    verifica = fwrite(&p, sizeof(Produto), 1, ptr_arq);
    if(verifica != 1){
        printf("\n\033[31mErro na escrita da nova quantidade.\033[m");
        fclose(ptr_arq);
        espera_enter();
        return;
    }
    printf("\n\033[32mProduto alterado com sucesso!\033[m");
    fclose(ptr_arq); //fecha
    espera_enter();
}

void relatorio_estq(){
    /*
    Funcao que exibe a quantidade de itens diferentes em estoque.
    */
    long tam_arq;
    int qtd_itens;
    FILE *ptr_arq;
    limpa_tela();
    printf("\033[1m--- MODULO DE RELATORIO ---\033[m");
    ptr_arq = fopen(NOME_ARQUIVO, "rb"); //abre
    if(verifica_arquivo(ptr_arq) == 1) return;
    fseek(ptr_arq, 0, SEEK_END);
    tam_arq = ftell(ptr_arq);
    qtd_itens = tam_arq / sizeof(Produto);
    printf("\nA quantidade de itens no estoque e de: %d.", qtd_itens);
    fclose(ptr_arq); //fecha
    espera_enter();
}
