#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

void error(const char * msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char * argv[])
{
    if(argc<2)
    {
        fprintf(stderr,"::usage:: ./a.out [PORT_NO]\nPROGRAM TERMINATED\n");
        exit(1);
    }

    int sockfd,newsockfd,portno,n;
    char buffer[255];
    struct sockaddr_in serv_addr,cli_addr;

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        error("ERROR OPENING SOCKET\n");
    }

    portno=atoi(argv[1]);

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr=INADDR_ANY;
    serv_addr.sin_port=htons(portno);
    memset(serv_addr.sin_zero,'\0',8);

    if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        error("BINDING FAILED\n");
    }

    listen(sockfd,5);
    int clilen=sizeof(cli_addr);
    newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);

    if(newsockfd<0)
    {
        error("ACCEPT FAILED");
    }
    printf("\n\n----------------------------------------------------\n\n\tWELCOME TO ARIHANT'S CHATTING APP\n\n----------------------------------------------------\n\n");
    while(1)
    {
        bzero(buffer,255);
        n=recv(newsockfd,buffer,255,0);
        if(n<0)
        {
            error("READ ERROR\n");
        }
        printf("CLIENT: %s",buffer);
        int i=strncmp("BYE",buffer,3);
        if(i==0)
            break;

        i=strncmp("bye",buffer,3);
        if(i==0)
            break;

        i=strncmp("Bye",buffer,3);
        if(i==0)
            break;

        bzero(buffer,255);
        printf("SERVER: ");
        fgets(buffer,255,stdin);

        n=send(newsockfd,buffer,strlen(buffer),0);
        if(n<0)
        {
            error("ERROR ON WRITING\n");
        }

        i=strncmp("BYE",buffer,3);
        if(i==0)
            break;

        i=strncmp("bye",buffer,3);
        if(i==0)
            break;

        i=strncmp("Bye",buffer,3);
        if(i==0)
            break;

    }
    close(newsockfd);
    close(sockfd);
    return 0;
}
