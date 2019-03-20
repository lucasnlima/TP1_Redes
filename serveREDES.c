#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> 


int main(int argc, char const *argv[]) {

        //-- Definição das estruturas de endereço do cliente e do servidor
        struct sockaddr_in adressServer {
                adressServer.sin_family = AF_INET;
                adressServer.sin_port = htons(port);
                adressServer.sin_addr.s_addr = htonl(INADDR_ANY);
        }

        struct sockaddr_in adressClient;

        int port, buffer_size;
        int sockfd, client;

        //--- inteiro que armazena o tamanho da estrutra de endereço do cliente
        int csize = sizeof adressClient;

        char buffer[buffer_size];

        int openSocket(int port){

                /*--Aqui temos a definição do nosso socket e os parementros quem definem
                   AF_INET - Define que trabalhara com a internet, SOCK_STREAM - Uso do TCP
                   0 - Defini o uso do IP*/
                sockfd = socket(AF_INET, SOCK_STREAM, 0);

                //-- Testa se o socket foi criado
                if(sockfd == -1) {
                        printf("\n Erro na criação do socket");
                        exit(1);
                }else
                        printf("\n Socket Criado com sucesso");

                //--Vincula um socket com um nome
                if(bind(sockfd,(struct sockaddr*)&adressServer, sizeof(adressServer)) == -1) {
                        printf("\n Erro de vinculação");
                        exit(1);
                }
                /* Função que deixa o servidor ouvindo pelo sockfd criado e permite
                   a conexão de até 10 clientes*/
                listen(sockfd, 10);

                return 0;
        }

        //-- Intreção para definir a porta que será usada a mensagem e o tamanho do buffer
        printf("\n\n Digite a porta que deseja abrir:");
        scanf("%d",&port);
        printf("\n\n Digite o tamanho do buffer:");
        scanf("%d",&buffer_size);
        printf("\n\n Digite uma mensagem:");
        scanf("%s",buffer);
        openSocket(port);

        while(1)
        {
                printf("\n\nServidor esperando conexões...\n");
                //-- Aceitando requisição de conexão de um cliente
                client = accept(sockfd, (struct sockaddr*) &adressClient, &csize);
                //-- Enviando mensagem para o cliente
                send(client, buffer, strlen(buffer), 0);
        }

        return 0;
}
