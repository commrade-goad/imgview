#include "str.h"

str_t str_init(int cap) {
    if (cap == -1)
        cap = 10;
    str_t a = (str_t){
        .data = malloc(sizeof(char) * cap),
        .len = 0,
        .cap = cap,
    };
    a.data[0] = '\0';
    return a;
}

void str_deinit(str_t *str) {
    if (str && str->data) {
        free(str->data);
        str->data = NULL;
        str->len = 0;
        str->cap = 0;
    }
}

void str_push_chr(str_t *str, const char data) {
    if (str->len + 2 >= str->cap) {
        str->cap *= 2;
        str->data = realloc(str->data, sizeof(char) * str->cap);
    }
    str->data[str->len] = data;
    str->len += 1;
    str->data[str->len] = '\0';
}

void str_pop_chr(str_t *str) {
    if (str->len > 0) {
        str->len -= 1;
        str->data[str->len] = '\0';
    }
}

void str_clear(str_t *str) {
    str->len = 0;
    str->data[0] = '\0';
}
