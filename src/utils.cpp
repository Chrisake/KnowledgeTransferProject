#include <stdexcept>
#include <utils.h>
#include <string>

namespace utils
{
	uint32_t reverse(const uint32_t val) {
		uint32_t input = val;
		uint32_t res = 0;
		uint32_t old_res = 0;
		while (input > 0) {
			res = res * 10 + input % 10;
			input /= 10;
			if (old_res > res/10) {
				throw std::invalid_argument(std::to_string(val) + " is not reversible");
				return UINT32_MAX;
			}
			old_res = res;
		}
		return res;
	}

	std::string reverse(const std::string& src) {
		std::string res = src;
		uint32_t length = res.size();
		for (int i = 0; i < length / 2; i++) {
			std::swap(res[i], res[length - 0x1 - i]);
		}
		return res;
	}
}