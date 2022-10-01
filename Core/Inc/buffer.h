#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#define BUFSIZE 256

struct buffer {
    uint8_t* data;
    int8_t ptr_in;
    int8_t ptr_out;
};

struct buffer buffer_create();
void buffer_push(struct buffer* buffer, uint8_t value);
uint8_t buffer_pop(struct buffer* buffer);
uint8_t buffer_get(struct buffer* buffer);
void buffer_clear(struct buffer* buffer);
int8_t buffer_elements(struct buffer* buffer);

#endif
