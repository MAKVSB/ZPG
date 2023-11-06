#include <vector>

class Utils {
public:
	template <typename T, std::size_t N>
	static std::vector<T> convertToVector(const T(&dataArray)[N]) {
		return std::vector<T>(dataArray, dataArray + N);
	}
};