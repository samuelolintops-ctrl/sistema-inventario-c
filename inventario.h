#ifndef INVENTARIO_H
#define INVENTARIO_H

#define NOME_ARQUIVO "estoque.bin"

typedef struct{
    int id;
    char nome[50];
    int quantidade;
    float preco;
    int ativo; //1 ativo e 0 inativo
}Produto;

int verifica_arquivo(FILE *ponteiro_arquivo);
long busca_id(int id_prod);
void cadastro();
void listagem_itens();
void busca_item();
void atualiza_estq();
void relatorio_estq();

#endif
