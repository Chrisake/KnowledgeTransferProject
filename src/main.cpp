#include "utils.h"
#include "logger.h"
#include <iostream>

int main() {
	uint32_t result = utils::reverse(1234);
	std::cout << result << "\n";
	
	return 0;
}