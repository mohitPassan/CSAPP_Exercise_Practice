#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    // Check if we have exactly 2 arguments (plus program name = 3 total)
    if (argc != 3) {
        printf("Usage: %s <number1> <number2>\n", argv[0]);
        return 1;
    }
    
    // Convert arguments to integers
    int num1 = atoi(argv[1]);
    int num2 = atoi(argv[2]);
    
    // Calculate sum
    int sum = num1 + num2;
    
    // Output in the requested format: "12 + 12 = 24"
    printf("%d + %d = %d\n", num1, num2, sum);
    
    return 0;
}
