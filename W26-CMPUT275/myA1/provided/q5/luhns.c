#include <stdio.h>
/*luhns.c tests for the validity of a number printing Valid if it passing luhns algorithm and Invalid otherwise*/
int main() {

    int number = (getchar() - '0');
    int nextNumber;
    int i = 1;
    int sumOdd = 0;
    int sumEven = 0;
    int finalSum;
    int digit;
    int nth_digit;
    while (number != -49 && number != -38) {

        nextNumber = (getchar() - '0');

        if (nextNumber == -49 || nextNumber == -38) {
            nth_digit = number;
            break;

        } else if (i % 2 == 0) {
            digit = number*2;
            sumEven = sumEven + number;
            if (digit >= 10) {
                sumOdd = sumOdd + (digit - 9);
            } else {
                sumOdd = sumOdd + digit;
            }

        } else {
            digit = number*2;
            sumOdd = sumOdd + number;
            if (digit >= 10) {
                sumEven = sumEven + (digit - 9);
            } else {
                sumEven = sumEven + digit;
            }
        }
        number = nextNumber;
        i = i + 1;
    }

    if (i % 2 == 0) {
        finalSum = sumEven;
    } else {
        finalSum = sumOdd;
    }
    if (((finalSum * 9) % 10) == nth_digit) {
            printf("Valid\n");
        } else {
            printf("Invalid\n");
        }
    return 0;
}
