#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<winsock2.h>
#include<winsock.h>
#include<netdb.h>
#include<signal.h>
#include<fcntl.h>

#define CONNECTIONMAX 1000 //defining maximum number of connections
#define BYTES 1024 

char *ROOTDIR;
//creating a socket and a client array
int listenfd, clients[CONNECTIONMAX]; 
//error function 
void error(char *);

void beginServer(char *port) //creating the server 
{
    struct addrinfo serverAddress, *responce, *p; //creating variables to get server addrss and responce

    // getting address information for host
    memset (&serverAddress, 0, sizeof(serverAddress));
    serverAddress.ai_family = AF_INET;
    serverAddress.ai_socktype = SOCK_STREAM;
    serverAddress.ai_flags = AI_PASSIVE;
    if (getaddrinfo( NULL, port, &serverAddress, &responce) != 0) //checking for errors in server address
    {
        perror ("g/etaddrinfo() error");
        exit(1);
    }
    // this is use socket and bind
    p = responce;
    while(p!=NULL){ //checking whether the responce is null
	listenfd = socket (p->ai_family, p->ai_socktype, 0);
        if (listenfd == -1) {
		continue;
	}
        if (bind(listenfd, p->ai_addr, p->ai_addrlen) == 0){ 
		break;
	}
	p= p -> ai_next;
     }
 	
    if (p==NULL){ //checking whether the port is null 
        perror ("socket() or bind() Error");
        exit(1);
    }

    freeaddrinfo(responce);

    // listen for incoming connections
    if ( listen (listenfd, 1000000) != 0 ) //can listen 1000000 connections
    {
        perror("listen() error");
        exit(1);
    }
}
//this method use client connection
void respondToClient(int clientNo){
    char msg[99999], *reqline[3], data_to_send[BYTES], path[99999];
    int rcvd, fd, bytes_read;

    memset( (void*)msg, (int)'\0', 99999 );

    rcvd=recv(clients[clientNo], msg, 99999, 0);

    if (rcvd<0)    // receive error
        fprintf(stderr,("recv() error\n"));
    else if (rcvd==0)    // receive socket closed
        fprintf(stderr,"ERROR: CLIENT DISCONNECTED UNEXPECTEDLY\n");
    else    // message received
    {
        printf("%s", msg);
        reqline[0] = strtok (msg, " \t\n");
        if ( strncmp(reqline[0], "GET\0", 4)==0 )
        {
            reqline[1] = strtok (NULL, " \t");
            reqline[2] = strtok (NULL, " \t\n");
            if ( strncmp( reqline[2], "HTTP/1.0", 8)!=0 && strncmp( reqline[2], "HTTP/1.1", 8)!=0 )
            {
                write(clients[clientNo], "HTTP/1.0 400 Bad Request\n", 25); //Bad Request error
            }
            else
            {
                if ( strncmp(reqline[1], "/\0", 2)==0 )
                    reqline[1] = "/home.html";        //Because if no file is specified, home.html will be opened by default

                strcpy(path, ROOTDIR);
                strcpy(&path[strlen(ROOTDIR)], reqline[1]);
                printf("file: %s\n", path);

                if ( (fd=open(path, O_RDONLY))!=-1 )    //FILE FOUND
                {
                    send(clients[clientNo], "HTTP/1.0 200 OK\n\n", 17, 0);
                    while ( (bytes_read=read(fd, data_to_send, BYTES))>0 )
                        write (clients[clientNo], data_to_send, bytes_read);
                }
                else    write(clients[clientNo], "HTTP/1.0 404 Not Found\n", 23); //FILE NOT FOUND
            }
        }
    }

    //Close the SOCKET
    shutdown (clients[clientNo], SHUT_RDWR);         //All further send and recieve operations are DISABLED...
    close(clients[clientNo]);
    clients[clientNo]=-1;
}

int main(int argc, char* argv[])
{
    struct sockaddr_in client_addr;
    socklen_t addrlen;
    char c;    
    
    //Default Values PATH = ~/ and PORT=5000
    char PORT[6];
    ROOTDIR = getenv("PWD");
    strcpy(PORT,"5000");

    int slot=0;

    //Parsing the command line arguments
    while ((c = getopt (argc, argv, "p:r:")) != -1)
        switch (c)
        {
            case 'r':
                ROOTDIR = malloc(strlen(optarg));
                strcpy(ROOTDIR,optarg);
                break;
            case 'p':
                strcpy(PORT,optarg);
                break;
            case '?':
                fprintf(stderr,"ERROR: Wrong arguments given!!!\n");
                exit(1);
            default:
                exit(1);
        }
    
    printf("Server started at port no. %s%s%s with ROOTDIR directory as %s%s%s\n","\033[92m",PORT,"\033[0m","\033[92m",ROOTDIR,"\033[0m");
    // Setting all elements to -1: signifies there is no client connected
    int i;
    for (i=0; i<CONNECTIONMAX; i++)
        clients[i]=-1;
    beginServer(PORT);

    // Accept the connections
    while (1)
    {
        addrlen = sizeof(client_addr);
        clients[slot] = accept (listenfd, (struct sockaddr *) &client_addr, &addrlen);

        if (clients[slot]<0)
            error ("accept() error");
        else{
            if ( fork()==0 ){
                respondToClient(slot);
                exit(0);
            }
        }

        while (clients[slot]!=-1) slot = (slot+1)%CONNECTIONMAX;
    }

    return 0;
}



