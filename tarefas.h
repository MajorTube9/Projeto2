#ifndef TAREFAS_H
#define TAREFAS_H

#include <stdio.h>

#define TOTAL 100
#define tamanhodescricao  300
#define tamanhocategoria 100

typedef struct {
    int prioridade;
    char descricao[tamanhodescricao];
    char categoria[tamanhocategoria];
} Tarefa;

typedef enum {
    OK,
    MAX_TAREFA,
    SEM_TAREFAS,
    NAO_ENCONTRADO,
    ABRIR,
    FECHAR,
    ESCREVER,
    LER
} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);
ERROS exportar(Tarefa tarefas[], int *pos);

void clearBuffer();

#endif
