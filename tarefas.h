#ifndef TAREFAS_H
#define TAREFAS_H

#define TOTAL 100
#define tamanhodescricao  300
#define tamanhocategoria 100

#include <stdio.h>

void clearBuffer();

typedef struct {
    int prioridade;
    char descricao[tamanhodescricao];
    char categoria[tamanhocategoria];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*, const char*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos, const char *nome_arquivo);
ERROS salvarTexto(Tarefa tarefas[], int *pos, const char *nome_arquivo);






#endif
