#ifndef BASE_FILE_UTIL_
#define BASE_FILE_UTIL_

#include <stdint.h>
#include <string>
#include <vector>

using std::string;
using std::vector;

namespace FileUtil {
  // Get the size of a file in bytes, if it exists.
  bool FileSize(const string& file_name, uint64_t* file_size);

  // Read the entire file to a string.
  bool FileToString(const string& file_name, string* text);

  // Write the entire string to a file.
  // Overwrites anything that was previously there.
  // Returns false on failure.
  bool StringToFile(const string& text, const string& file_name);

  // List a directory.
  // Returns false on failure.
  bool ListDir(const string& dir_name, vector<string>* names);
}

#endif  // BASE_FILE_UTIL_
