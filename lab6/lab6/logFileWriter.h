#include <windows.h>
#include <stdio.h>
#include "fstream"
#include "List.h"

HANDLE ghWriteEvent;
HANDLE ghThreads[1];
DWORD WINAPI LogSizeMonitoringThread(LPVOID);

struct Data {
	List list;
	std::ofstream* file;
};

class LogFileWriter {

public: 
	void logFile(List list, std::ofstream* file) {
		HANDLE* handles = new HANDLE[1];

		Data data;
		data.list = list;
		data.file = file;

		handles[0] = CreateThread(NULL, 0, &LogSizeMonitoringThread, &data, CREATE_SUSPENDED, NULL);

		ResumeThread(handles[0]);

		WaitForMultipleObjects(1, handles, true, INFINITE);
	}
};

DWORD WINAPI LogSizeMonitoringThread(CONST LPVOID lpParam)
{
	struct Data* data = (struct Data*)lpParam;

	Node* last = data->list.getLast();
	while (last != nullptr) {
		List list = data->list;
		int value = list.getValue(last);
		*data->file << value << std::endl;
		last = data->list.Prev(last);
	}

	ExitThread(0);
}