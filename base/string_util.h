#ifndef BASE_STRING_UTIL_H_
#define BASE_STRING_UTIL_H_

#include <string>
#include <vector>

using std::string;
using std::vector;

class StringUtil {
 public:
  // Split a string |s| into pieces separated by |c| into |v|.
  //
  // Examples:
  //   ("Hello, World\n", ',') -> ["Hello", " World\n"]
  //   ("", 'c') -> [""]
  //   ("c", 'c') -> ["", ""]
  //   ("cc", 'c') -> ["", "", ""]
  static void Split(const string& s, char c, vector<string>* v);

  // Split by whitespace.  Ignore whitespace on either end.
  static void SplitByWhitespace(const string& s, vector<string>* v);

  // atoi/atol equivalent for all integral types.
  // Returns bool success.
  template <typename int_t>
  static bool ToInt(const string& from, int_t* to);

  // atof/atod equivalent for all floating point types.
  // Returns bool success.
  template <typename float_t>
  static bool ToFloat(const string& from, float_t* to);

  // Put text without the comments at end of line if they exist into out.
  static void Decomment(const string& in, const string& comment_mark,
                        string* out);

  // Whether |str| begins with |with|.
  static bool BeginsWith(const string& str, const string& with);

  // Equivalents of printf that work on strings, from gflags source code.
  // Clears output before writing to it.
  inline void SStringPrintf(std::string* output, const char* format, ...);
  inline void StringAppendF(std::string* output, const char* format, ...);
  inline std::string StringPrintf(const char* format, ...);
};

#endif  // BASE_STRING_UTIL_H_
