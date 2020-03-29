#include "pch.h"
#include <windows.h>
#include <string>
#include <iostream>

CRITICAL_SECTION CriticalSection;

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	EnterCriticalSection(&CriticalSection);

	int* working_variable = (int*)lpParam;

	for (int i = 0; i < 50000; i++) {
		int j = *working_variable;
		*working_variable = j + 1;
	}

	LeaveCriticalSection(&CriticalSection);

	ExitThread(0);
}


int main(int argc)
{
	int working_variable = 0;

	if (!InitializeCriticalSectionAndSpinCount(&CriticalSection,
		0x00000400))
		return 0;

	HANDLE* handles = new HANDLE[2];

	for (int i = 0; i < 2; i++) {
		handles[i] = CreateThread(NULL, i, &ThreadProc, &working_variable, CREATE_SUSPENDED, NULL);
		SetThreadAffinityMask(handles[i], 1 << 4);
	}

	for (int i = 0; i < 2; i++) {
		ResumeThread(handles[i]);
	}

	WaitForMultipleObjects(2, handles, true, INFINITE);

	std::cout << working_variable << std::endl;

	DeleteCriticalSection(&CriticalSection);

	return 0;
}