#include <stdio.h>
#include <ctype.h>
/**
 * reworked + reduced to 1 function
 */

void print_arguments(int argc, char *argv[])
{
    int i = 0;
    int j = 0;
    
    for (i = 0; i < argc; i++) {
        for (j = 0; argv[i][j] != '\0'; j++) {
            if (isalpha((char) argv[i][j]) || isblank((char) argv[i][j])) {
                printf("'%c' == %d ", argv[i][j], argv[i][j]);
            }
        }
        printf("\n");
    }
}


int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    return 0;
}
