#include <stdio.h>
float sum_elements(float a[], unsigned length) {
    int i;
    float result = 0;

    for (i = 0; i <= length-1; i++)
        result += a[i];

    return result;
}

int main() {
    float a[3] = {1.0, 2.0, 3.0};

    printf("sum_elements: %f\n", sum_elements(a, 0));

    return 0;
}