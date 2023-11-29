#pragma once
#include <vector>

class Utils {
public:
	template <typename T, std::size_t N>
	static std::vector<T> convertToVector(const T(&dataArray)[N]) {
		return std::vector<T>(dataArray, dataArray + N);
	}

	static int intRand(int max = INT_MAX, int min = INT_MIN) {
		return static_cast<int>(rand()) / static_cast<int>(RAND_MAX) * (max - min) + min;
	}

	static float floatRand(float max = FLT_MAX, float min = FLT_MIN) {
		return static_cast<float>(rand()) / static_cast<float>(RAND_MAX) * (max - min) + min;
	}

	static double doubleRand(double max = FLT_MAX, double min = FLT_MIN) {
		return static_cast<double>(rand()) / static_cast<double>(RAND_MAX) * (max - min) + min;
	}
};