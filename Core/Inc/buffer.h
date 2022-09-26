#ifndef BUFFER_H
#define BUFFER_H

#include <stdint.h>

#define BUFSIZE 256

void buffer_push(char value);
char buffer_pop();
char buffer_get();
void buffer_clear();
int16_t buffer_elements();
char* getBuffer();

#endif
