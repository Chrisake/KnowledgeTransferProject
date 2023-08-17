#include "utils.h"
#include <iostream>
#include "logger.h"


int main() {
	std::cout << "version: " << __cplusplus << "\n";
	std::cout << utils::reverse(1234) << "\n";
	std::cout << utils::reverse(235617) << "\n";
	std::cout << utils::reverse(5849648) << "\n";
	std::cout << utils::reverse(19838419) << "\n";
	std::cout << utils::reverse("Hello World") << "\n";
	std::cout << utils::reverse("abcdEFGhijkLMNOP") << "\n";
	return 0;
}