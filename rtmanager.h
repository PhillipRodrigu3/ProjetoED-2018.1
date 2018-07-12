/* Estruturas a serem utilizadas pelo programa sendo
   as estruturas com o "_p" no final as resposaveis
   por gerar o ID de acordo com a ordem de inserção
   e também apontar o inicio de cada estrutura.*/

typedef enum {false, true} boolean;

#define NOME_MAX 30

typedef struct elem {
    char nome[NOME_MAX]; 
    int id;
    union{
        struct{
        int ip[4];
        char prioridade;
        };
        int tamanho;
    };
    struct elem *prox;
}elemento;

typedef struct elem_p{
    char tipo;          //flag sera igual a 0 quando for elemento do tipo computador e 1 caso for recurso.
    elemento *inicio;
    int id;

}lst_elementos;

typedef struct download{
    elemento *arq_atual;
    float   tam_atual;
    int count_ciclos;     //variavel pra contar os ciclos
    float velocidade_arq; //atribuir no inicio de cada ciclo
}down;

typedef struct download_p{
    down* inicio;
    int id;
}lst_downloads;

typedef struct passo{
    lst_downloads *lista;
    elemento   computador;
    float velocidade_com; //atribuir no inicio do ciclo
    struct passo *prox;
} elemciclo;

typedef struct ciclo_p{
    elemciclo* inicio;
    int id, ativos;
}lst_ciclo;


typedef struct hist_down{
    elemento arq, com;      //informa o computador usado e o arquivo baixado
    int ciclos;             //quantidade de ciclos necessaria pra acabar o down
    struct historico *prox;
}elemhist;

typedef elemhist* historico;

/*typedef struct historico_p{
    elemhist *inicio;
    elemhist *fim;
}*/


//IP
void scan_ip(int *ip);

void print_ip(int ip[]); 

int valida_ip(int *ip, lst_elementos com);

//ESTRUTURA
void inicia_vars_simulador(lst_elementos *com, lst_elementos *arq, lst_ciclo *elem, lst_downloads *downs, historico *baixados);

boolean vazia_comp (lst_elementos com);

boolean vazia_arq (lst_elementos arq);

int cadastrar_comp (lst_elementos* comp, char nome[], int ip[], char prior);

int cadastrar_rec (lst_elementos* arq, char* nome_arq, int tam);

void listar_elementos (lst_elementos lista);

boolean validaid_elem(lst_elementos elemento, int id);
