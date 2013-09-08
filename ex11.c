#include <stdio.h>

int main(int argc, char *argv[])
{
    // go through each string in argv

    int i = 0;
    while (i < argc) {
        printf("arg %d: %s\n", i, argv[i]);
        ++i;
    }

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas"
    };

    int num_states = 4;
    i = 0; // watch for this
    while (i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        ++i;
    }

    // extra credits
    printf("\nextra credits:\n");
    i = argc;
    while (--i > -1) {
        printf("arg %d: %s\n", i, argv[i]);
    }

    // copy the values from argv to states
    printf("\ncopying values from argv to states\n");
    i = 1;
    while (i < argc) {
        if (i <= num_states) {
            states[i - 1] = argv[i];
        }
        ++i;
    }
    
    i = 0;
    while (i < num_states) {
        printf("state %d: %s\n", i, states[i]);
        ++i;
    }


    return 0;
}
