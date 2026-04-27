//
// Created by DSU on 4/24/2026.
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

int lastline_dup(struct head_t *S) {
    struct text_t *mov;
    mov = S->link;
    while (mov->link != NULL) {
        mov = mov->link;
    }
    char *origin = mov->text;
    mov = S->link;
    for (int i = 0; i < S->lines-1; i++) {
        if (strcmp(origin, mov->text) == 0) {
            return 1;
        }
        mov = mov->link;
    }
    return 0;
}

void longest(struct head_t *S){
    // How long is the longest text
    struct text_t *search = S->link;

    int longest = strlen(search->text)-1;
    int shortest = strlen(search->text)-1;

    while(search->link != NULL)
    {
        search = search->link;

        if(longest < strlen(search->text)-1)
        {
            longest = strlen(search->text)-1;
        }

        if(shortest > strlen(search->text)-1)
        {
            shortest = strlen(search->text)-1;
        }
    }

    printf("%d %d\n", longest, shortest);
}


int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1],"r");
    struct head_t *storage = malloc(sizeof(struct head_t));
    storage->lines = 0;
    storage->link = NULL;
    readFile(fp, storage);
    int Lflag = lastline_dup(storage);
    if (Lflag==1)
        printf("Last Line is duplicated\n");
    if (Lflag==0)
        printf("Last Line is NOT duplicated\n");
    longest(storage);
}
