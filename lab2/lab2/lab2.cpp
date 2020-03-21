#include "pch.h"
#include <windows.h>
#include <string>
#include <iostream>
#include <fstream>

#pragma comment(lib, "winmm.lib")

DWORD start = 0;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	start = timeGetTime();
	std::ofstream out;
	std::string file_name = "out" + std::to_string(*((int*)lpParam)) + ".txt";
	out.open(file_name);
	for (int i = 0; i < 25; i++) {
		std::cout << "Stream number " << *((int*)lpParam) << std::endl;
		out << (int)(timeGetTime() - start) << std::endl;
	}
	ExitThread(0);
}

int main(int argc)
{
	int* param = new int(2);
	for (int i = 0; i < 2; i++) {
		param[i] = i;
	}
	// создание двух потоков
	HANDLE* handles = new HANDLE[2];
	handles[0] = CreateThread(NULL, 0, &ThreadProc, &param[0], CREATE_SUSPENDED, NULL);
	handles[1] = CreateThread(NULL, 0, &ThreadProc, &param[1], CREATE_SUSPENDED, NULL);

	// запуск двух потоков
	for (int i = 0; i < 2; i++) {
		ResumeThread(handles[i]);
	}

	// ожидание окончания работы двух потоков
	WaitForMultipleObjects(argc, handles, true, INFINITE);
	return 0;
}
