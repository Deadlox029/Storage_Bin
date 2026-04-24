//
// Created by deadlox029 on 4/24/26.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct head_t {
    int lines;
    struct text_t *link;
};

struct text_t {
    char *text;
    struct text_t *link;
};

void readFile(FILE *fp, struct head_t *S) {
    char buffer[1000];
    struct text_t *current = NULL;

    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        struct text_t *t = malloc(sizeof(struct text_t));
        t->text = strdup(buffer);
        t->link = NULL;

        if (S->link == NULL) {
            S->link = t;
        } else {
            current->link = t;
        }
        current = t;
        S->lines++;
    }
}

int main() {
    struct head_t *storage = malloc(sizeof(struct head_t));
    storage->lines = 0;
    storage->link = NULL;
    readFile("input.txt", storage);

}
