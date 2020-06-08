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
	std::ofstream file{ "output.txt" };

public: 
	void logFile(List list) {
		HANDLE* handles = new HANDLE[1];

		Data data;
		data.list = list;
		data.file = &file;

		handles[0] = CreateThread(NULL, 0, &ThreadProc, &data, CREATE_SUSPENDED, NULL);

		ResumeThread(handles[0]);

		WaitForMultipleObjects(1, handles, true, INFINITE);
	}
};

DWORD WINAPI ThreadProc(CONST LPVOID lpParam)
{
	struct Data* data = (struct Data*)lpParam;

	Node* first = data->list.getFirst();
	while (first != nullptr) {
		*data->file << "Stream number " << *((int*)data->list.getValue(first)) << " doing his job" << std::endl;
		first = data->list.Next(first);
	}

	ExitThread(0); // функция устанавливает код завершения потока в 0
}