#include "buffer.h"


struct buffer buffer_create() {
    return (struct buffer) {
        .data = malloc(sizeof(uint8_t) * BUFSIZE),
        .ptr_in = 0,
        .ptr_out = 0
    };
}

void buffer_push(struct buffer* buffer, uint8_t value) {
    buffer->data[buffer->ptr_in++] = value;
    if (buffer->ptr_in >= BUFSIZE) buffer->ptr_in = 0;
}

uint8_t buffer_pop(struct buffer* buffer) {
    uint8_t ret = buffer->data[buffer->ptr_out++];
    if (buffer->ptr_out >= BUFSIZE) buffer->ptr_out = 0;
    return ret;
}

uint8_t buffer_get(struct buffer* buffer) {
    return buffer->data[buffer->ptr_out];
}

void buffer_clear(struct buffer* buffer) {
    buffer->ptr_in = 0;
    buffer->ptr_out = 0;
}

int8_t buffer_elements(struct buffer* buffer) {
    if (buffer->ptr_in >= buffer->ptr_out)
        return (buffer->ptr_in - buffer->ptr_out);
    else
        return ((BUFSIZE - buffer->ptr_out) + buffer->ptr_in);
}
