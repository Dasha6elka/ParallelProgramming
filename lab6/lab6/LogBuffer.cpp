#include "LogBuffer.h";

int MAX_BUFFER_COUNT = 10;

LogBuffer:: LogBuffer() {
	InitializeCriticalSectionAndSpinCount(&criticals_section, 0x00000400);

	event = CreateEvent(nullptr, TRUE, FALSE, TEXT("Event"));

	thread = CreateThread(NULL, 0, &LogSizeMonitoringThread, (void*)this, 0, NULL);
}

LogBuffer::~LogBuffer() {
	DeleteCriticalSection(&criticals_section);
}

void LogBuffer::Log(int value) {
	EnterCriticalSection(&criticals_section);

	if (list.Count() >= MAX_BUFFER_COUNT) {
		Notify();
	}

	list.Add(value);

	LeaveCriticalSection(&criticals_section);
}

void LogBuffer::Notify() {
	SetEvent(event);

	DWORD wait = WaitForSingleObject(thread, INFINITE);

	if (wait == WAIT_OBJECT_0) {
		ResetEvent(event);
		thread = CreateThread(NULL, 0, &LogSizeMonitoringThread, (void*)this, 0, NULL);
	}
}

DWORD WINAPI LogBuffer::LogSizeMonitoringThread(CONST LPVOID lp_param) {
	LogBuffer* data = (LogBuffer*)lp_param;

	DWORD wait = WaitForSingleObject(data->event, INFINITE);
	
	if (wait == WAIT_OBJECT_0) {
		data->log_file_writer.Log(&data->list);
	}

	ExitThread(EXIT_SUCCESS);
}