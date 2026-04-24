//
// Created by DSU on 4/24/2026.
//
int lastline_dup(struct head_t *S) {
    struct text_t *mov;
    mov = S->link;
    if (mov->link != NULL) {
        mov = mov->link;
    }
    char origin[] = mov->text;
    mov = S->link;
    for (int i = 0; i < S->lines; i++) {
        if (strcmp(origin, mov->text) == 0) {
            return 1;
        }
        mov = mov->link;
    }
    return 0;
}