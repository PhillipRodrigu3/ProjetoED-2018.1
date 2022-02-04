#include <stdio.h>
#include <stdlib.h>
#include "rtmanager.h"

/////////////////////////////////////////////////////////////////////////////
/////////******************************************************//////////////
/////////************LISTA DE FUNÇÕES CATEGORIZADAS************//////////////
/////////******************************************************//////////////
/////////////////////////////////////////////////////////////////////////////

/*
    Ordem de categorias:
    1. Inicialização
    2. Auxiliares
    3. Informativos/prints
    4. Ip
    5. Cadastros
    6. Iniciar ciclo
*/

//                  <INICIALIZAÇÃO>

void inicia_vars_simulador(lst_elementos *com, lst_elementos *arq, lst_ciclo *ciclo, historico *baixados){
    com->inicio = NULL;
    com->id = 0;
    com->tipo = '0';
    arq->inicio = NULL;
    arq->id = 0;
    arq->tipo = '1';
    ciclo->inicio = NULL;
    ciclo->id = 0;
    *baixados = NULL;
}

//                  <AUXILIARES>
               
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

//compara duas strings

boolean compara_str(char *str1, char *str2){
    int i;
    
    for (i =0;*(str1+i)==*(str2+i) && *(str1+i) != '\0';i++);

    return (*(str1+i) == '\0');
}

//checa se a elementos está vazia

boolean lst_vazia (lst_elementos elem) {
    return (elem.inicio == NULL);
}

//Checa se o id enviado é valido

boolean valida_id_elemento(lst_elementos elemento, int id){

    while(elemento.inicio != NULL){
        if(elemento.inicio->id == id){
            return true;
        }else{
            elemento.inicio = elemento.inicio->prox;
        }
    }
    return false;
}

//Procura o ID do elemento pelo nome

int procuraId_elemento(lst_elementos elemento, char nome[]){

    while(elemento.inicio != NULL){
        if(compara_str(elemento.inicio->nome, nome)){
            return elemento.inicio->id;
        }else{
            elemento.inicio = elemento.inicio->prox;
        }
    }
    return -1;
}

int tam_lst_download(lst_downloads lista){
    int i;
    if  (lista.inicio == NULL)
        return -1;
    for (i = 0; lista.inicio != NULL; i++, lista.inicio =lista.inicio->prox);
    
    return i;
}

void remove_down(lst_downloads *lista, int id){
    
    down *aux_down = lista->inicio, *aux;

    if(aux_down->id == id ){
        if(aux_down->prox == NULL){
            lista->inicio = NULL;
            free(aux_down);
        }else{
            lista->inicio = aux_down->prox;
            free(aux_down);
        }
        return;
    }
    while(aux_down->id != id && aux_down != NULL){
        aux = aux_down;
        aux_down = aux_down->prox;
    }
    if(aux_down->id == id){
        if (aux_down->prox != NULL){
            aux->prox = aux_down->prox;
        }else{
            aux->prox = NULL;
        }
        free(aux_down);    
    }
}

void remove_passo(lst_ciclo *lista, int id){
    
    elemciclo *aux_com = lista->inicio, *aux = aux_com;


    if(aux_com->id == id ){
        if(aux_com->prox == NULL){
            lista->inicio = NULL;
            free(aux_com);
        }else{
            lista->inicio = aux_com->prox;
            free(aux_com);
        }
        
        return;
    }
    while(aux_com->id != id && aux_com != NULL){
        
        aux = aux_com;
        aux_com = aux_com->prox;
    }

    if(aux_com->id == id){
       if (aux_com->prox != NULL){
            aux->prox = aux_com->prox;
        }else{
            aux->prox = NULL;
        }
        free(aux_com);
    }
}

//                  <INFORMATIVOS/PRINTS>

//listar a lista de elementos mandada como parametro

