#include <stdexcept>

#include "utils.h"

namespace utils
{
	std::tm localtime(std::time_t t) {
		{
#ifdef _MSC_VER >= 1400 // MSVCRT (2005+): std::localtime is threadsafe
#pragma warning(suppress : 4996)
			return *std::localtime(&t);
#else // POSIX
			std::tm temp;
			return *::localtime_r(&t, &temp);
#endif // _MSC_VER
		}
	}

	std::string timestamp() {

		using namespace std::literals;
		using system_clock = std::chrono::system_clock;
		using milliseconds = std::chrono::microseconds;

		const auto now = system_clock::now();
		const auto timer = system_clock::to_time_t(now);
		const auto local_time = localtime(timer);

		auto sstream = std::stringstream{};
		sstream << std::put_time(&local_time, "%d-%m-%Y %H:%M:%S");

		//append milliseconds to the timestamp
		auto duration = now.time_since_epoch();
		const auto millisec = std::chrono::duration_cast<milliseconds>(duration) % 1000ms;
		sstream << "." + std::to_string(millisec.count());

		return sstream.str();
	}

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
		size_t length = res.size();
		for (size_t i = 0; i < length / 2; i++) {
			std::swap(res[i], res[length - 0x1 - i]);
		}
		return res;
	}
}