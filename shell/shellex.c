#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#define MAXLINE 1024
#define MAXARGS 128

extern char **environ;

void eval(char* cmdline);
void unix_error(char *msg);
int builtin_command(char **argv);
int parseline(char *buf, char **argv);

int main()
{
    char cmdline[MAXLINE];

    while(1)
    {
        printf(">");
        fgets(cmdline, MAXLINE, stdin);
        if(feof(stdin))
            exit(0);

        // Evaluate
        eval(cmdline);
    }
}

void eval(char* cmdline)
{
    char *argv[MAXARGS];
    char buf[MAXLINE];
    int bg;
    pid_t pid;

    strcpy(buf, cmdline);
    bg = parseline(buf, argv);
    if(argv[0] == NULL)
        return;

    if(!builtin_command(argv))
    {
        if((pid = fork()) == 0)
        {
            if(execve(argv[0], argv, environ) < 0)
            {
                printf("%s: Command not found", argv[0]);
                exit(0);
            }
        }

        // Parent waits for foreground job to terminate
        if(!bg)
        {
            int status;
            if(waitpid(pid, &status, 0) < 0)
                unix_error("waitfg: waitpid error");
        }
        else
        {
            printf("%d %s", pid, cmdline);
        }
    }

    return;
}

// If first arg is a builtin command, run it and return true
int builtin_command(char **argv)
{
    if(!strcmp(argv[0], "quit"))    // Quit command
        exit(0);
    if(!strcmp(argv[0], "&"))       // Ignore singelton &
        return 1;

    return 0;                              // Not a builtin command
}

void unix_error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(0);
}

int parseline(char *buf, char **argv)
{
    char *delim;
    int argc;
    int bg;

    buf[strlen(buf) - 1] = ' ';
    while(*buf && (*buf == ' '))
        buf++;

    // Build the argv list
    argc = 0;
    while((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while(*buf && (*buf == ' '))
            buf++;
    }
    argv[argc] = NULL;

    if(argc == 0)
        return 1;

    // Should the job run in the background
    if((bg = (*argv[argc - 1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}