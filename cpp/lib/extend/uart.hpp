#pragma once

#include <stdlib.h>

#include <Windows.h>
extern HANDLE hComm;

int uart_init(const char *path);
int uart_close();

void uart_write(unsigned char *buf, size_t size);
void uart_read(unsigned char *buf, size_t size);