#pragma once

#include "fstream"
#include "List.h"
#include "LogFileWriter.h"

class LogBuffer {
	List list;
	LogFileWriter logFileWriter;

public:
	void log(int, std::ofstream*);
};