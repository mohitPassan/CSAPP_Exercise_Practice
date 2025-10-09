#include<stdlib.h>
#include<stdio.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please provide an integer\n");
        return 1;
    }

    int d = atoi(argv[1]);
    int i = 0;
    char hex[100];
    sprintf(hex, "%x", d);
    printf("%s\n", hex);

    return 0;
}