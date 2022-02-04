#include <stdlib.h>
//#include <conio.h>
#include <stdio.h>
#include "rtmanager.h"

    /*
        Programadores:
    Phillip Rodrigues
    Gabriel Bezerra
    Jackson Cavalcante
    */




int main(){

    int link, opcao, ip[4], i, tamanho, id_computador, id_recurso;
    float prioridade;
    char nome[30], prioridade_flag;
    lst_elementos computadores, recursos;
    lst_ciclo ciclos;
    //lst_downloads downloads_ativos;
    historico downloads_terminados;

    inicia_vars_simulador(&computadores, &recursos, &ciclos, &downloads_terminados);


    printf("Digite a velocidade do link banda em Mbps: ");
    scanf("%d", &link);
    while (link <=0){
        printf("Velocidade definida e invalida, uma valida: ");
        scanf("%d", &link);
    }
    printf("Insira o adicional de banda que os computadores prioritarios possuirao[0-50%%]: ");
    scanf("%f", &prioridade);
    while(prioridade > 50.0 || prioridade < 0){
        printf("Prioridade inserida e invalida, insira no intervalo entre 0 e 50: ");
        scanf("%f", &prioridade);
        }

    do{

        system("cls");

        printf("\n Velocidade de link setada para %dMbps\n Computadores com prioridade tem %.2f%% de banda adicional\n=======================================\n Escolha uma das operacoes abaixo: \n=======================================\n", link, prioridade);
        printf(" 1. Cadastrar computadores\n");
        printf(" 2. Listar computadores\n");
        printf(" 3. Cadastrar recursos\n");
        printf(" 4. Listar recursos\n");
        printf(" 5. Inserir jobs para processamento\n");
        printf(" 6. Iniciar simulacao\n");
        printf(" 7. Exibir sequencia de jobs finalizados\n");
        printf(" 8. Povoamento automatico\n");
        printf(" 9. Sair\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch(opcao){

            case 1:
                printf(" Insira as informacoes a seguir: \n");
                printf(" Nome do computador (Sem espacos): ");
                scanf("%s", nome);

                printf(" Ip do computador no formato xxx.xxx.xxx.xxx: ");

                scan_ip(ip);
                getchar();
                while(!print_retorno(valida_ip(ip, computadores))){
                    scan_ip(ip);
                    getchar();
                }
                
                printf("\n O computador tem prioridade? \n 1.Sim\n 0.Nao\nresposta:");
                scanf("%c", &prioridade_flag);
                while(prioridade_flag != '0' && prioridade_flag != '1'){
                    printf("Entrada invalida, insira novamente: ");
                    scanf("%c", &prioridade_flag);
                }
                if(print_retorno(cadastrar_computadores(&computadores, nome, ip, prioridade_flag)))
                    printf("Operacao realizada com sucesso\n");


            break;

            case 2:
                listar_elementos(computadores);
                system("pause");
            break;

            case 3:

                printf(" Digite o nome do arquivo a ser inserido(Sem espacos): ");
                scanf("%s", nome);

                printf(" Digite o tamanho do arquivo em Kb: ");
                scanf("%d", &tamanho);

                if(print_retorno(cadastrar_recursos(&recursos, nome, tamanho)))
                    printf("Operacao realizada com sucesso\n");
                system("pause");
            break;

            case 4:
                listar_elementos(recursos);
                system("pause");
            break;

            case 5:
                if(lst_vazia(computadores)){
                    printf(" Lista de computadores vazia, insira ao menos 1 computador antes de tentar cadastrar um job.\n\n");
                    system("pause");
                    break;
                }else{
                    printf(" Escolha o  ID do computador ao qual deseja adicionar ao job: \n");
                    listar_elementos(computadores);
                    printf("Opcao: ");
                    scanf("%d", &id_computador);
                    getchar();
                }

                if(lst_vazia(recursos)){
                    printf(" Lista de recursos vazia, insira ao menos 1 recurso antes de tentar cadastrar um job.\n");
                }else{
                    printf(" Escolha o  ID do recurso ao qual deseja adicionar ao job: \n");
                    listar_elementos(recursos);
                    printf("Opcao: ");
                    scanf("%d", &id_recurso);
                    getchar();
                }
                if(print_retorno(cadastrar_job(&computadores,&recursos,&ciclos,id_computador,id_recurso)))
                    printf("Operacao realizada com sucesso\n");
                system("pause");
                

            break;

            case 6:
                iniciar_ciclo(&ciclos, &downloads_terminados, link, prioridade);
            break;

            case 7:
                listar_historico(downloads_terminados);
                system("pause");
            break;

            case 8:
                if(povoamento_auto(&computadores, &recursos, &ciclos)){
                    printf("Povoado com sucesso.\n");
                }else{
                    printf("Houve problemas no povoamento.\n");
                }
                system("pause");
                
            break;

            case 9:
                return 0;
            break;

            default:
                printf(" **Operacao invalida.**\n");
                system("pause");

        }
    
    }while(opcao != 9);

    return 0;
}


