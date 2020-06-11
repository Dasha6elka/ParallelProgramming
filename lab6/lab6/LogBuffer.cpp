#include "logBuffer.h";

int MAX_BUFFER_COUNT = 10;

void LogBuffer::log(int value, std::ofstream* file) {
	int count = list.getCount();
	if (count == MAX_BUFFER_COUNT) {
		logFileWriter.logFile(list, file);
		list.Clear();
	}

	list.Add(value, nullptr);
}