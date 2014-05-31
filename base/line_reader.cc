#include <cassert>
#include <cstdio>
#include <string>
#include "line_reader.h"

using std::string;

LineReader::~LineReader() {
  if (file_ != NULL) {
    Close();
  }
}

bool LineReader::Open(const string& file_name) {
  cache_index_ = 0;

  file_ = fopen(file_name.c_str(), "r");
  return file_ != NULL;
}

void LineReader::Close() {
  fclose(file_);
  file_ = NULL;
}

bool LineReader::Next(string* line) {
  assert(file_ != NULL);

  // Keep to reasonable size (trim already-used data off front of buffer).
  if (cache_index_ > 4096) {
    cache_ = cache_.substr(cache_index_, cache_.size() - cache_index_);
    cache_index_ = 0;
  }

  // Load more into cache if necessary.
  size_t nl;
  while (true) {
    // If found newline, done.
    nl = cache_.find('\n', cache_index_);
    if (nl != string::npos) {
      break;
    }

    // If not, load another chunk into cache, then try again (look for newline).
    int nread = fread(buffer_, 1, LINE_READER_READ_SIZE, file_);
    if (nread > 0) {
      cache_ += string(buffer_, nread);
      continue;
    }

    // If read nothing, we have hit EOF.
    nl = cache_.size();
    break;
  }

  if (nl > cache_index_) {
    *line = cache_.substr(cache_index_, nl - cache_index_ + 1);
    cache_index_ = nl + 1;
    return true;
  } else {
    line->clear();
    return false;
  }
}