void listar_elementos(lst_elementos lista){
    printf("\n");
    if(lista.inicio == NULL){
        printf("\t\tLista vazia\n");
        return;
    }
    if(lista.tipo == '0'){
        printf("\tLista de computadores:      \n\n");
        printf("\tID  NOME\t\t\tIP\t\tPRIORIDADE\n");
        while(lista.inicio != NULL){
            printf("\t%02d  %-13s\t\t", lista.inicio->id, lista.inicio->nome);
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
        printf("\tID  NOME\t\tTAMANHO\n");
        while(lista.inicio != NULL){
        printf("\t%02d  %-12s\t%02dKb\n", lista.inicio->id,lista.inicio->nome, lista.inicio->tamanho);
        lista.inicio = lista.inicio->prox;
        }
    }
    
 }

//printa o status do ciclo
void print_ciclo(lst_ciclo ciclo){
    
    if(!ciclo.inicio){
        printf("\t\tCICLO VAZIO\n\n");
        return;
    }

    elemciclo* auxelem;
    down* auxdown;
    auxelem = ciclo.inicio;
    while(auxelem != NULL){
        printf("\nCOMPUTADOR: \n");
        printf("\nNOME\t\t\tIP\t\tBANDA ALOCADA\tDOWNLOADS RESTANTES\n");
        printf("%-13s\t\t", auxelem->computador->nome);
        print_ip(auxelem->computador->ip);
        printf("\t%.2fMbps\t%d\n", auxelem->velocidade_com, tam_lst_download(*(auxelem->lista_downs)));
        printf("\n\tDOWNLOADS ATIVOS:");
        auxdown = auxelem->lista_downs->inicio;
        printf("\n\tID NOME\t\t\tBAIXADO/TAMANHO TOTAL\tVELOCIDADE DE DOWNLOAD\n");
        while(auxdown != NULL){
            printf("\t%02d %-13s\t%.2f/%dKb\t\t%.2fMbps\n", auxdown->id, auxdown->arq_atual->nome, auxdown->tam_atual, auxdown->arq_atual->tamanho, auxdown->velocidade_arq);
            auxdown = auxdown->prox;
        }

        auxelem = auxelem->prox;
    }
}

//Printa erros, se encontrados, relativo ao retorno de algumas funções

boolean print_retorno(int retorno){

    switch(retorno){

        case 1:
            return true;

        break;

        case -1:
            printf("\n **ERRO** Nao foi possivel alocar memoria.\n");
            return false;
        break;

        case -2:
            printf("\n **ERRO** Nome fornecido invalido.\n");
            return false;
        break;
        case -3:
            printf("\n **ERRO** ID invalido.\n"); 
            return false;

        case -4:
            printf("\n **ERRO** IP invalido: primeiro campo igual a 0.\n Digite novamente: ");
            return false;
        break;
        
        case -5:
            printf("\n **ERRO** IP invalido: maior ou menor que a range permitida (0-255).\n Digite novamente: ");
            return false;
        break;
        
        case -6:
            printf("\n **ERRO** IP invalido: ja esta em uso.\n Digite novamente: ");
            return false;
        break;
    }
}

//Mostra o historico de arquivos baixados
void listar_historico (historico terminados){
    if (terminados == NULL){
        printf("\t\tLista Vazia\n");
        return;
    }
        printf("Historico de arquivos baixados em ordem de finalizacao:\n");
        printf("Computador:\tArquivo:\tCiclos Necessarios:\tVelocidade no ultimo ciclo:\n");
    while (terminados != NULL){
        printf("%-13s\t%-12s\t\t%d\t\t\t%.2fMbps\n", terminados->com->nome, terminados->arq->nome, terminados->ciclos, terminados->velocidade_final);
        terminados = terminados ->prox;
    }
        printf("\n\t\t\tFIM DA LISTA\n");
}


//                  <IP>

//Ler o IP com formatação

void scan_ip(int *ip){ 
    
    int i;
    
    scanf("%d", ip);
        
        for(i=1;i<4;i++){
            
            scanf(".%d", ip+i);
            
        }
}

//Printa o IP no formato XXX.XXX.XXX.XXX

void print_ip(int ip[]){ 
   
    printf("%d.%d.%d.%d", *(ip), *(ip+1), *(ip+2), *(ip+3));
}

//Valida o ip inserido

int valida_ip(int *ip, lst_elementos com){ 
    int i, count = 0;

    if(*(ip) == 0)
        return -4;                          //primeiro campo igual a 0
    for(i=0;i<4; i++){
        if (*(ip+i) > 255 || *(ip+i) < 0)
            return -5;                     //maior ou menor que permitido 
    }
    while(com.inicio!= NULL){
        for(i=0;i<4; i++){
            if(*(ip+i) == *(com.inicio->ip+i)){
                 count++;
            }
        }
        if (count == 4){
            return -6;                    //IP ja usado;
        }else{
            count = 0;
        }
        com.inicio = com.inicio->prox;
    }
    return 1;
}

//                  <CADASTROS>

//Cadastrar elemento(no) na lista de computadores
int cadastrar_computadores (lst_elementos* comp, char nome[], int ip[], char prior){
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
    if (lst_vazia(*comp)){
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
int cadastrar_recursos (lst_elementos* arq, char nome[], int tam){
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
    if (lst_vazia (*arq)){
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

int cadastrar_job(lst_elementos *com, lst_elementos *arq, lst_ciclo *ciclo, int id_com, int id_arq){
    
    if(!(valida_id_elemento(*com, id_com) && valida_id_elemento(*arq, id_arq)))
        return -3;      //id invalido
    
    int opcao;
    boolean ciclo_vazio = (ciclo->inicio == NULL);
    elemento* auxelem;
    elemciclo* auxciclo;
    down* novo_down;
    novo_down = (down*) malloc (sizeof(down));

    if (novo_down == NULL)
        return -1; //problema na alocação

    if(!ciclo_vazio){
        auxciclo = ciclo->inicio;
        while (auxciclo->computador->id != id_com && auxciclo->prox != NULL){
            auxciclo = auxciclo->prox;
        }
    }
    if(ciclo_vazio || auxciclo->computador->id != id_com){
        
        elemciclo* novo_passo;
        lst_downloads* nova_lstdown;
               
        novo_passo = (elemciclo*) malloc(sizeof(elemciclo));
        nova_lstdown = (lst_downloads*) malloc(sizeof(lst_downloads));
        

        if(nova_lstdown == NULL || novo_passo == NULL){
            return -1; //   problema na alocação
        }

        nova_lstdown->id = 0;
        

        auxelem = com->inicio;

        while(auxelem != NULL){
            if(auxelem->id == id_com){
                novo_passo->computador = auxelem;
                break;
            }else{
                auxelem = auxelem->prox;
            }
        }
        auxelem = arq->inicio;
        while(auxelem != NULL){
            if(auxelem->id == id_arq){
                novo_down->arq_atual = auxelem;
                novo_down->tam_atual = 0;
                novo_down->count_ciclos = 0;
                novo_down->velocidade_arq = 0;
                novo_down->prox = NULL;
                novo_down->id        = nova_lstdown->id;
                nova_lstdown->id++;
                break;
            }else{
                auxelem = auxelem->prox;
            }
        }
        nova_lstdown->inicio = novo_down;
        novo_passo->lista_downs = nova_lstdown;
        novo_passo->id = ciclo->id++;
        novo_passo->prox = NULL;
        
        if (ciclo_vazio){
            ciclo->inicio = novo_passo;
        }else{
            auxciclo->prox = novo_passo;
        }
        
        return 1; //sucesso

    }else{  
          
        auxelem = arq->inicio;
        down* auxdown;
        auxdown = auxciclo->lista_downs->inicio;
        while(auxelem != NULL){
                
            if(auxelem->id == id_arq){
                novo_down->arq_atual = auxelem;
                novo_down->tam_atual = 0;
                novo_down->velocidade_arq = 0;
                novo_down->prox = NULL;
                novo_down->id  = auxciclo->lista_downs->id++;
                    
                while(auxdown->prox != NULL){
                    auxdown = auxdown->prox;
                }
                auxdown->prox = novo_down;
                break;
            }else{                    
                auxelem = auxelem->prox;
            }
        }
    }
}

void cadastrar_historico(historico *lista, elemento *recurso, elemento *computador, float velocidade, int ciclos){
    
    elemhist *novo;

    novo = (elemhist*) malloc (sizeof(elemhist));

    if (novo == NULL)
        return;

    novo->arq = recurso;
    novo->com = computador;
    novo->ciclos = ciclos;
    novo->velocidade_final = velocidade;
    novo->prox = NULL;

    if (*lista == NULL){
        
        //system("pause");
        *lista = novo;
        
        return;
    }
    elemhist *aux = *lista;
    while (aux->prox != NULL){
        aux = aux->prox;
    }
    aux->prox = novo;
}

boolean povoamento_auto(lst_elementos *com, lst_elementos *arq, lst_ciclo *ciclo){
    int i, j, ip [4] = {192, 168, 1};
    
    char nome_com[4][15] = {"Computador  1", "Computador  2", "Computador  3","Computador  4"};

    for(i = 0, ip [3] = 0 ;valida_ip(ip, *com) == 1 && i < 4; ip[3]= i++);
    
    if(i<3){
        return false; //ip padrão já foi usado
    }

    for(i = 0; i < 4; i++){
        ip[3] = i;
        if(!cadastrar_computadores(com, nome_com[i], ip, i % 2? '0' : '1')){
            break;
        }
    }
    if (i < 4){
        return false;
    }

    char nome_arq[4][15] = {"Documento  1", "Documento  2", "Documento  3","Documento  4"};

    for(i = 0; i < 4; i++){
        if(cadastrar_recursos(arq, nome_arq[i], (i+5)*1450) != 1){
            break;
        }
    }
    if (i < 4){
        return false;
    }

    int aux = procuraId_elemento(*com, nome_com[0]);
    
    for (i = aux; i < aux+4; i++){
        cadastrar_job(com,arq,ciclo,i, i % 4);
    }
}

//              <INICIAR CICLO>

void iniciar_ciclo(lst_ciclo* ciclo, historico *hist, int link, float prioridade){

    if(ciclo->inicio == NULL){
        printf("Nao a nenhum job a ser feito.\n");
        system("pause");
        return;
    }
    char opcao;
    int computadores_ativos = 0, prioritarios = 0, quantidade_down = 0;
    float banda_alocada, banda_total_temp;
    //auxiliares
    elemciclo *aux_ciclo;
    down *aux_down;
    elemciclo *aux_aux_ciclo;
    down *aux_aux_down;

    system("cls");

    



    //Alocação de banda/calculos
    do{ 
        
        aux_ciclo = ciclo->inicio;
        for (computadores_ativos= 0; aux_ciclo != NULL; computadores_ativos++,aux_ciclo = aux_ciclo->prox);

        banda_alocada = 0;
        banda_total_temp = link;
        //Velocidade dos computadores
        aux_ciclo = ciclo->inicio;
        prioritarios = 0;
        while(aux_ciclo != NULL){
        
            if(aux_ciclo->computador->prioridade == '1'){
                prioritarios++;
            }
            aux_ciclo = aux_ciclo->prox;
        }

        if(prioritarios == 0){
            
            aux_ciclo = ciclo->inicio; //reseta a posição
            
            while(aux_ciclo != NULL){
                aux_ciclo->velocidade_com = banda_total_temp/computadores_ativos;
                aux_ciclo = aux_ciclo->prox; 
            }

        }else{    
                //printf("contas do programa:\n");
                banda_alocada = (float)link/computadores_ativos;
                //printf("link/computadores_ativos: %f\n", banda_alocada);
                if(computadores_ativos != prioritarios){
                    banda_alocada += ((banda_alocada/100)*prioridade);
                    banda_total_temp -= banda_alocada*prioritarios;
                    aux_ciclo = ciclo->inicio; //reseta a posição
            
                    while(aux_ciclo != NULL){
                        if(aux_ciclo->computador->prioridade == '1'){
                            aux_ciclo->velocidade_com = banda_alocada;
                        }else{
                            aux_ciclo->velocidade_com = banda_total_temp/(computadores_ativos-prioritarios);
                        }
                        aux_ciclo = aux_ciclo->prox;
                    }
                }else{
                    aux_ciclo = ciclo->inicio; //reseta a posição
                    while(aux_ciclo != NULL){
                        aux_ciclo->velocidade_com = banda_alocada;
                        aux_ciclo = aux_ciclo->prox;
                    }
                }
            
                //printf("banda mais incremento: %f\nIncremento foi de:%f(%f%%)", banda_alocada, (banda_alocada/100)*prioridade, prioridade);
                  //remove o valor prioritario do link total
                
            
        }

        //Velocidade dos downloads
        aux_ciclo = ciclo->inicio; //reseta a posição

        while(aux_ciclo != NULL){
            
            banda_alocada = aux_ciclo->velocidade_com/tam_lst_download(*(aux_ciclo->lista_downs));
            aux_down = aux_ciclo->lista_downs->inicio;

            while(aux_down != NULL){
                aux_down->velocidade_arq = banda_alocada;
                aux_down= aux_down->prox;
            }

            aux_ciclo = aux_ciclo->prox;
        }

        //system("cls");
        printf("\n\t\t\tSIMULACAO EM ANDAMENTO\n\n");
        printf("LINK DE BANDA(TOTAL): %dMbps\t",link);
        printf("GANHO CASO POSSUIR PRIORIDADE: %.2f%%\t", prioridade);
        printf("\n\nCOMPUTADORES ATIVOS NO CICLO ");
        printf("TOTAL: %d PRIORITARIOS: %d\n", computadores_ativos, prioritarios);
        
        
        print_ciclo(*ciclo);
        getchar();
        printf("\nEscolha uma opcao abaixo: \n\t1.Continuar no ciclo\n\t2.Voltar ao menu\nOpcao: ");
        scanf("%c", &opcao);
        
        if(opcao != '1'){
            if(opcao == '2'){
                return;
            }else{
                while (opcao != '1' && opcao != '2'){
                    getchar();
                    printf("opcao invalida[%c], escolha entre 1 ou 2: ", opcao);
                    scanf("%c", &opcao);
                    
                    if(opcao == '2')
                        return;
                }
                
            }
        }
        system("cls");
        aux_ciclo = ciclo->inicio;
        //contar ciclos
        while(aux_ciclo != NULL){
            
            aux_down = aux_ciclo->lista_downs->inicio;

            while(aux_down != NULL){
                aux_down->count_ciclos++;
                
                aux_down = aux_down->prox;
            }
            aux_ciclo = aux_ciclo->prox;
        }
        
        aux_ciclo = ciclo->inicio; //reseta a posição

        while(aux_ciclo != NULL){

            aux_down = aux_ciclo->lista_downs->inicio;
            quantidade_down = 0;
            while (aux_down != NULL){
                aux_down = aux_down->prox;
                quantidade_down++;
            }
            aux_down = aux_ciclo->lista_downs->inicio;
            while(aux_down != NULL){

                aux_down->tam_atual += aux_down->velocidade_arq*1000;

                aux_aux_down = aux_down->prox;
                //printf("Tamanho atual do arquivo: %f\n", aux_down->tam_atual);

                if (aux_down->tam_atual >= aux_down->arq_atual->tamanho){
                    cadastrar_historico(hist, aux_down->arq_atual, aux_ciclo->computador, aux_down->velocidade_arq, aux_down->count_ciclos);
                    remove_down(aux_ciclo->lista_downs, aux_down->id);    
                }
                aux_down = aux_aux_down;
            } 
            if(aux_ciclo->lista_downs->inicio == NULL){
                
                aux_aux_ciclo = aux_ciclo->prox;
                
                if(aux_ciclo->prox == NULL){
                    
                    remove_passo(ciclo, aux_ciclo->id);
                    aux_ciclo = NULL;
                }else{    
                    remove_passo(ciclo, aux_ciclo->id);     
                    aux_ciclo = aux_aux_ciclo;
                }
            }else{
                aux_ciclo = aux_ciclo->prox;
            }
        }
    }while (ciclo->inicio !=NULL);
    printf("\t\tTodos os downloads foram concluidos.\n");
    system("pause");
}