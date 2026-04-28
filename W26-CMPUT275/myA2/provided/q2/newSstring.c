#include <stdio.h>
#include <stdlib.h>

int main() {
    int arr[3] = {1, 2, 3};
    for (int *p = arr; p < arr + 3; ++p){
        printf("%d\n", *p);
    }
}

