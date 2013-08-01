#include <stdio.h>

int main() {
    int age = 25;
    int height = 72;

    printf("I am %d years old.\n", age);
    printf("I am %d inches tall.\n", height);

    /*extra credit*/
    printf("\a - beep\n");
    printf("\b - backspace\n");
    printf("\f - formfeed\n");
    printf("\n - newline\n");
    printf("\r - carriage return\n");
    printf("\t - horizontal tab\n");
    printf("\\ - backslash\n");
    printf("\' - single quotation mark\n");
    printf("\" - double quotation mark\n");
    /*printf("\o141 - Octal code\n");*/
    printf("\x61 - Hex code\n");
    return 0;
}
