/* 
    Estruturas a serem utilizadas pelo programa sendo
    as estruturas com o "_p" no final as resposaveis
    por gerar o ID de acordo com a ordem de inserção
    e também apontar o inicio de cada estrutura.*/

/*  
    Legenda para palavras encurtadas:
        Arq  : arquivo(recurso)
        Com  : computador(es)
        Count: contador
        Elem : elemento
        prior: prioridade
        Tam  : tamanho
        
*/
typedef enum {false, true} boolean;

#define NOME_MAX 30 //Tamanho das strings de nome para recursos e computadores

/*
    DESCRIÇÃO: struct elem 
    Estrutura responsavel por armazenar os dados dos elementos de arquivo e computadores como:
    Nome(com/arq), ip(com), prioridade(com), tamanho(arquivos apenas).
    
*/
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
    int count_ciclos, id;     //variavel pra contar os ciclos
    float velocidade_arq; //atribuir no inicio de cada ciclo
    struct download *prox;
}down;

typedef struct download_p{
    down* inicio;
    int id;
}lst_downloads;

typedef struct passo{
    lst_downloads *lista_downs;
    elemento   *computador;
    float velocidade_com; //atribuir no inicio do ciclo
    struct passo *prox;
    int id;
    //boolean ativo;
} elemciclo;

typedef struct ciclo_p{
    elemciclo* inicio;
    int id;
}lst_ciclo;


typedef struct hist_down{
    elemento *arq, *com;      //informa o computador usado e o arquivo baixado
    int ciclos;             //quantidade de ciclos necessaria pra acabar o down
    float velocidade_final;
    struct hist_down *prox;
}elemhist;

typedef elemhist* historico;


//IP

/*
    Descrição:  scan_ip
        Recebe o ip no padrão XXX.XXX.XXX.XXX e insere no vetor de forma apropriada
    Parametros: 
        int *ip - ponteiro para o vetor que irá conter ip
     
*/

void scan_ip(int *ip);

/*
    Descrição:  print_ip
        printa o vetor na tela no formato XXX.XXX.XXX.XXX
    Parametros: 
        int ip[] - vetor que contem o ip
     
*/

void print_ip(int ip[]); 

/*
    Descrição:  valida_ip
        checa se o ip inserido é válido
    Parametros:
        int *ip       - ponteiro do vetor que contém o ip;
        lst_elementos - lista de computadores para pesquisar caso o ip for duplicado
    Retornos:
         1: Ip Valido
        -4: primeiro campo é igual a 0
        -5: Maior ou menor que a range permitida (0-255)
        -6: Esse ip já está em uso

*/

int valida_ip(int *ip, lst_elementos com);

//ESTRUTURA

/*
    Descrição:  inicia_vars_simulador
        Inicia as variaveis necessarias para a simulação
    Parametros:
        lst_elementos *com  - Lista de elementos por referencia a ser iniciada como computadores
        lst_elementos *arq  - Lista de elementos por referencia a ser iniciada como recursos
        lst_ciclo *elem     - Lista do ciclo por referencia a ser iniciada
        historico *baixados - Lista de downloads a terminados a ser iniciada
     
*/

void inicia_vars_simulador(lst_elementos *com, lst_elementos *arq, lst_ciclo *elem, historico *baixados);

/*
    Descrição:  lst_vazia
        Checa se a lista de elementos enviada está vazia
    Parametros:
        lst_elementos elem - lista de elementos por valor
    Retornos: 
        True: A lista está vazia
        False: A lista contém ao menos 1 elemento
*/

boolean lst_vazia (lst_elementos elem);

/*
    Descrição: cadastrar_computadores
    Parametros: 
        lst_elementos* comp - Lista de elementos do tipo computadores por referencia
        char nome[]         - String por valor do nome do computador
        int ip[]            - IP a ser atribuido ao computador
        char prior          - flag de prioridade ('1' ou '0')
    Retornos:
         1: Cadastrado com sucesso
        -1: Não conseguiu alocar o novo elemento
        -2: String de nome passada é invalida

*/

int cadastrar_computadores (lst_elementos* comp, char nome[], int ip[], char prior);

