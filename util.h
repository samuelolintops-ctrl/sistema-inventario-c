#ifndef UTIL_H
#define UTIL_H

void limpa_buffer();
void limpa_tela();
void espera_enter();
int recebe_inteiro_pos(char texto[]);
float recebe_float_pos(char texto[]);
void le_string(char mensagem[], char variavel[], size_t tam);
int mostra_menu(char **lista_opcoes, int tam_list);

#endif
