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

    int longest = strlen(search->text);
    int shortest = strlen(search->text);

    while(search->link != NULL)
    {
        search = search->link;

        if(longest < strlen(search->text))
        {
            longest = strlen(search->text);
        }

        if(shortest > strlen(search->text))
        {
            shortest = strlen(search->text);
        }
    }

    printf("%d %d\n", longest, shortest);
}
//duplicate and unique lines
void dup_uniq_lines(struct head_t *S) {
    int n = S->lines;
    struct text_t nodes[n];

    struct text_t *cur = S->link;
    for (int i = 0; i<n; i++) {
        nodes[i] = *cur;
        cur = cur->link;
    }

    int visited[n];
    for (int i = 0; i<n; i++)
        visited[i] = 0;

    int unique = 0;
    int duplicate = 0;

    for (int i = 0; i<n; i++) {
        if(visited[i] == 1)
            continue; //skipping read lines

        int count = 1; //number of occurances

        for (int next = i+1; next<n; next++) {
            if (strcmp(nodes[i].text, nodes[next].text) == 0) { //checking for duplicates
                duplicate = duplicate + 1; //increasing number of occurances of duplicate
                //printf("dupe found!\n");
                visited[next]=1; //marking line as read
            }
            else
            {
                //printf("No dupe here!\n");
            }
        }

        unique++;
        if (count>1)
            duplicate++;
    }

    printf("Number of unique lines = %d\n", unique);
    printf("Number of duplicate lines = %d\n", duplicate);
}

int main(int argc, char *argv[]) {
    FILE *fp = fopen(argv[1],"r");
    if (fp == NULL)
        return -1;
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
    dup_uniq_lines(storage);
}