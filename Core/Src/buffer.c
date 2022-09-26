#include "buffer.h"

int8_t ptr_in = 0;
int8_t ptr_out = 0;

char buffer[BUFSIZE];

void buffer_push(char value) {
    buffer[ptr_in++] = value;
    if (ptr_in >= BUFSIZE) ptr_in = 0;
}

char buffer_pop() {
    char ret = buffer[ptr_out++];
    if (ptr_out >= BUFSIZE) ptr_out = 0;
    return ret;
}

char buffer_get() {
    return buffer[ptr_out];
}

void buffer_clear() {
    ptr_in = 0;
    ptr_out = 0;
}

int16_t buffer_elements() {
    if (ptr_in >= ptr_out)
        return (ptr_in - ptr_out);
    else
        return ((BUFSIZE - ptr_out) + ptr_in);
}

char* getBuffer() {
    return buffer;
}
