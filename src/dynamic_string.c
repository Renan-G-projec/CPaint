// Ad Maiorem Dei Gloriam!
#include "dynamic_string.h"
#include "assert.h"
#include <stdlib.h>
#include <string.h>

CPaintDynamicString dynamic_string_new(int buffer_size)
{
    assert(buffer_size > 0 && "Error: Buffer size shall be greater than zero.");
    CPaintDynamicString str;

    str.buffer = (char*)malloc((size_t)buffer_size * sizeof(char));
    str.length = 0;
    str.capacity = 0;

    if (str.buffer)
    {
        str.capacity = buffer_size;
        str.length = buffer_size - 1;
    }

    return str;
}

void dynamic_string_set(CPaintDynamicString *dystr, const char *str)
{
    size_t len = strnlen(str, dystr->capacity) + 1;
    if (len >= dystr->capacity)
    {
        if (dystr->buffer) free(dystr->buffer);
        dystr->buffer = (char *)malloc(len * sizeof(char));

        if (dystr->buffer)
        {
            dystr->capacity = len;
            dystr->length = len - 1;
        }
        else
        {
            dystr->capacity = 0;
            dystr->length = 0;
            return;
        }
    }

    strncpy(dystr->buffer, str, dystr->length);
    dystr->buffer[dystr->capacity - 1] = '\0';
}

const char *dynamic_string_get_cstr(CPaintDynamicString *dystr)
{
    if (dystr->length <= 0 || !dystr->buffer) return "";
    return dystr->buffer; // Confirmed to be null terminated.
}

void dynamic_string_delete(CPaintDynamicString *dystr)
{
    if (dystr->buffer) free(dystr->buffer);
}