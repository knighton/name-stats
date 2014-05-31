#ifndef BASE_LINE_READER_H_
#define BASE_LINE_READER_H_

#include <string>

using std::string;

#define LINE_READER_READ_SIZE 2048

// Read a file a line at a time.

// Usage:
//   LineReader reader;
//   assert(reader.Open(file_name));
//   string line;
//   while (reader.Next(&line)) {
//     // Do something with line.
//   }

class LineReader {
 public:
  LineReader()
    : cache_index_(0),
      file_(NULL)
  {}
  ~LineReader();

  bool Open(const string& file_name);
  void Close();

  bool Next(string* line);

 private:
  char buffer_[LINE_READER_READ_SIZE];
  string cache_;
  size_t cache_index_;
  FILE* file_;
};

#endif  // BASE_LINE_READER_H_
