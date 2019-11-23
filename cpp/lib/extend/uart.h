#pragma once

#include <stdlib.h>

extern int uart_fd;

int uart_init(const char *path);
int uart_close();

void uart_write(unsigned char *buf, size_t size);
void uart_read(unsigned char *buf, size_t size);
