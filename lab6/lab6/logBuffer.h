#pragma once

#include <mutex>
#include "fstream"
#include "List.h"
#include "LogFileWriter.h"

int MAX_BUFFER_COUNT = 10;

class LogBuffer {
	List list;
	std::mutex g_i_mutex;
	LogFileWriter logFileWriter;

public:
	void log(int value) {
		const std::lock_guard<std::mutex> lock(g_i_mutex);

		int count = list.getCount();
		if (count == MAX_BUFFER_COUNT) {
			logFileWriter.logFile(list);
			list.Clear();
		}
		list.Add(value, nullptr);
	}
};