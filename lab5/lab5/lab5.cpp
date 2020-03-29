#include "pch.h"
#include <windows.h>
#include <string>
#include <iostream>

CRITICAL_SECTION CriticalSection;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	// Request ownership of the critical section.
	EnterCriticalSection(&CriticalSection);

	int* working_variable = (int*)lpParam;

	// Access the shared resource.
	for (int i = 0; i < 50000; i++) {
		int j = *working_variable;
		*working_variable = j + 1;
	}

	// Release ownership of the critical section.
	LeaveCriticalSection(&CriticalSection);

	ExitThread(0); // функция устанавливает код завершения потока в 0
}


int main(int argc)
{
	int working_variable = 0;

	// Initialize the critical section one time only.
	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection,
		0x00000400))
		return 0;

	// создание двух потоков
	HANDLE* handles = new HANDLE[2];

	for (int i = 0; i < 2; i++) {
		handles[i] = CreateThread(NULL, i, &ThreadProc, &working_variable, CREATE_SUSPENDED, NULL);
		SetThreadAffinityMask(handles[i], 1 << 4);
	}

	// запуск двух потоков
	for (int i = 0; i < 2; i++) {
		ResumeThread(handles[i]);
	}

	// ожидание окончания работы двух потоков
	WaitForMultipleObjects(2, handles, true, INFINITE);

	std::cout << working_variable << std::endl;

	// Release resources used by the critical section object.
	DeleteCriticalSection(&CriticalSection);

	return 0;
}