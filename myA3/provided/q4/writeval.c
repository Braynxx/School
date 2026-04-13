#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "writeval.h"

#define TAG_INT  0
#define TAG_CHAR 1
#define TAG_PTR  2
#define TAG_STR  3

static char *align_ptr(char *p, size_t alignment) {
    size_t addr = (size_t)p;
    size_t rem = addr % alignment;

    if (rem == 0) {
        return p;
    }
    return (char *)(addr + (alignment - rem));
}

void *writeValue(void *writeLoc, const char *type, void *payload) {
    char *base  = (char *)writeLoc;
    char *dataLoc;
    unsigned char tag;

    if (strcmp(type, "int") == 0) {
        tag = TAG_INT;
    } else if (strcmp(type, "char") == 0) {
        tag = TAG_CHAR;
    } else if (strcmp(type, "ptr") == 0) {
        tag = TAG_PTR;
    } else if (strcmp(type, "str") == 0) {
        tag = TAG_STR;
    } else {
        return writeLoc;
    }

    *base = (char)tag;
    dataLoc = base + 1;

    if (tag == TAG_INT) {
        dataLoc = align_ptr(dataLoc, sizeof(int));
        *(int *)dataLoc = *(int *)payload;
        return dataLoc + sizeof(int);
    }

    if (tag == TAG_CHAR) {
        dataLoc = align_ptr(dataLoc, sizeof(char));
        *(char *)dataLoc = *(char *)payload;
        return dataLoc + sizeof(char);
    }

    if (tag == TAG_PTR) {
        dataLoc = align_ptr(dataLoc, sizeof(void *));
        *(void **)dataLoc = *(void **)payload;
        return dataLoc + sizeof(void *);
    }

    dataLoc = align_ptr(dataLoc, sizeof(char));
    strcpy(dataLoc, (char *)payload);
    return dataLoc + strlen((char *)payload) + 1;
}

void printValues(void *dataStart) {
    char *cur = (char *)dataStart;
    int index = 0;

    while((unsigned char)*cur != 0xFF) {
        unsigned char tag = (unsigned char)*cur;
        char *dataLoc = cur + 1;

        if (tag == TAG_INT) {
            dataLoc = align_ptr(dataLoc, sizeof(int));
            printf("Value %d at %p: %d\n", index, (void *)cur, *(int *)dataLoc);
            cur = dataLoc + sizeof(int);
        } else if (tag == TAG_CHAR) {
            dataLoc = align_ptr(dataLoc, sizeof(char));
            printf("Value %d at %p: '%c'\n", index, (void *)cur, *(char *)dataLoc);
            cur = dataLoc + sizeof(char);
        } else if (tag == TAG_PTR) {
            dataLoc = align_ptr(dataLoc, sizeof(void *));
            printf("Value %d at %p: %p\n", index, (void *)cur, *(void **)dataLoc);
            cur = dataLoc + sizeof(void *);
        } else if (tag == TAG_STR) {
            dataLoc = align_ptr(dataLoc, sizeof(char));
            printf("Value %d at %p: \"%s\"\n", index, (void *)cur,dataLoc);
            cur = dataLoc + strlen(dataLoc) + 1;
        } else {
            break;
        }
        index++;
    }
}
