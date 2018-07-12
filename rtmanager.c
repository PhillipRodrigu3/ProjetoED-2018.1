#include <stdio.h>
#include <stdlib.h>
#include "rtmanager.h"



                /*Manipulação de strings*/
//copia o str da origem pro destino por referencia
boolean copia_str (char *origem, char *destino){
    int i;
    for (i=0; *(origem+i) != '\0' || i<NOME_MAX;i++){
        *(destino+i) = *(origem+i); 
    }
    if(*(origem+i) != '\0'){
        *(destino+i) = '\0';
        return true;
    }
    return false;
    
}
//compara duas strings;
boolean compara_str(char *str1, char *str2){ //FUNCIONAL
    int i, flag;
    
    for (i =0;*(str1+i)==*(str2+i) && *(str1+i) != '\0';i++);

    return (*(str1+i) == '\0');
}
                /*Area responsavel pela manipulação e validação do IP*/
//Ler o IP com formatação
void scan_ip(int *ip){ //FUNCIONAL
    
    int i;
    
    scanf("%d", ip);
        
        for(i=1;i<4;i++){
            
            scanf(".%d", ip+i);
            
        }
}
//Printa o IP no formato XXX.XXX.XXX.XXX
void print_ip(int ip[]){ //FUNCIONAL
   
    int i;

     printf("%d", *ip);
        for(i=1 ; i<4 ; i++){
            printf(".%d", *(ip+i));
        }
}

//Valida o ip inserido
int valida_ip(int *ip, lst_elementos com){ //FUNCIONAL
    int i, count = 0;

    if(*(ip) == 0)
        return -1;                          //primeiro campo igual a 0
    for(i=0;i<4; i++){
        if (*(ip+i) > 255 || *(ip+i) < 0)
            return -2;                     //maior ou menor que permitido 
    }
    while(com.inicio!= NULL){
        for(i=0;i<4; i++){
            if(*(ip+i) == *(com.inicio->ip+i)){
                 count++;
            }
        }
        if (count == 4){
            return -3;                    //IP ja usado;
            return (-1);
        }else{
            count = 0;
        }
        com.inicio = com.inicio->prox;
    }
    return 1;
}

                /*Funções das estruturas*/

//Inicialização das estruturas
void inicia_vars_simulador(lst_elementos *com, lst_elementos *arq, lst_ciclo *elem, lst_downloads *downs, historico *baixados){
    com->inicio = NULL;
    com->id = 0;
    com->tipo = '0';
    arq->inicio = NULL;
    arq->id = 0;
    arq->tipo = '1';
    elem->inicio = NULL;
    elem->id = 0;
    downs->inicio = NULL;
    downs->id = 0;
    baixados = NULL;
}

//Lista de computadores vazia
boolean vazia_comp (lst_elementos com) {
    return (com.inicio == NULL);
}

//Lista de recursos vazia
boolean vazia_arq (lst_elementos arq) {
    return (arq.inicio == NULL);
}
//Cadastrar elemento(no) na lista de computadores
int cadastrar_comp (lst_elementos* comp, char nome[], int ip[], char prior){
    elemento* novo;
    int i;
    novo = (elemento*) malloc(sizeof(elemento));
    if (novo == NULL) 
        return -1;      //Não conseguiu alocar
    else if (copia_str (nome, novo->nome)){
        return -2;     //Não pode copiar a string nome/string nome inserida é invalida
    }
    for(i = 0; i < 4; *(novo->ip+i)=*(ip+i++));
    novo->id = comp->id++;
    novo->prioridade = prior;
    novo->prox = NULL;
    if (vazia_comp(*comp)){
        comp->inicio = novo;
        return 1;
    }
    elemento* aux;
    aux = comp->inicio;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox = novo;
    return 1;
}

//Cadastrar elemento(no) na lista de recursos
int cadastrar_rec (lst_elementos* arq, char* nome, int tam){
    elemento* novo;
    novo = (elemento*)malloc(sizeof(elemento));
    if (novo == NULL)
        return -1;  //Não foi possivel alocar
    else if(copia_str (nome, novo->nome)){
        return -2;  //Não pode copiar a string nome/string nome inserida é invalida
    }
    novo->tamanho = tam;
    novo->id = arq->id++;
    novo->prox = NULL;
    if (vazia_arq (*arq)){
        arq->inicio = novo;
        return 1;
    }
    elemento* aux;
    aux = arq->inicio;
    while (aux->prox != NULL) {
        aux = aux->prox;
    }
    aux->prox= novo;
    return 1;

}
//listar a lista mandada como parametro

void listar_elementos(lst_elementos lista){
    
    if(lista.inicio == NULL){
        printf("\t\tA lista está vazia\n");
        return;
    }
    if(lista.tipo == '0'){
        printf("\tLista de computadores:      \n\n");
        printf("\tID  NOME\t\tIP\t\tPRIORIDADE\n");
        while(lista.inicio != NULL){
            printf("\t%02d  %-10s\t\t", lista.inicio->id, lista.inicio->nome);
            print_ip(lista.inicio->ip);
            if(lista.inicio->prioridade == '1'){
                printf("\tSIM\n");
            }else{
                printf("\tNAO\n");
            }
            
            lista.inicio = lista.inicio->prox;
        }
    }else if(lista.tipo == '1'){
        printf("\tLista de recursos:      \n\n");
        printf("\tID  NOME\tTAMANHO\n");
        while(lista.inicio != NULL){
        printf("\t%02d  %-10s\t%02d\n", lista.inicio->id,lista.inicio->nome, lista.inicio->tamanho);
        lista.inicio = lista.inicio->prox;
        }
    }
    
 }
boolean validaid_elem(lst_elementos elemento, int id){

    while(elemento.inicio != NULL){
        if(elemento.inicio->id == id){
            return true;
        }else{
            elemento.inicio = elemento.inicio->prox;
        }
    }
    return false;
}
boolean inserir_job(lst_elementos *com, lst_elementos *arq, lst_ciclo* ciclo){
    
    int opcao;
    //lst_elementos aux_arq, aux_com;
    elemciclo* novo_passo;
    lst_downloads* novo_job;

    novo_job = (lst_downloads*) malloc(sizeof(lst_downloads));
    novo_passo = (elemciclo*) malloc (sizeof(elemciclo));

    if(novo_job == NULL || novo_passo == NULL || com->inicio == NULL || arq->inicio == NULL)
        return false;

    printf("Escolha o  ID do computador ao qual deseja adicionar ao job: \n");
    listar_elementos(*com);
    scanf("%d", &opcao);
    validaid_elem(*com, opcao);
    
    printf("Escolha o  ID do recurso ao qual deseja adicionar ao job: \n");
    listar_elementos(*arq);
    scanf("%d", &opcao);
    validaid_elem(*arq, opcao);

}

