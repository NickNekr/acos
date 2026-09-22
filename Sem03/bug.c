#include <stdio.h>

void copy_text(char *dst, const char *src, size_t size) {
    snprintf(dst, size, "%s", src);
}

int main(void) {
    char text[32];
    const char src[] = "Programming";

    copy_text(text, src, sizeof(src));
    printf("Result: %s\n", text);

    return 0;
}
