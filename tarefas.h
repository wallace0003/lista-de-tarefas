#define TOTAL 100
#define T_Categoria 100
#define T_Descricao 300

typedef struct {
    int prioridade;
    char descricao[T_Descricao];
    char categoria[T_Categoria];
} Tarefa;

typedef enum {OK, MAX_TAREFA, SEM_TAREFAS, NAO_ENCONTRADO, ABRIR, FECHAR, ESCREVER, LER} ERROS;

typedef ERROS (*funcao)(Tarefa[], int*);

ERROS criar(Tarefa tarefas[], int *pos);
ERROS deletar(Tarefa tarefas[], int *pos);
ERROS listar(Tarefa tarefas[], int *pos);
ERROS salvar(Tarefa tarefas[], int *pos);
ERROS carregar(Tarefa tarefas[], int *pos);


ERROS exportar_tarefas_txt(Tarefa tarefas[], int *pos);



void clearBuffer();
