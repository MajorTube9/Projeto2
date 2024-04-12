#include <stdio.h>
#include "tarefas.h"

int main() {
    char nome_arquivo[] = "./tarefas.bin";

    // Ajustando o tamanho do array para seis e removendo a função carregar da lista
    funcao fs[6] = {criar, deletar, listar, salvarTexto, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[5](tarefas, &pos, nome_arquivo); // Carregar as tarefas do arquivo
    if (erro != OK) {
        printf("Erro ao carregar tarefas. Reiniciando posição.\n");
        pos = 0;
    }

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Salvar tarefas em arquivo de texto\n");
        printf("5 - Salvar tarefas em arquivo binário\n");
        printf("6 - Carregar tarefas de arquivo binário\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");

        scanf("%d", &opcao);
        if (opcao < 0 || opcao > 6) {
            printf("Opção inválida\n");
            continue;
        }

        erro = fs[opcao - 1](tarefas, &pos, nome_arquivo);
        if (erro != OK) {
            printf("Erro ao executar a operação.\n");
        }

    } while (opcao != 0);

    erro = fs[4](tarefas, &pos, nome_arquivo); // Salvar as tarefas no arquivo binário
    if (erro != OK) {
        printf("Erro ao salvar tarefas.\n");
    }
    return 0;
}
