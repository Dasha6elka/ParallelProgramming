#include "List.h"
#include "fstream"
#include <mutex>

int MAX_BUFFER_COUNT = 10;

class LogBuffer {
	List list;
	std::mutex g_i_mutex;
	std::ofstream file{"output.txt"};
public:
	void log(int value) {
		const std::lock_guard<std::mutex> lock(g_i_mutex);

		if (list.getCount() < MAX_BUFFER_COUNT) {
			list.Add(value);
		}
		else {
			Node* first = list.getFirst();
			while (first != nullptr) {
				file << list.getValue(first);
				first = list.Next(first);
			}
			list.Clear();
		}
	}
};