#pragma once

#include <fstream>

#include "LinkedList.h"

class LogFileWriter {
private:
	std::ofstream output{"output.txt"};

public:
	void Log(LinkedList* list) {
		while (list->Count() > 0) {
			output << list->Pop() << std::endl;
		}
	}
};