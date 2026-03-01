#include <stdio.h>
#include <stdlib.h>

int main (int argc, char *argv[]) {
    unsigned int first_num = atoi(argv[1]);
    unsigned int second_num = atoi(argv[2]);
    unsigned int base_arg = atoi(argv[3]);
    unsigned int ham_sum = 0;
    while (first_num > 0 || second_num > 0) {
        if (first_num == 0 || second_num == 0) {
            ham_sum = ham_sum + 1;
        } else if ((first_num % base_arg) != (second_num % base_arg)) {
            ham_sum = ham_sum + 1;
        }
        first_num = first_num / base_arg;
        second_num = second_num / base_arg;
    }
    printf("%d\n", ham_sum);
    return 0;
}