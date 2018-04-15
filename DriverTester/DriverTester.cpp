// DriverTester.cpp: define el punto de entrada de la aplicación de consola.
//

#include "stdafx.h"

using namespace std;

int main(int argc, char* argv[])
{
	HANDLE handle;
	bool bResult;
	string driverName;
	DWORD ioctl;
	char* buffer = NULL;
	DWORD dwBytes;

	// clear creen
	system("cls");

	// check number of arguments
	if (argc < 3 || argc > 4) {
		cout << "[-] Too few arguments. Usage: DriverTester.exe drivername ioctl [buffer]" << endl;
	}

	// parse arguments
	driverName = "\\\\.\\" + string(argv[1]);
	ioctl = strtoul(argv[2], 0, 16);
	if (argc == 4) {
		buffer = argv[3];
	}

	// connect to device
	handle = CreateFileA(driverName.c_str(), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (handle == INVALID_HANDLE_VALUE) {
		cout << "[-] Couldn't obtain a handle to the Device." << endl;
		return -1;
	}
		
	// send IOCTL to the driver
	bResult = DeviceIoControl(handle, ioctl, buffer, sizeof(*buffer), NULL, NULL, &dwBytes, NULL);

	if (bResult == NULL) {
		CloseHandle(handle);
		cout << "[-] DeviceIoControl failed!" << endl;
		return -2;
	}

	// close handle
	CloseHandle(handle);

	// wait for char and exit
	cout << "[+] DeviceIoControl sucess! Press any key to exit." << endl;
	getchar();

    return 0;
}

