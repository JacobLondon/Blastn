#pragma once

#include <stdlib.h>

#ifdef __linux__
	extern int uart_fd;
#elif defined(_WIN32)
	#include <Windows.h>
	extern HANDLE hComm;
#else
	#error Unsupported operating system. Please use either Linux or Windows.
#endif

int uart_init(const char *path);
int uart_close();

void uart_write(unsigned char *buf, size_t size);
void uart_read(unsigned char *buf, size_t size);
