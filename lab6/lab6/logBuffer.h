#include <mutex>
#include "fstream"
#include "List.h"
#include "LogFileWriter.h"

int MAX_BUFFER_COUNT = 10;

class LogBuffer {
	List list;
	std::mutex g_i_mutex;
public:
	void log(int value) {
		const std::lock_guard<std::mutex> lock(g_i_mutex);

		if (list.getCount() < MAX_BUFFER_COUNT) {
			list.Add(value);
		}
		else {
			LogFileWriter logFileWriter;
			logFileWriter.logFile(list);
			list.Clear();
		}
	}
};