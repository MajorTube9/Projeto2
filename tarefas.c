#include <stdio.h>
#include <string.h>
#include "tarefas.h"
void clearBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}




ERROS criar(Tarefa tarefas[], int *pos) {
    if (*pos >= TOTAL)
        return MAX_TAREFA;

    int prioridade;
    printf("Entre com a prioridade (1 a 10): ");
    scanf("%d", &prioridade);
    clearBuffer();

    if (prioridade < 1 || prioridade > 10) {
        printf("Prioridade inválida. Deve estar entre 1 e 10.\n");
        return OK;
    }

    tarefas[*pos].prioridade = prioridade;

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, tamanhocategoria, stdin);
    size_t len_cat = strlen(tarefas[*pos].categoria);
    if (tarefas[*pos].categoria[len_cat - 1] == '\n')
        tarefas[*pos].categoria[len_cat - 1] = '\0';

    printf("Entre com a descrição: ");
    fgets(tarefas[*pos].descricao, tamanhodescricao, stdin);
    size_t len_desc = strlen(tarefas[*pos].descricao);
    if (tarefas[*pos].descricao[len_desc - 1] == '\n')
        tarefas[*pos].descricao[len_desc - 1] = '\0';

    (*pos)++;

    return OK;
}

ERROS deletar(Tarefa tarefas[], int *pos) {
    if (*pos == 0)
        return SEM_TAREFAS;

    int pos_deletar;
    printf("Entre com a posição da tarefa a ser deletada: ");
    scanf("%d", &pos_deletar);
    pos_deletar--;
    if (pos_deletar >= *pos || pos_deletar < 0)
        return NAO_ENCONTRADO;

    for (int i = pos_deletar; i < *pos; i++) {
        tarefas[i] = tarefas[i + 1];
    }

    (*pos)--;

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
            printf("Prioridade: %d\tCategoria: %s\tDescrição: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
        }
    }

    if (!encontrou_tarefa && categoria[0] != '\0') {
        printf("Nenhuma tarefa encontrada para a categoria '%s'\n", categoria);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos) {
    FILE *f = fopen("tarefas.bin", "wb");
    if (f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, *pos, sizeof(Tarefa), f);
    if (qtd == 0)
        return ESCREVER;

    if (fclose(f))
        return FECHAR;

    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos, const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "rb");
    if (f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, TOTAL, sizeof(Tarefa), f);
    if (qtd == 0)
        return LER;

    *pos = qtd;

    if (fclose(f))
        return FECHAR;

    return OK;
}

ERROS salvarTexto(Tarefa tarefas[], int *pos, const char *nome_arquivo) {
    char nome_arquivo_texto[100];
    printf("Digite o nome do arquivo de texto para salvar as tarefas: ");
    clearBuffer(); // Limpa o buffer de entrada antes de ler o nome do arquivo
    fgets(nome_arquivo_texto, sizeof(nome_arquivo_texto), stdin); // Lê o nome do arquivo de texto

    // Remove a quebra de linha do final, se houver
    size_t len = strlen(nome_arquivo_texto);
    if (nome_arquivo_texto[len - 1] == '\n') {
        nome_arquivo_texto[len - 1] = '\0';
    }

    FILE *f = fopen(nome_arquivo_texto, "w");
    if (f == NULL)
        return ABRIR;

    for (int i = 0; i < *pos; i++) {
        fprintf(f, "Prioridade: %d\tCategoria: %s\tDescrição: %s\n", tarefas[i].prioridade, tarefas[i].categoria, tarefas[i].descricao);
    }

    if (fclose(f) != 0)
        return FECHAR;

    return OK;
}
