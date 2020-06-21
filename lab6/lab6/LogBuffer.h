#pragma once

#include <fstream>
#include <windows.h>

#include "LogFileWriter.h"
#include "LinkedList.h"

class LogBuffer {
private:
	LinkedList list{};
	LogFileWriter log_file_writer{};
	CRITICAL_SECTION criticals_section;
	HANDLE event;
	HANDLE thread;

	void Notify();

public:
	LogBuffer();

	~LogBuffer();
	
	void Log(int);

	static DWORD WINAPI LogSizeMonitoringThread(CONST LPVOID);
};