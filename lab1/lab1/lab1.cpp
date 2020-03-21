#include "pch.h"
#include <windows.h>
#include <string>
#include <iostream>

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	std::cout << "Stream number " << *((int*)lpParam) << " doing his job" << std::endl;
	ExitThread(0); // функция устанавливает код завершения потока в 0
}


int main(int argc)
{
	int* param = new int(argc);
	for (int i = 0; i < argc; i++) {
		param[i] = i;
	}
	// создание двух потоков
	HANDLE* handles = new HANDLE[argc];
	for (int i = 0; i < argc; i++) {
		handles[i] = CreateThread(NULL, i, &ThreadProc, &param[i], CREATE_SUSPENDED, NULL);
	}

	// запуск двух потоков
	for (int i = 0; i < argc; i++) {
		ResumeThread(handles[i]);
	}

	// ожидание окончания работы двух потоков
	WaitForMultipleObjects(argc, handles, true, INFINITE);
	return 0;
}
