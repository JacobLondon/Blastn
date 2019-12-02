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
	HANDLE hComm;
	char ComPortName[] = "\\\\.\\COM10";
	BOOL Status;
#else
	#error Unsupported operating system. Please use either Linux or Windows.
#endif

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

	// opening the serial port
	hComm = CreateFile(
		ComPortName,
		GENERIC_READ | GENERIC_WRITE,	// Read/Write Access
		0,								// No Sharing, ports cant be shared
		NULL,							// No Security
		OPEN_EXISTING,					// Open existing port only
		0,								// Non Overlapped I/O
		NULL							// Null for Comm Devices
	);

	if (hComm == INVALID_HANDLE_VALUE)
		fprintf(stderr, "Serial Port Error: Port %s can't be opened\n", ComPortName);

	// Initializing DCB structure
	DCB dcbSerialParams = { 0 };
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);

	// Retreives current settings
	Status = GetCommState(hComm, &dcbSerialParams);

	if (!Status) {
		fprintf(stderr, "Serial Port Error: Could not obtain COM port state GetCommState()\n");
		exit(-1);
	}

	dcbSerialParams.BaudRate = CBR_256000;	// Setting BaudRate = 256000
	dcbSerialParams.ByteSize = 8;			// Setting ByteSize = 8
	dcbSerialParams.StopBits = ONESTOPBIT;	// Setting StopBits = 1
	dcbSerialParams.Parity = NOPARITY;		// Setting Parity = None 

	Status = SetCommState(hComm, &dcbSerialParams);	// Configuring the port according to settings in DCB 

	if (!Status) {
		fprintf(stderr, "Serial Port Error: Could not set DCB structure\n");
		exit(-1);
	}

	// timeouts
	COMMTIMEOUTS timeouts = { 0 };

	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;

	if (!SetCommTimeouts(hComm, &timeouts)) {
		fprintf(stderr, "Serial Port Error: Could not set time out");
		exit(-1);
	}
#endif

    return 1;
}

int uart_close()
{
#ifdef __linux__
    return close(uart_fd);
#else // _WIN32
	return CloseHandle(hComm);
#endif
}

void uart_write(unsigned char *buf, size_t size)
{
#ifdef __linux__
    write(uart_fd, buf, size);
#else // _WIN32
	DWORD  dNoOfBytesWritten = 0;
	Status = WriteFile(
		hComm,				// Handle to the Serialport
		buf,				// Data to be written to the port 
		(DWORD)size,		// No of bytes to write into the port
		&dNoOfBytesWritten,	// No of bytes written to the port
		NULL
	);

	printf("Bytes written: %ld\n", dNoOfBytesWritten);

	if (!Status) {
		fprintf(stderr, "Serial Port Error: %d in writing to serial port\n", GetLastError());
		exit(-1);
	}
#endif
}

void uart_read(unsigned char *buf, size_t size)
{
#ifdef __linux__
    read(uart_fd, buf, size);
#else // _WIN32
	// setting receive mask
	// configure Windows to monitor the serial device for character reception
	Status = SetCommMask(hComm, EV_RXCHAR);

	if (!Status) {
		fprintf(stderr, "Serial Port Error: Could not set CommMask\n");
		exit(-1);
	}

	// Event mask to trigger
	DWORD dwEventMask;

	// Wait for the character to be received
	Status = WaitCommEvent(hComm, &dwEventMask, NULL);

	// wait until a character is received
	char TempChar;			// Temperory Character
	DWORD NoBytesRead;		// Bytes read by ReadFile()
	int i = 0;

	if (!Status) {
		fprintf(stderr, "Serial Port Error: Could not set WaitCommEvent()\n");
		exit(-1);
	}

	// read the RXed data using ReadFile();
	else {
		do {
			Status = ReadFile(hComm, &TempChar, sizeof(TempChar), &NoBytesRead, NULL);
			if (i < size)
				buf[i++] = TempChar;
		} while (NoBytesRead > 0);
	}
#endif
}