/*
    Descrição:  cadastrar_recursos
        Cadastra recursos(arquivos) na lista enviada
    Parametros:
        lst_elementos *arq - Uma lista de arquivos por referencia
        char nome[]        - String por valor do nome do arquivo
        int tam - inteiro com o tamanho do arquivo
    Retornos:
         1: Cadastrado com sucesso
        -1: Não conseguiu alocar o novo elemento
        -2: String de nome passada é invalida
 
*/

int cadastrar_recursos (lst_elementos* arq, char nome[], int tam);

/*
    Descrição:  listar_elementos
        A função printa na tela todos os elementos da lista
        e suas caracteristicas
    Parametros: 
        lst_elementos lista - lista de elementos por valor
    
*/

void listar_elementos (lst_elementos lista);

/*
    Descrição:  valida_id_elemento
        Checa se o ID enviado é valido, ou seja,
        possui um elemento relacionado a ele.
    Parametros: 
        lst_elementos elemento - lista por valor
        int id - id a ser consultado
    Retornos: 
        True:  ID valido, contém um elemento relacionado
        False: ID invalido, não há elemento com esse ID
*/

boolean valida_id_elemento(lst_elementos elemento, int id);

/*
    Descrição: cadastrar_job
        Cadastra jobs no ciclo, insere downloads a
        serem feitos na execução.
    Parametros:
        lst_elementos *com  - Lista de computadores por referencia a ser percorrida
        lst_elementos *arq  - Lista de recursos por referencia a ser percorrida
        lst_ciclo *elem     - Lista do ciclo por referencia a ser preenchida
        int id_com          - id do computador que será usado no job
        int id_arq          - Id do arquivo que será posto para baixar
    Retornos:
         1 : Cadastrado com sucesso
        -1 : Problema na alocação
        -3 : ID invalido
        
*/

int cadastrar_job(lst_elementos *com, lst_elementos *arq, lst_ciclo *ciclo, int id_com, int id_arq);
/*
    Descrição:  listar_historico
        Lista os downloads terminados na ordem,
        mostrando quantos ciclos foram necessarios,
        o nome do arquivo baixado e o computador
        que o baixou.
    Parametros: 
        historico terminados - lista de downloads terminados por valor
*/

void listar_historico (historico terminados);

/*
    Descrição: povoamento_auto
        Preenche os campos necessarios para iniciar
        a simulação, não impedindo a inserção de 
        novos elementos.
    Parametros:
        lst_elementos *com  - Lista de computadores por referencia a ser preenchida
        lst_elementos *arq  - Lista de recursos por referencia a ser preenchida
        lst_ciclo *elem     - Lista do ciclo por referencia a ser preenchida
    Retornos:
        True: Conseguiu preencher sem problemas
        False: Não foi possivel preencher
*/
boolean povoamento_auto(lst_elementos *com, lst_elementos *arq, lst_ciclo *ciclo);

/*
    Descrição: print_ciclo
        Responsavel por mostrar o status dos jobs
        em cada ciclo de forma a informar o 
        usuario qual o progresso em cada ciclo
    Parametros:
        lst_ciclo ciclo - Lista do ciclo por copia
*/

void print_ciclo(lst_ciclo ciclo);

/*
    Descrição: print_returno
        Retorna uma mensagem relativa ao retorno
        da função, como um dicionario para a mesma
        preferencialmente, pode-se usar a descrição
        das funções e usar mensagens personalizadas,
        não sendo obrigatorio o uso da mesma.
    Parametros:
        int retorno - retorno da função do tipo int
    Retornos:
        True  - Não ocorreu erros
        False - Ocorreu algum erro e printa uma mensagem relativa ao mesmo
*/

boolean print_retorno(int retorno);

/*
    Descrição: iniciar_ciclo
        Inicia o processo de ciclo, mostrando o status
        em cada ciclo, como arquivos sendo baixados,
        computadores que estão baixando cada arquivo,
        quantidade de computadores fazendo download,
        informações sobre a banda.

    Parametros:
        lst_ciclo* ciclo - Lista do ciclo propriamente dita por referencia
        historico *hist  - Lista de downloads terminados por referencia
        int link         - Inteiro contendo o link de banda total em Mb
        float prioridade - Valor da prioridade 
*/

void iniciar_ciclo(lst_ciclo* ciclo, historico *hist, int link, float prioridade);