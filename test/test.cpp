#include <gtest/gtest.h>

//#include "loger.h"
#include "utils.h"

namespace utils {

	TEST(ReverseFunction, HandlesUnsignedInts) {
		EXPECT_EQ(reverse(1234), 4321);
		EXPECT_EQ(reverse(12965927), 72956921);
		
	}

	TEST(ReverseFunction, HandlesStrings) {
		EXPECT_EQ(reverse("Hello World"), "dlroW olleH");
		EXPECT_EQ(reverse("abcd"), "dcba");
		EXPECT_EQ(reverse("abcde"), "edcba");
	}

	TEST(ReverseFunction, HandlesEmptyString) {
		EXPECT_EQ(reverse(""), "");
	}

	TEST(ReverseFunction, HandlesZero) {
		EXPECT_EQ(reverse(0), 0);
	}
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
