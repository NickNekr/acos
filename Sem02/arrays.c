#include <stdio.h>

void ChangeArray(int* array) {
    // array[1] = 11;
    *(array + 1) = 11;

    printf("%s: %ld\n", __func__, sizeof(array));
}

int main() {
    int array[3] = {};

    for (int i = 0; i < 3; ++i) {
        printf("%d\n", array[i]);
    }

    printf("Array size: %ld\n", sizeof(array) / sizeof(int));

    int* parray = array;

    for (int i = 0; i < 3; ++i) {
        printf("%d\n", parray[i]);
    }

    printf("PArray size: %ld\n", sizeof(parray));


    ChangeArray(array);

    for (int i = 0; i < 3; ++i) {
        printf("%d\n", array[i]);
    }

    int array2[] = {1000, 993, 986};
    for (int i = 0; i < 3; ++i) {
        printf("%d\n", array[i + 4]);
    }
}
