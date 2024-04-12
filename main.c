#include <stdio.h>
#include "tarefas.h"

int main() {
    funcao fs[] = {criar, deletar, listar, salvar, carregar, exportar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if (erro != OK) {
        printf("Erro ao carregar tarefas. Reiniciando posicao.\n");
        pos = 0;
    }

    int opcao;
    do {
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas para arquivo de texto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);

        if(opcao==4){
            printf("arquivo salvo\n");
        }


        if (opcao < 0 || opcao > 4) { // Modifiquei o limite superior para 4
            printf("Opcao invalida\n");
            continue;
        }

        if (opcao == 0)
            break;

        erro = fs[opcao - 1](tarefas, &pos);
        if (erro != OK) {
            printf("Erro ao executar a operacao.\n");
        }

    } while (opcao >= 0);

    erro = fs[3](tarefas, &pos);
    if (erro != OK) {
        printf("Erro ao salvar tarefas.\n");
    }
    return 0;

}
