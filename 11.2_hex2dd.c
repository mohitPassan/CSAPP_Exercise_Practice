#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if(argc != 2) {
        printf("Please provide a hexadecimal number\n");
        return 1;
    }

    char hex[100];
    sprintf(hex, "%x", atoi(argv[1]));

    char dec[100];
    sprintf(dec, "%d", atoi(hex));
    printf("%s\n", dec);

    return 0;
}