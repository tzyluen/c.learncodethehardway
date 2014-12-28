#include <stdio.h>
#include <stdlib.h>

#define STACKSIZE   512

typedef struct stack {
    size_t size;
    int items[STACKSIZE];
} T_STACK;


void push(T_STACK *ps, int i)
{
    if (ps->size >= STACKSIZE) {
        fprintf(stderr, "Error: stack overflow\n");
        abort();
    }

    ps->items[ps->size++] = i;
}


int pop(T_STACK *ps)
{
    if (ps->size <= 0) {
        fprintf(stderr, "Error: stack overflow\n");
        abort();
    }
    
    return ps->items[--ps->size];
}


int main(int argc, char **argv)
{
    T_STACK *stack = malloc(sizeof(T_STACK));
    printf("stack->size = %zu\n", stack->size);
    int i;
    for (i = 0; i < 7; ++i)
        push(stack, i);

    while (stack->size > 0)
        printf("pop(stack(%zu))-> %d\n", stack->size, pop(stack));

    return EXIT_SUCCESS;
}
