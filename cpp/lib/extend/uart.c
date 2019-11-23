#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>

#include "uart.h"

int uart_fd;

int uart_init(const char *path)
{
    uart_fd = open(path, O_RDWR | O_NOCTTY | O_NDELAY);

    if (uart_fd = -1) {
        fprintf(stderr, "Error: Could not open serial connection to %s\n", path);
        return 0;
    }

    struct termios serial_settings;
    tcgetattr(uart_fd, &serial_settings);

    cfsetispeed(&serial_settings, B921600);
    cfsetospeed(&serial_settings, B921600);

    serial_settings.c_cflag &= ~PARENB;         // disable parity
    serial_settings.c_cflag &= ~CSTOPB;         // 1 stop bit
    serial_settings.c_cflag &= ~CSIZE;          // clear mask for size setting
    serial_settings.c_cflag |= CS8;             // set bit size to 8 bits per data
    serial_settings.c_cflag &= ~CRTSCTS;        // no hardware flow control
    serial_settings.c_cflag |= CREAD | CLOCAL;  // receiver en, ignore modem control lines

    serial_settings.c_iflag &= ~(IXON | IXOFF | IXANY); // disable xon/xoff for input and output
    serial_settings.c_iflag &= ~(ICANON | ECHO | ECHOE | ISIG); // non cannonical mode

    serial_settings.c_oflag &= ~OPOST; // no output processing


    if ((tcsetattr(uart_fd, TCSANOW, &serial_settings)) != 0) {
        fprintf(stderr, "Error: Could not initialize uart file descriptor attributes\n");
        return 0;
    }

    return 1;
}

int uart_close()
{
    return close(uart_fd);
}

void uart_write(unsigned char *buf, size_t size)
{
    write(uart_fd, buf, size);
}

void uart_read(unsigned char *buf, size_t size)
{
    read(uart_fd, buf, size);
}
