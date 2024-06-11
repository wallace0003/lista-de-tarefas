#include <stdio.h>
#include "tarefas.h"
#include <string.h>

int main(){
    funcao fs[] = {criar, deletar, listar, exportar_tarefas_txt, salvar, carregar};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[5](tarefas, &pos); // Corrigir erro de carregar ao iniciar
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n"); 
        printf("1 - Criar tarefa\n"); // 0
        printf("2 - Deletar tarefa\n"); // 1
        printf("3 - Listar tarefas\n"); // 2
        printf("4 - Exportar tarefas para arquivo de texto\n"); // 3
        printf("5 - Salvar tarefas em arquivo binário\n"); // 4
        printf("6 - Carregar tarefas de arquivo binário\n"); // 5
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao > 5 || opcao < -1)
            printf("Opcao invalida\n");
        else if(opcao >= 0) {
            erro = fs[opcao](tarefas, &pos);
            if (erro != OK) {
                verificErros(erro);
            }
        } else {
            printf("Sair...\n");
        }

    } while(opcao >= 0);

    erro = fs[4](tarefas, &pos); // Salvar ao sair
    if (erro != OK) {
        verificErros(erro);
    }

    return 0;
}
