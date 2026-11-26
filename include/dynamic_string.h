// Ad Maiorem Dei Gloriam!
#ifndef DYNAMIC_STRING_H
#define DYNAMIC_STRING_H

typedef struct {
    char *buffer;
    int capacity;
    int length;
} CPaintDynamicString;

// Buffer-size includes the null terminator
CPaintDynamicString dynamic_string_new(int buffer_size);
void dynamic_string_set(CPaintDynamicString *dystr, const char *str);
const char *dynamic_string_get_cstr(CPaintDynamicString *dystr);
void dynamic_string_delete(CPaintDynamicString *dystr);

#endif