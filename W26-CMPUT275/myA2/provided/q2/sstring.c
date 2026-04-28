#include <stdio.h>
#include <stdlib.h>

typedef struct {
    char *data;
    unsigned int size;
    unsigned int capacity;
} SString;

int is_whitespace(int c) {
    return (c == ' ' || c == '\n' || c == '\r' || c == '\t' || c == '\v' || c == '\f');
}

void initSString(SString *s) {
    s->size = 0;
    s->capacity = 4;
    s->data = malloc(sizeof(char) * s->capacity);
}

void appendChar(SString *s, char c) {
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        s->data = realloc(s->data, sizeof(char) * s->capacity);
    }
    s->data[s->size++] = c;
}

SString* getTarget(char name, SString *a, SString *b, SString *c, SString *d) {
    if (name == 'a') return a;
    if (name == 'b') return b;
    if (name == 'c') return c;
    if (name == 'd') return d;
    return NULL;
}

void readInput(SString *s, int appendMode) {
    if (!appendMode) s->size = 0;
    int c;
    while ((c = getchar()) != EOF && is_whitespace(c));
    if (c == EOF) return;

    if (c == '"') {
        while ((c = getchar()) != EOF && c != '"') appendChar(s, (char)c);
    } else {
        appendChar(s, (char)c);
        while ((c = getchar()) != EOF && !is_whitespace(c)) appendChar(s, (char)c);
    }
}

int main() {
    SString a, b, c, d;
    initSString(&a); initSString(&b); initSString(&c); initSString(&d);

    char cmd;
    while (scanf(" %c", &cmd) != EOF && cmd != 'q') {
        char name;
        if (cmd == 'r' || cmd == 'a') {
            if (scanf(" %c", &name) != 1) break;
            readInput(getTarget(name, &a, &b, &c, &d), (cmd == 'a'));
        } else if (cmd == 'p' || cmd == 'd') {
            if (scanf(" %c", &name) != 1) break;
            SString *t = getTarget(name, &a, &b, &c, &d);
            if (cmd == 'd') printf("String: \"");
            for (unsigned int i = 0; i < t->size; i++) putchar(t->data[i]);
            if (cmd == 'd') printf("\"\nLength: %u\nCapacity: %u\n", t->size, t->capacity);
            else putchar('\n');
        } else if (cmd == 'c') {
            char n1, n2, n3;
            if (scanf(" %c %c %c", &n1, &n2, &n3) != 3) break;
            SString *dest = getTarget(n1, &a, &b, &c, &d);
            SString *src1 = getTarget(n2, &a, &b, &c, &d);
            SString *src2 = getTarget(n3, &a, &b, &c, &d);

            dest->size = 0;
            for(unsigned int i = 0; i < src1->size; i++) appendChar(dest, src1->data[i]);
            for(unsigned int i = 0; i < src2->size; i++) appendChar(dest, src2->data[i]);
        }
    }
    free(a.data); free(b.data); free(c.data); free(d.data);
    return 0;
}
