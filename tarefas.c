#include <stdio.h>
#include <string.h>
#include "tarefas.h"

ERROS criar(Tarefa tarefas[], int *pos){
    if(*pos >= TOTAL)
        return MAX_TAREFA;

    int prioridade;
    do{
        printf("Entre com a prioridade (Digite valores entre 1 e 10): ");
        scanf("%d", &prioridade);

        if (prioridade > 10 || prioridade < 1){
            printf("Valor invalido\n");
        }
    } while (prioridade > 10 || prioridade < 1);
    tarefas[*pos].prioridade = prioridade;

    clearBuffer();

    printf("Entre com a categoria: ");
    fgets(tarefas[*pos].categoria, T_Categoria, stdin);
    tarefas[*pos].categoria[strcspn(tarefas[*pos].categoria, "\n")] = '\0';

    printf("Entre com a descricao: ");
    fgets(tarefas[*pos].descricao, T_Descricao, stdin);
    tarefas[*pos].descricao[strcspn(tarefas[*pos].descricao, "\n")] = '\0';

    *pos = *pos + 1;

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

    for(int i = pos_deletar; i < *pos - 1; i++){
        tarefas[i].prioridade = tarefas[i+1].prioridade;
        strcpy(tarefas[i].categoria, tarefas[i+1].categoria);
        strcpy(tarefas[i].descricao, tarefas[i+1].descricao);
    }

    *pos = *pos - 1;

    return OK;
}

ERROS listar(Tarefa tarefas[], int *pos) {
    if (*pos == 0) {
        return SEM_TAREFAS;
    }

    char categoria[100];

    printf("Digite a categoria que deseja listar (deixe em branco para exibir todas): ");
    clearBuffer();
    fgets(categoria, 100, stdin);

    categoria[strcspn(categoria, "\n")] = '\0';

    int encontrou = 0;

    if (categoria[0] == '\0') {
        for (int i = 0; i < *pos; i++) {
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
        return OK;
    }

    for (int i = 0; i < *pos; i++) {
        if (strcmp(categoria, tarefas[i].categoria) == 0) {
            encontrou = 1;
            printf("Pos: %d\t", i + 1);
            printf("Prioridade: %d\t", tarefas[i].prioridade);
            printf("Categoria: %s\t", tarefas[i].categoria);
            printf("Descricao: %s\n", tarefas[i].descricao);
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada para a categoria \"%s\".\n", categoria);
    }

    return OK;
}

ERROS salvar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "wb");
    if(f == NULL)
        return ABRIR;

    int qtd = fwrite(tarefas, sizeof(Tarefa), TOTAL, f);
    if(qtd == 0)
        return ESCREVER;

    qtd = fwrite(pos, sizeof(int), 1, f);
    if(qtd == 0)
        return ESCREVER;

    if(fclose(f))
        return FECHAR;

    printf("\nArquivo salvo com sucesso\n");
    return OK;
}

ERROS carregar(Tarefa tarefas[], int *pos){
    FILE *f = fopen("tarefas.bin", "rb");
    if(f == NULL)
        return ABRIR;

    int qtd = fread(tarefas, sizeof(Tarefa), TOTAL, f);
    if(qtd == 0)
        return LER;

    qtd = fread(pos, sizeof(int), 1, f);
    if(qtd == 0)
        return LER;

    if(fclose(f))
        return FECHAR;

    printf("\nTarefas carregadas com sucesso!\n");
    return OK;
}

ERROS exportar_tarefas_txt(Tarefa tarefas[], int *pos) {
    char nome_arquivo[50];
    char txt[] = ".txt";
    printf("Digite o nome do arquivo para exportar: ");
    clearBuffer();
    fgets(nome_arquivo, 50, stdin);

    nome_arquivo[strcspn(nome_arquivo, "\n")] = '\0';
    strcat(nome_arquivo, txt);

    FILE *f = fopen(nome_arquivo, "w");
    if (f == NULL)
        return ABRIR;

    char categoria[100];
    printf("Digite a categoria que deseja exportar (deixe em branco para exportar todas): ");
    fgets(categoria, 100, stdin);
    categoria[strcspn(categoria, "\n")] = '\0';

    int encontrou = 0;
    if (categoria[0] == '\0') {
        for (int i = 0; i < *pos; i++) {
            fprintf(f, "Prioridade: %d\n", tarefas[i].prioridade);
            fprintf(f, "Categoria: %s\n", tarefas[i].categoria);
            fprintf(f, "Descricao: %s\n", tarefas[i].descricao);
            fprintf(f, "\n");
        }
        encontrou = 1;
    } else {
        for (int i = 0; i < *pos; i++) {
            if (strcmp(categoria, tarefas[i].categoria) == 0) {
                encontrou = 1;
                fprintf(f, "Prioridade: %d\n", tarefas[i].prioridade);
                fprintf(f, "Categoria: %s\n", tarefas[i].categoria);
                fprintf(f, "Descricao: %s\n", tarefas[i].descricao);
                fprintf(f, "\n");
            }
        }
    }

    if (!encontrou) {
        printf("Nenhuma tarefa encontrada para a categoria \"%s\".\n", categoria);
    }

    if (fclose(f) != 0)
        return FECHAR;

    if (encontrou) {
        printf("Arquivo exportado com sucesso!\n");
    }
    return OK;
}


int verificErros(ERROS erro){
    switch (erro){
        case MAX_TAREFA:
            printf("\nNúmero máximo de tarefas alcançado.\n");
            break;

        case SEM_TAREFAS:
            printf("\nNão foram encontradas tarefas salvas.\n");
            break;

        case NAO_ENCONTRADO:
            printf("\nNenhuma tarefa encontrada.\n");
            break;

        case ABRIR:
            printf("\nErro ao abrir o arquivo de tarefas.\n");
            break;

        case FECHAR:
            printf("\nErro ao fechar o arquivo de tarefas.\n");
            break;

        case ESCREVER:
            printf("\nErro ao escrever no arquivo de tarefas.\n");
            break;

        case LER:
            printf("\nErro ao ler o arquivo de tarefas.\n");
            break;
        default:
            break;
    }
    return erro;
}

void clearBuffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
