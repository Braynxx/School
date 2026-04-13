#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct {
    char oper[5];
    int number;
} Operation;

long int performOp(long int value, char oper[], int number) {
    if (strcmp(oper, "add") == 0) {
        value += number;
    } else if (strcmp(oper, "sub") == 0) {
        value -= number;
    } else if (strcmp(oper, "mul") == 0) {
        value *= number;
    } else if (strcmp(oper, "div") == 0) {
        value /= number;
    }
    return value;
}

int main(int argc, char *argv[]) {
    char *argNum = argv[1];
    long int value = strtol(argNum, NULL, 10);
    Operation opers[100];
    int operCount = 0;
    char nextOp[5];
    while (scanf("%4s", nextOp) == 1) {
        if (strcmp(nextOp, "n") == 0) {
            for (int i = 0; i < operCount; i++){
                value = performOp(value, opers[i].oper, opers[i].number);
            }
            printf("%ld\n", value); 
        } else {
            strcpy(opers[operCount].oper, nextOp);
            scanf("%d", &opers[operCount].number);
            operCount++;
        }
    }       
    return 0;
}
