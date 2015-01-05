#include <stdio.h>
#include <stdlib.h>
#include <time.h>


typedef struct node {
    int data;
    struct node *next;
} Stack;


void push(Stack **ps, int i)
{
    struct node *s = malloc(sizeof(struct node));

    if (s == NULL) {
        fprintf(stderr, "Error: stack overflow.\n");
        abort();
    }

    s->data = i;
    s->next = *ps;
    *ps = s;
}

int pop(Stack **ps)
{
    Stack *s = *ps;
    int data;

    if (*ps == NULL) {
        fprintf(stderr, "Error: stack underflow.\n");
        abort();
    } else {
        data = (*ps)->data;
        if ((*ps)->next)
            *ps = (*ps)->next;
        free(s);
    }

    return data;
}

void iter_stack(Stack **ps)
{
    if (*ps == NULL) {
        fprintf(stderr, "Error: stack underflow.\n");
        abort();
    }

    Stack *curr = *ps;
    printf("\n-------------------\n");
    printf("iter_stack:");

    while (curr != NULL) {
        printf("%d ", curr->data);
        curr = curr->next;
    }

    printf("\n-------------------\n");
}

void free_stack(Stack **ps)
{
    struct node *curr = *ps;
    struct node *tmp;

    while (curr != NULL) {
        tmp = curr;
        curr = curr->next;
        free(tmp);
    }

    *ps = NULL;
}

int main(int argc, char **argv)
{
    Stack *stack = NULL;
    time_t t;
    srand((unsigned) time(&t));

    int i, n;
    for (i = 0; i < 5; ++i) {
        n = rand() % 50;
        printf("(%d) push(&stack, %d)\n", __LINE__, n);
        push(&stack, n);
    }

    iter_stack(&stack);

    /*int data;
    while ((data = pop(&stack)) != NULL) {
        printf("(%d) pop(&stack): %d\n", __LINE__, data);
    }*/

    printf("(%d) pop(&stack): %d\n", __LINE__, pop(&stack));
    printf("(%d) pop(&stack): %d\n", __LINE__, pop(&stack));
    printf("(%d) pop(&stack): %d\n", __LINE__, pop(&stack));
    printf("(%d) pop(&stack): %d\n", __LINE__, pop(&stack));

    push(&stack, 1);
    push(&stack, 11);
    iter_stack(&stack);
    free_stack(&stack);

    return EXIT_SUCCESS;
}
