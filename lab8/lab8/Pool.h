#pragma once

#include <vector>
#include "Task.h"

class Pool {
public:
	Pool(std::vector<Task*> tasks, int threadCount) {
		tasksCount = tasks.size();

		handles = new HANDLE[tasksCount];
		for (int i = 0; i < tasksCount; i++) {
			handles[i] = CreateThread(NULL, 0, &threadProc, tasks[i], CREATE_SUSPENDED, NULL);
		}
		threadsCount = threadCount;
	}
	void execute() {
		int count = 0;

		for (int i = 0; i < tasksCount; i++) {
			ResumeThread(handles[i]);

			count++;

			if (count == threadsCount) {
				WaitForMultipleObjects(i + 1, handles, true, INFINITE);

				count = 0;
			}
		}

		WaitForMultipleObjects(tasksCount, handles, true, INFINITE);
	}
private:
	HANDLE* handles;
	int tasksCount;
	int threadsCount;
};
