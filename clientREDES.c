#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[]) {

        //-- Definição das estruturas de endereço do cliente
        struct sockaddr_in adressServer;

        int port, buffer_size;
        int sockfd, client;

        //--- inteiro que armazena o tamanho da estrutra de endereço do cliente
        int csize = sizeof adressServer;

        char buffer[buffer_size];
        char fileName[255];
        char server_adress[15];


        //-- Intreção para definir a porta que será usada a mensagem e o tamanho do buffer
        printf("\n\n Qual o enredereço(IP) do servidor que deseja acessar:");
        scanf("%s",server_adress);
        printf("\n\n Qual porta será usada na comunicação:");
        scanf("%d",&port);
        printf("\n\n Digite o tamanho do buffer:");
        scanf("%d",&buffer_size);

        /*--Aqui temos a definição do nosso socket e os parementros quem definem
           AF_INET - Define que trabalhara com a internet, SOCK_STREAM - Uso do TCP
           0 - Defini o uso do IP*/
        sockfd = socket(AF_INET, SOCK_STREAM, 0);

        adressServer.sin_family = AF_INET;
        adressServer.sin_port = htons(port);
        adressServer.sin_addr.s_addr = inet_addr(server_adress);

        //-- Testa se o socket foi criado
        if(sockfd == -1) {
                printf("\n Erro na criação do socket");
                exit(1);
        }else
                printf("\n Socket Criado com sucesso");

        //-- Conecta ao Servidor
        if(connect(sockfd, (struct sockaddr*) &adressServer, csize) == -1){
            printf("\n Erro na conexão do socket");
            exit(1);
        }else
            printf("\n Conectado ao servidor");

            memset(fileName,0x0,255);

        printf("\n\n Qual o nome do arquivo que deseja baixar:");
        scanf("%s",fileName);



        send(sockfd, fileName,strlen(fileName),0);
        printf("%s\n",fileName);



               recv(sockfd, buffer, csize,0);

                // -- cria o pronteiro de arquvo
                FILE *arq;

                arq = fopen(fileName, "w");

                if(arq == NULL){
                  printf("Erro na criação do arquivo");
                  return 1;
                }

                fprintf(arq, "%s", buffer);

                fclose(arq);

                printf("Arquivo tranferido com sucesso\n Conteudo: \n");

                if(fputs(buffer, stdout) == EOF)
                {
                    printf("\nStandard output error");
                }



        return 0;
}
