#ifndef STR_H_
#define STR_H_

#include <stdlib.h>
#include <string.h>

typedef struct str_t {
    char *data;
    size_t len;
    size_t cap;
} str_t;

str_t str_init(int cap);
void str_deinit(str_t *str);
void str_push_chr(str_t *str, const char data);
void str_pop_chr(str_t *str);
void str_clear(str_t *str);

#endif // STR_H_
