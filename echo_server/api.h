#ifndef ECHO_SERVER_API_H
#define ECHO_SERVER_API_H

#include <stdio.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>
#include <unistd.h>

#define LISTENQ 1024
#define MAXLINE 1024

int open_clientfd(char *hostname, char *port);
int open_listenfd(char *port);

typedef struct addrinfo addrinfo;

#endif