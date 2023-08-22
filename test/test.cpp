#include <gtest/gtest.h>

#include "logger.h"
#include "utils.h"

namespace utils {

	TEST(ReverseFunction, HandlesUnsignedInts) {
		EXPECT_EQ(reverse(1234), 4321);
		EXPECT_EQ(reverse(12965927), 72956921);
	}

	TEST(ReverseFunction, HandlesTooLargeUInts) {
		try {
			reverse(4294967295);
			FAIL() << "Expected std::invalid_argument";
		}
		catch (std::invalid_argument const& err) {
			EXPECT_EQ(err.what(), std::string("Argument val is not reversible"));
		}
		catch (...) {
			FAIL() << "Expected std::invalid_argument";
		}
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

namespace logging {
	class TestHandler : public LogHandler
	{
	public:
		//cannot be default constructed
		TestHandler() = delete;

		//does not support copy-semantics
		TestHandler(const TestHandler&) = delete;
		TestHandler& operator=(const TestHandler&) = delete;

		//has a non-virtual public destructor; not be used as a base class
		~TestHandler() noexcept = default;

		//offers move semantics
		TestHandler(TestHandler&&) = default;
		TestHandler& operator=(TestHandler&&) = default;

		TestHandler(const HandlerMeta& metadata) : LogHandler(metadata) { totalMessages = 0; }

		//a thread-safe implementation that routes all log messages to a console
		void log(const std::string& message,
			const log_level severity) {
			last_message = message;
			last_severity = severity;
			totalMessages++;
		}

		std::string getLastMessage() { return last_message; }
		log_level getLastSeverity() { return last_severity; }
		uint32_t getTotalMessages() { return totalMessages; }
		void resetCounter() { totalMessages = 0; }

	private:
		std::string last_message = "";
		log_level last_severity = log_level::none;
		uint32_t totalMessages = 0;
	};

	class LoggerTest : public ::testing::Test {
	protected:
		void SetUp() override {
			Logger& logger = Logger::instance();
			logger.add("Test1", std::unique_ptr<LogHandler>(new TestHandler({ "Test1", log_level::none })));
			handler = (TestHandler*) logger.get_handler("Test1").value();
		}

	public:
		TestHandler* handler;
	};

	TEST_F(LoggerTest, HandleNoneLevel) {
		Logger& logger = Logger::instance();
		handler->resetCounter();
		logger.fatal("fatal-None");
		logger.error("error-None");
		logger.warn("warn-None");
		logger.info("info-None");
		logger.debug("debug-None");
		EXPECT_EQ(handler->getTotalMessages(), 0);
	}

	TEST_F(LoggerTest, HandleDebugLevel) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::debug);
		handler->resetCounter();
		logger.fatal("fatal-Debug");
		logger.error("error-Debug");
		logger.warn("warn-Debug");
		logger.info("info-Debug");
		logger.debug("debug-Debug");
		EXPECT_EQ(handler->getTotalMessages(), 5);
	}

	TEST_F(LoggerTest, HandleInfoLevel) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::info);
		handler->resetCounter();
		logger.fatal("fatal-Info");
		logger.error("error-Info");
		logger.warn("warn-Info");
		logger.info("info-Info");
		logger.debug("debug-Info");
		EXPECT_EQ(handler->getTotalMessages(), 4);
	}

	TEST_F(LoggerTest, HandleWarnLevel) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::warning);
		handler->resetCounter();
		logger.fatal("fatal-Warn");
		logger.error("error-Warn");
		logger.warn("warn-Warn");
		logger.info("info-Warn");
		logger.debug("debug-Warn");
		EXPECT_EQ(handler->getTotalMessages(), 3);
	}

	TEST_F(LoggerTest, HandleErrorLevel) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::error);
		handler->resetCounter();
		logger.fatal("fatal-Error");
		logger.error("error-Error");
		logger.warn("warn-Error");
		logger.info("info-Error");
		logger.debug("debug-Error");
		EXPECT_EQ(handler->getTotalMessages(), 2);
	}

	TEST_F(LoggerTest, HandleFatalLevel) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::fatal);
		handler->resetCounter();
		logger.fatal("fatal-Fatal");
		logger.error("error-Fatal");
		logger.warn("warn-Fatal");
		logger.info("info-Fatal");
		logger.debug("debug-Fatal");
		EXPECT_EQ(handler->getTotalMessages(), 1);
	}

	TEST_F(LoggerTest, HandleMultipleHandlers) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::warning);
		handler->resetCounter();
		logger.fatal("fatal-Multi");
		logger.error("error-Multi");
		logger.warn("warn-Multi");
		logger.add("Test2", std::unique_ptr<LogHandler>(new TestHandler({ "Test2", log_level::info })));
		TestHandler* handler2 = (TestHandler*)logger.get_handler("Test2").value();
		logger.info("info-Multi");
		logger.debug("debug-Multi");
		EXPECT_EQ(handler->getTotalMessages(), 3);
		EXPECT_EQ(handler2->getTotalMessages(), 1);
	}

	TEST_F(LoggerTest, HandleSetLevelHandlers) {
		Logger& logger = Logger::instance();
		handler->set_level(log_level::fatal);
		handler->resetCounter();
		logger.fatal("fatal-Multi");
		logger.debug("debug-Multi");
		handler->set_level(log_level::debug);
		logger.error("error-Multi");
		logger.warn("warn-Multi");
		logger.info("info-Multi");
		EXPECT_EQ(handler->getTotalMessages(), 4);
	}
}



int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
