#pragma once

#include <windows.h>

class Task {
public:
	~Task() = default;
	virtual void execute() = 0;
};

static DWORD WINAPI threadProc(CONST LPVOID lpParam) {
	Task* task = (Task*)lpParam;
	task->execute();
 	ExitThread(0);
}
