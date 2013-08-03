#include <stdio.h>

int main(int argc, char *argv[])
{
    int i = 0;

    // let's make our own array of strings
    char *states[] = {
        "California", "Oregon",
        "Washington", "Texas",
        NULL, "Arizona"
    };
    int num_states = 6;

    for (i = 0; i < num_states; i++) {
        printf("state %d: %s\n", i, states[i]);
    }

    // go through each string in argv
    // why am I skipping argv[0]
    for (i = 1; i < argc; i++) {
        if (i < num_states) {
            argv[i] = states[i];
        }
        printf("arg %d: %s\n", i, argv[i]);
    }

    return 0;
}
