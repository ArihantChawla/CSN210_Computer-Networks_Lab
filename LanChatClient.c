#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>

void error(const char * msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[])
{
    if(argc<3)
    {
        fprintf(stderr,"::USAGE:: ./a.out [SERVER_IP] [SERVER_PORTNO]\n");
        exit(1);
    }

    int sockfd,n;
    struct sockaddr_in serv_addr;
    char buffer[255];
    int portno;

    portno=atoi(argv[2]);

    sockfd=socket(AF_INET,SOCK_STREAM,0);
    if(sockfd<0)
    {
        error("ERROR OPENING SOCKET\n");
    }

    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port=htons(portno);
    serv_addr.sin_addr.s_addr=inet_addr(argv[1]);
    memset(serv_addr.sin_zero,'\0',8);

    if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        error("CONNECTION FAILED\n");
    }
    printf("\n\n----------------------------------------------------\n\n\tWELCOME TO ARIHANT'S CHATTING APP\n\n----------------------------------------------------\n\n");
    while(1)
    {
        bzero(buffer,255);
        printf("CLIENT: ");
        fgets(buffer,255,stdin);

        n=send(sockfd,buffer,strlen(buffer),0);
        if(n<0)
        {
            error("ERROR ON SEND");
        }
        int i=strncmp("BYE",buffer,3);
        if(i==0)
            break;

        i=strncmp("Bye",buffer,3);
        if(i==0)
            break;

        i=strncmp("bye",buffer,3);
        if(i==0)
            break;
        bzero(buffer,255);
        n=recv(sockfd,buffer,255,0);
        if(n<0)
        {
            error("ERROR ON READING");
        }

        printf("SERVER: %s",buffer);

        i=strncmp("BYE",buffer,3);
        if(i==0)
            break;

        i=strncmp("Bye",buffer,3);
        if(i==0)
            break;

        i=strncmp("bye",buffer,3);
        if(i==0)
            break;

    }
    close(sockfd);
    return 0;
}
