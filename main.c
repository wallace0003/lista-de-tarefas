#include <stdio.h>
#include "tarefas.h"
#include <string.h>

int main(){
    funcao fs[] = {criar, deletar, listar, salvar, carregar,exportar_tarefas_para_texto};

    Tarefa tarefas[TOTAL];
    int pos;
    ERROS erro = fs[4](tarefas, &pos);
    if(erro != OK)
        pos = 0;

    int opcao;
    do{
        printf("\nMenu principal\n");
        printf("1 - Criar tarefa\n");
        printf("2 - Deletar tarefa\n");
        printf("3 - Listar tarefas\n");
        printf("4 - Exportar tarefas para arquivo de texto\n");
        printf("0 - Sair\n");
        printf("Escolha uma opcao: ");

        scanf("%d", &opcao);
        opcao--;
        if(opcao > 3)
            printf("Opcao invalida\n");
        else if(opcao >= 0) {
          if (opcao == 2) {
              fs[opcao](tarefas, &pos);
          } 
          else if(opcao == 3){
              exportar_tarefas_para_texto(tarefas, &pos);
          }
            
          else {
              fs[opcao](tarefas, &pos);
          }
        } else {
            printf("Sair...\n");
        }

    } while(opcao >= 0);

    fs[3](tarefas, &pos);
}