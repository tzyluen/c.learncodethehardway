/**
 * Structure packing suppresses structure padding.
 * Padding used when alignment matters most, packing used when
 * space matters most.
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

// 64-bit machine 
struct foo1 {
    char *p;     /* 8 bytes */
    char c;      /* 1 byte */
    //char pad[7]; /* 7 bytes */ will be padded automatically
    long x;      /* 8 bytes */

    // largest structure member is long, therefore total size of the
    // structure should be a multiple of the largest alignment of any
    // structure member.
    // In 64 bit, alignment(long) = 8; sizeof(fool) = 24
};

/**
 * GCC - __attribute__((__packed__)) explicitly prevents compiler from
 * doing padding.
 */
struct __attribute__((__packed__)) foo2 {
    char c;      /* 1 byte */
    char *p;     /* 8 bytes */
    long x;      /* 8 bytes */
};

int main(int argc, char **argv)
{
    printf("sizeof(char*): %zu\n", sizeof(char*));
    printf("sizeof(char) : %zu\n", sizeof(char));
    printf("sizeof(long) : %zu\n", sizeof(long));

    printf("sizeof struct foo1: %zu\n", sizeof(struct foo1));
    printf(" p:%zu\n", offsetof(struct foo1, p));
    printf(" c:%zu\n", offsetof(struct foo1, c));
    //printf(" pad:%zu\n", offsetof(struct foo1, pad));
    printf(" x:%zu\n", offsetof(struct foo1, x));

    printf("sizeof struct foo2: %zu\n", sizeof(struct foo2));
    printf(" p:%zu\n", offsetof(struct foo2, p));
    printf(" c:%zu\n", offsetof(struct foo2, c));
    printf(" x:%zu\n", offsetof(struct foo2, x));

    exit(EXIT_SUCCESS);
}
