#include <windows.h>
#include <stdio.h>

#include "logFileWriter.h"

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