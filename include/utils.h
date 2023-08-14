#pragma once
#include <time.h>
#include <chrono>
#include <string>
#include <sstream>
#include <iomanip>

namespace utils
{
   /**
   * @brief    A cross-platform thread-safe implementation of the 
   *           C Standard Libary 'localtime' function.
   * 
   *           Converts the given time since epoch into calendar time.
   * 
   * @param    t [std::time_t] - The timer object representing time elapsed since epoch
   * @return   [std::tm] - The calendar time, expressed as local time
   */
    /*
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
   */

   /**
   * @brief    Returns the current timestamp as a formatted string.         
   * @return   [std::string] - The returned timestamp has the format: "dd-mm-yyyy HH:MM:SS.xxx"
   */
    /*
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
   */
   /**
   * @brief    Reverses the input integer.
   *           Example: 
   *              1. reverse(10)   -> 1
   *              2. reverse(0)    -> 0
   *              3. reverse(191)  -> 191
   * 
   * @param    val [uint32_t] - The number to reverse
   * @return   [uint32_t] - The reversed number
   * @throws   a 'std::domain_error' exception if the reversed 'val' cannot be represented as uint32_t
   */
   uint32_t reverse(const uint32_t val);
   
   /**
   * @brief    Reverses the input string.
   *           Example:
   *              1. reverse("bob")          -> "bob"
   *              2. reverse("book")         -> "koob"
   *              3. reverse("hello world")  -> "dlrow olleh"
   * 
   * @param    src [std::string] - The string to reverse
   * @return   [std::string] - The reversed form of 'src'.
   * @throws   a 'std::invalid_argument' exception if 'src' is an empty string,
               or contains white-space characters only
   */
   std::string reverse(const std::string& src);
}