#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    int prioridade;
    printf("Entre com a prioridade (1 a 10): ");
    scanf("%d", &prioridade);
    clearBuffer();

    if (prioridade < 1 || prioridade > 10) {
        printf("Prioridade invalida. Deve estar entre 1 e 10.\n");
        return OK;
    }

    tarefas[*pos].prioridade = prioridade;

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, tamanhocategoria, stdin);
    size_t len_cat = strlen(tarefas[*pos].categoria);
    if (tarefas[*pos].categoria[len_cat - 1] == '\n')
        tarefas[*pos].categoria[len_cat - 1] = '\0';

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, tamanhodescricao, stdin);
    size_t len_desc = strlen(tarefas[*pos].descricao);
    if (tarefas[*pos].descricao[len_desc - 1] == '\n')
        tarefas[*pos].descricao[len_desc - 1] = '\0';

    (*pos)++;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos){
    // teste se existem tarefas
    if(*pos == 0)
        return SEM_TAREFAS;

    // verifica se a tarefa escolhida existe
    int pos_deletar;
    printf("Entre com a posicao da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--; // garantir posicao certa no array
    if(pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for(int i = pos_deletar; i < *pos; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao,  tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
    if (*pos == 0) {
        return SEM_TAREFAS;
    }

    char categoria[tamanhocategoria];
    printf("Entre com a categoria (ou deixe em branco para exibir todas as tarefas): ");


    clearBuffer();

    if (fgets(categoria, sizeof(categoria), stdin) == NULL) {
        return LER;
    }

    size_t len_cat = strlen(categoria);
    if (categoria[len_cat - 1] == '\n') {
        categoria[len_cat - 1] = '\0';
    }

    printf("Categoria lida: '%s'\n", categoria);

    int encontrou_tarefa = 0;

    for (int i = 0; i < *pos; i++) {
        if (categoria[0] == '\0' || strcmp(tarefas[i].categoria, categoria) == 0) {
            encontrou_tarefa = 1;
            printf("Prioridade: %d\tCategoria: %s\tDescricao: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
        }
    }

    if (!encontrou_tarefa && categoria[0] != '\0') {
        printf("Nenhuma tarefa encontrada para a categoria '%s'\n", categoria);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, 1, sizeof(int), f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    return OK;
}

ERROS exportar(Tarefa tarefas[], int *pos) {
    char nome_arquivo[100];
    printf("Digite o nome do arquivo para exportar: ");
    scanf("%s", nome_arquivo);

    FILE *arquivo = fopen(nome_arquivo, "w");
    if (arquivo == NULL) {
        return ABRIR;
    }

    for (int i = 0; i < pos; i++) {
        fprintf(arquivo, "Prioridade: %d\tCategoria: %s\tDescricao: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    fclose(arquivo);
    return OK;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
