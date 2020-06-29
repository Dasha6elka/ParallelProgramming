#pragma once

#include "Bitmap.h"
#include "Task.h"

#undef min
#undef max

constexpr auto M_PI = 3.141592653589793238462643383279502884L;

struct Params {
	bitmap* initBmp;
	bitmap* blurBmp;
	uint32_t startHeight;
	uint32_t endHeight;
	uint32_t startWidth;
	uint32_t endWidth;
};

class Blur: public Task {
public:
	Blur(Params params) {
		this->params = params;
	};
	void execute() override {
		float rs = ceil(5 * 2.57);
 		Params params = this->params;
		int start = params.startHeight;
		int end = params.endHeight;
		for (int i = params.startHeight; i < params.endHeight; ++i)
		{
			for (int j = params.startWidth; j < params.endWidth; ++j)
			{
				double r = 0, g = 0, b = 0;
				double count = 0;

				for (int iy = i - rs; iy < i + rs + 1; ++iy)
				{
					for (int ix = j - rs; ix < j + rs + 1; ++ix)
					{
						auto x = std::min(static_cast<int>(params.endWidth) - 1, std::max(0, ix));
						auto y = std::min(static_cast<int>(params.endHeight) - 1, std::max(0, iy));

						auto dsq = ((ix - j) * (ix - j)) + ((iy - i) * (iy - i));
						auto wght = std::exp(-dsq / (2.0 * 25)) / (M_PI * 2.0 * 25);

						rgb32* pixel = params.initBmp->getPixel(x, y);

						r += pixel->r * wght;
						g += pixel->g * wght;
						b += pixel->b * wght;
						count += wght;
					}
				}

				rgb32* pixel = params.blurBmp->getPixel(j, i);
				pixel->r = std::round(r / count);
				pixel->g = std::round(g / count);
				pixel->b = std::round(b / count);
			}
		}
	};
private:
	Params params;
};
