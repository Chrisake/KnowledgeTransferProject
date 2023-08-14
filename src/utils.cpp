#include <stdexcept>
#include <utils.h>

uint32_t utils::reverse(const uint32_t val) {
	uint32_t input = val;
	uint32_t res = 0;
	uint32_t old_res = 0;
	while (input > 0) {
		res = res * 10 + input % 10;
		input /= 10;
		if (old_res > res) {
			// OVF happened
			throw std::invalid_argument(std::format("{} is not reversible", val));
		}
		old_res = res;
	}
	return res;
}

std::string utils::reverse(const std::string& src) {
	std::string res = src;
	uint32_t length = res.size();
	for (int i = 0; i < length / 2; i++) {
		std::swap(res[i], res[length-1-i]);
	}
	return res;
}