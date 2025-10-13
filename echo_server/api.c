#include "./api.h"

int open_clientfd(char *hostname, char *port)
{
    int clientfd;
    addrinfo hints, *listp, *p;

    // Get a list of potential server addresses
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_NUMERICSERV;
    hints.ai_flags |= AI_ADDRCONFIG;
    int getAddrInfoErrCode = getaddrinfo(hostname, port, &hints, &listp);
    if(getAddrInfoErrCode != 0)
    {
        fprintf(stderr, "There was an error while calling getaddrinfo: %s", gai_strerror(getAddrInfoErrCode));
        return -1;
    }


    // Traverse the list for one that we can successfully connect to
    for(p = listp; p; p = p -> ai_next)
    {
        // Create a socket descriptor
        clientfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol);
        if(clientfd < 0)
        {
            continue;
        }

        // Connect to the server
        int err = connect(clientfd, p -> ai_addr, p -> ai_addrlen);
        if(err != -1)
        {
            break;
        }
        close(clientfd);
    }

    // Clean up
    freeaddrinfo(listp);
    if(!p)
    {
        return -1;
    } 
    else 
    {
        return clientfd;
    }
}

int open_listenfd(char *port)
{
    addrinfo hints, *listp, *p;
    int listenfd, optval = 1;

    // Get a list of potential server addresses
    memset(&hints, 0, sizeof(addrinfo));
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE | AI_ADDRCONFIG;
    hints.ai_flags |= AI_NUMERICSERV;
    int getAddrInfoErrCode = getaddrinfo(NULL, port, &hints, &listp);
    if(getAddrInfoErrCode != 0)
    {
        fprintf(stderr, "There was an error while calling getaddrinfo: %s", gai_strerror(getAddrInfoErrCode));
        return -1;
    }

    // Walk the list for one that we can bind to
    for(p = listp; p; p = p -> ai_next)
    {
        // Create a socket descriptor
        listenfd = socket(p -> ai_family, p -> ai_socktype, p -> ai_protocol);
        if(listenfd < 0)
        {
            continue;
        }

        // Eliminated "Address already in use" error from bind
        setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(int));

        // Bind the descriptor to the address
        int err = bind(listenfd, p -> ai_addr, p -> ai_addrlen);
        if(err == 0)
        {
            break;
        }
        close(listenfd);
    }

    // Clean up
    freeaddrinfo(listp);
    if(!p)
    {
        return -1;
    }

    if(listen(listenfd, LISTENQ) < 0)
    {
        close(listenfd);
        return -1;
    }

    return listenfd;
}