#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>


#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>


int main(int argc, char const *argv[]) {

        //-- Definição das estruturas de endereço do cliente e do servidor
        struct sockaddr_in adressServer;
        struct sockaddr_in adressClient;

        int port, buffer_size;
        int sockfd, client;

        //--- inteiro que armazena o tamanho da estrutra de endereço do cliente
        int csize = sizeof adressClient;


        char fileName[255];

        memset(fileName,0,255);


        int openSocket(int port){

                /*--Aqui temos a definição do nosso socket e os parementros quem definem
                   AF_INET - Define que trabalhara com a internet, SOCK_STREAM - Uso do TCP
                   0 - Defini o uso do IP*/
                sockfd = socket(AF_INET, SOCK_STREAM, 0);

                adressServer.sin_family = AF_INET;
                adressServer.sin_port = htons(port);
                adressServer.sin_addr.s_addr = htonl(INADDR_ANY);

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
        openSocket(port);




        while(1)
        {
                printf("\n\nServidor esperando conexões...\n");
                //-- Aceitando requisição de conexão de um cliente
                client = accept(sockfd, (struct sockaddr*) &adressClient, &csize);



                //-- Recebe mensagem do cliente contendo nome do arquivo a ser enviado:
                int mensagem_len;
                if((mensagem_len = recv(client, fileName, 255,0)) > 0){
                  fileName[mensagem_len] = '\0';
                  printf("O arquivo solicidado pelo cliente é : %s\n",fileName);
                }

                //-- Enviando arquivo para o cliente.

                // -- cria o pronteiro de arquvo
                FILE *arq;

                arq = fopen(fileName, "r");
                if (arq == NULL){
                  printf("\nERRO! O arquivo não foi aberto");
                }


                char buffer[buffer_size];




                  while(!feof(arq)){
                    memset(buffer,0,buffer_size);
                    fgets(buffer, buffer_size, arq);
                    //fputs(buffer, stdout);
                    send(client, buffer, buffer_size, 0);
                  }

                fclose(arq);

                close(client);

        }

        return 0;
}
