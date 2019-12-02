#include <stdio.h>
#include <string.h>

#include "uart.hpp"

#ifdef __linux__
    #include <errno.h>
    #include <fcntl.h>
    #include <termios.h>
    #include <unistd.h>
    int uart_fd;
#elif defined(_WIN32)
    #include <Windows.h>
    #include <string>
    HANDLE hComm;
    std::string ComPortName = "\\\\.\\";
    BOOL Status;
#else
    #error Unsupported operating system. Please use either Linux or Windows.
#endif

/**
 * Initialize the serial port connection depending on the operating system.
 */

int uart_init(const char *path)
{
#ifdef __linux__
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

#else // _WIN32

    ComPortName += path;

    // opening the serial port
    hComm = CreateFile(
        ComPortName.c_str(),
        GENERIC_READ | GENERIC_WRITE,   // read/write access
        0,                              // no sharing, ports can't be shared
        NULL,                           // no security
        OPEN_EXISTING,                  // open existing port only
        0,                              // non overlapped I/O
        NULL                            // null for comm devices
    );

    if (hComm == INVALID_HANDLE_VALUE) {
        fprintf(stderr, "Serial Port Error: Port %s can't be opened\n", ComPortName);
        exit(-1);
    }

    // initializing DCB structure
    DCB dcb_params = { 0 };
    dcb_params.DCBlength = sizeof(dcb_params);

    // retrieve current settings
    Status = GetCommState(hComm, &dcb_params);

    if (!Status) {
        fprintf(stderr, "Serial Port Error: Could not obtain COM port state\n");
        exit(-1);
    }

    dcb_params.BaudRate = CBR_256000;   // BaudRate = 256000
    dcb_params.ByteSize = 8;            // ByteSize = 8
    dcb_params.StopBits = ONESTOPBIT;   // StopBits = 1
    dcb_params.Parity   = NOPARITY;     // Parity   = None

    // configure the port according to settings in DCB
    Status = SetCommState(hComm, &dcb_params);

    if (!Status) {
        fprintf(stderr, "Serial Port Error: Could not set DCB structure\n");
        exit(-1);
    }

    // timeouts
    COMMTIMEOUTS timeouts = { 0 };
    timeouts.ReadIntervalTimeout         = 50;
    timeouts.ReadTotalTimeoutConstant    = 50;
    timeouts.ReadTotalTimeoutMultiplier  = 10;
    timeouts.WriteTotalTimeoutConstant   = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(hComm, &timeouts)) {
        fprintf(stderr, "Serial Port Error: Could not set timeouts\n");
        exit(-1);
    }
#endif

    return 1;
}

/**
 * Serial port tear-down depending on the operating system
 */

int uart_close()
{
#ifdef __linux__
    return close(uart_fd);
#else // _WIN32
    return CloseHandle(hComm);
#endif
}

/**
 * Write data from the computer to the serial port
 */

void uart_write(unsigned char *buf, size_t size)
{
#ifdef __linux__
    write(uart_fd, buf, size);
#else // _WIN32
    DWORD  bytes_written = 0;
    Status = WriteFile(
        hComm,          // serial port handle
        buf,            // data to be written
        (DWORD)size,    // num bytes to write
        &bytes_written, // num bytes written
        NULL
    );

    printf("Bytes written: %ld\n", bytes_written);

    if (!Status) {
        fprintf(stderr, "Serial Port Error: Code %d received in writing to serial port\n", GetLastError());
        exit(-1);
    }
#endif
}

/**
 * Read data from the serial port to the computer
 */

void uart_read(unsigned char *buf, size_t size)
{
#ifdef __linux__
    read(uart_fd, buf, size);
#else // _WIN32
    // set receive mask to configure Windows to monitor the serial device for character reception
    Status = SetCommMask(hComm, EV_RXCHAR);

    if (!Status) {
        fprintf(stderr, "Serial Port Error: Could not set CommMask\n");
        exit(-1);
    }

    // wait for the character to be received from even_mask trigger
    DWORD event_mask;
    Status = WaitCommEvent(hComm, &event_mask, NULL);

    // wait until a character is received
    char rx_byte;
    DWORD bytes_read;
    int i = 0;

    // read rx data
    if (!Status) {
        fprintf(stderr, "Serial Port Error: Could not set WaitCommEvent\n");
        exit(-1);
    }
    else {
        do {
            Status = ReadFile(hComm, &rx_byte, sizeof(rx_byte), &bytes_read, NULL);
            if (i < size)
                buf[i++] = rx_byte;
        } while (bytes_read > 0);
    }
#endif
}
