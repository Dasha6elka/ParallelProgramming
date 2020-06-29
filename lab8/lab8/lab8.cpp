#include <iostream>
#include <fstream>
#include <algorithm>
#include <windows.h>
#include <string>
#include <vector>
#include "Pool.h"
#include "Blur.h"

#include <filesystem>

namespace fs = std::experimental::filesystem;

#pragma comment(lib, "winmm.lib")

std::vector<Task*> createTasks(bitmap* initBmp, bitmap* blurBmp, int blocksCount) {
	int partWidth = 0, partHeight = 0;
	if (blocksCount != 0) {
		partWidth = initBmp->getWidth() / blocksCount;
		partHeight = initBmp->getHeight() / blocksCount;
	}

	int w = initBmp->getWidth() - partWidth * blocksCount;
	int widthRemaining = std::max(w, 0);
	int h = initBmp->getHeight() - partHeight * blocksCount;
	int heightRemaining = std::max(h, 0);

	std::vector<Task*> tasks;

	for (int i = 0; i < blocksCount; i++) {
		Params params;
		params.initBmp = initBmp;
		params.blurBmp = blurBmp;

		for (int j = 0; j < blocksCount; j++) {
			params.startHeight = partHeight * j;
			params.endHeight = (partHeight * (j + 1)) + (j == blocksCount - 1 ? heightRemaining : 0);
			params.startWidth = i * partWidth;
			params.endWidth = ((i + 1) * partWidth) + (i == blocksCount - 1 ? widthRemaining : 0);
			tasks.push_back(new Blur(params));
		}
	}

	return tasks;
}

void threadsRunner(std::vector<Task*> tasks, HANDLE* handles)
{
	int count = tasks.size();
	for (int i = 0; i < count; i++)
	{
		handles[i] = CreateThread(NULL, i, &threadProc, tasks[i], CREATE_SUSPENDED, NULL);
	}

	for (int i = 0; i < count; i++) {
		ResumeThread(handles[i]);
	}

	WaitForMultipleObjects(count, handles, true, INFINITE);
}

int main(int argc, const char** argv)
{
	std::string mode = argv[1];
	int blocksCount = atoi(argv[2]);
	int threadsCount = atoi(argv[5]);

	int k = 0;

	DWORD start = timeGetTime();

	for (auto &p : fs::directory_iterator(argv[3])) {
		std::string path = p.path().string();
		bitmap initBmp{ path.c_str() };
		bitmap blurBmp{ path.c_str() };

		std::vector<Task*> tasks = createTasks(&initBmp, &blurBmp, blocksCount);

		if (mode == "0") {
			HANDLE* handles = new HANDLE[tasks.size()];
			threadsRunner(tasks, handles);
		}
		else {
			Pool pool(tasks, threadsCount);
			pool.execute();
		}

		std::string s = "\\";
		std::string out = argv[4] + s + std::to_string(k) + ".bmp";

		blurBmp.save(out.c_str());

		k++;
	}

	std::cout << timeGetTime() - start << std::endl;

	return 0;
}
