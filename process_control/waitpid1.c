#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

#define N 10

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int main()
{
    int status, i;
    pid_t pid;

    // Parent created N children
    for(i = 0; i < N; i++)
        if((pid = fork()) == 0)
            exit(100 + i);

    // Parent reaps N children in no particular order
    while ((pid = waitpid(-1, &status, 0)) > 0)
    {
        if(WIFEXITED(status))
            printf("child %d terminated normally with exit status = %d\n", pid, WEXITSTATUS(status));
        else
            printf("child %d terminated abnormally\n", pid);
    }

    // The only normal termination if there are no more children
    if(errno != ECHILD)
        unix_error("waitpid error");

    exit(0);
}