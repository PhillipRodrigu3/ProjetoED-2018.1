#include <stdlib.h>
#include <stdio.h>
/*
    Programadores:
    Phillip Rodrigues
    Gabriel Bezerra
    Jackson Cavalcante
*/

#include "rtmanager.h"


int main(){
    int link, opcao, ip[4], i, tamanho;
    float prioridade;
    char nome[30], prioridade_flag;
    lst_elementos computadores, recursos;
    lst_ciclo ciclos;
    lst_downloads downloads_ativos;
    historico downloads_terminados;
    inicia_vars_simulador(&computadores, &recursos, &ciclos, &downloads_ativos, &downloads_terminados);


    printf("Digite a velocidade do link banda em Mbps: ");
    scanf("%d", &link);
    while (link <=0){
        printf("velocidade definida é invalida, uma valida: ");
        scanf("%d", &link);
    }
    printf("Insira o adicional de banda que os computadores prioritarios possuirao[0-50\%]: ");
    scanf("%f", &prioridade);
    while(prioridade > 50.0 || prioridade < 0){
        printf("Prioridade inserida e invalida, insira no intervalo entre 0 e 50: ");
        scanf("%f", &prioridade);
        }

    printf("Velocidade de link setada para %dMbps, escolha uma das operações abaixo: \n", link);
    printf("1. Cadastrar computadores\n");
    printf("2. Listar computadores\n");
    printf("3. Cadastrar recursos\n");
    printf("4. Listar recursos\n");
    printf("5. Inserir jobs para processamento\n");
    printf("6. Iniciar simulação\n");
    printf("7. Exibir sequência de jobs finalizados\n");
    printf("8. Povoamento automatico\n");
    scanf("%d", &opcao);
    switch(opcao){
        
        case 1:
            printf("Insira as informações a seguir: \n");
            printf("Nome do computador: ");
            scanf("%s", nome);
            getchar();
            printf("Ip do computador no formato xxx.xxx.xxx.xxx: ");

            scan_ip(ip);
            while(!valida_ip(ip, computadores)){
                printf("O ip inserido e invalido, digite novamente: ");
                scan_ip(ip);
            }
            getchar();
            printf("O computador tem prioridade? \n 1.Sim\n 0.Nao\nresposta:");
            scanf("%c", &prioridade_flag);
            while(prioridade_flag != '0' && prioridade_flag != '1'){
                printf("Entrada invalida, insira novamente: ");
                scanf("%c", &prioridade_flag);
            }
            if(cadastrar_comp(&computadores, nome, ip, prioridade_flag)){
                printf("Computador cadastrado com sucesso.\n");
                
                listar_elementos(computadores);
                
            }else{
                printf("Nao foi possivel cadastrar.\n");
            }
            //print_ip(ip);
           
        break;
        
        case 2:
            listar_elementos(computadores);
        break;
        
        case 3:
            
            printf("Digite o nome do arquivo a ser inserido: ");
            scanf("%s", nome);
            
            printf("Digite o tamanho do arquivo em Kb: ");
            scanf("%d", &tamanho);
            
            cadastrar_rec(&recursos, nome, tamanho);
            listar_elementos(recursos);
        break;
        
        case 4:
            listar_elementos(recursos);
        break;
        
        case 5:
            printf("Escolha o  ID do computador ao qual deseja adicionar ao job: \n");
            listar_elementos(computadores);
            scanf("%d", &opcao);
            validaid_elem(computadores, opcao);
        break;
        
        case 6:
        break;
        
        case 7:
        break;
        
        case 8:
        break;
        
        default:
            printf("operacao invalida.");

    }
    
    return 0;
}


