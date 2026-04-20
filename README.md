# Sistema de Inventário em C

Este é um projeto de gerenciamento de estoque desenvolvido para a disciplina de Linguagem de Programação II.

## Funcionalidades
* Cadastro de produtos com ID, nome, quantidade e preço.
* Listagem de itens.
* Busca rápida por ID usando.
* Atualização de estoque em arquivos binários.
* Relatório total de itens cadastrados.

## Compilar e Rodar
No Linux, use o GCC:
```bash
gcc main.c util.c inventario.c -o programa
./programa
