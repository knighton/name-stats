#include <cstdarg>  // For va_*.
#include <cstdio>  // For vsprintf.
#include <string>
#include <vector>
#include "string_util.h"

using std::string;
using std::vector;

void StringUtil::Split(const string& s, char c, vector<string>* v) {
  v->clear();
  int prev_c = 0;
  for (unsigned i = 0; i < s.size(); ++i) {
    if (s[i] == c) {
      v->push_back(s.substr(prev_c, i - prev_c));
      prev_c = i + 1;
    }
  }
  v->push_back(s.substr(prev_c, s.size() - prev_c));
}

void StringUtil::SplitByWhitespace(const string& s, vector<string>* v) {
  v->clear();
  size_t last_nonspace_i = ~0;
  for (unsigned i = 0; i < s.size(); ++i) {
    char c = s[i];
    if (isspace(c)) {
      if (last_nonspace_i != (size_t)~0) {
        v->push_back(s.substr(last_nonspace_i, i - last_nonspace_i));
        last_nonspace_i = ~0;
      }
    } else {
      if (last_nonspace_i == (size_t)~0) {
        last_nonspace_i = i;
      }
    }
  }
  if (last_nonspace_i != (size_t)~0) {
    v->push_back(s.substr(last_nonspace_i));
  }
}

template <typename int_t>
bool StringUtil::ToInt(const string& from, int_t* to) {
  if (from.empty()) {
    return false;
  }

  *to = 0;
  bool positive = true;

  unsigned i = 0;

  if (from[i] == '-') {
    positive = false;
    ++i;
  }

  if (i == from.size()) {
    return false;
  }

  for (; i < from.size(); ++i) {
    if (from[i] < '0' || '9' < from[i]) {
      return false;
    } else {
      *to *= 10;
      *to += from[i] - '0';
    }
  }

  if (!positive) {
    *to *= -1;
  }

  return true;
}

template <typename float_t>
bool StringUtil::ToFloat(const string& from, float_t* to) {
  if (from.empty()) {
    return false;
  }

  *to = 0;
  bool positive = true;

  int i = 0;

  if (from[i] == '-') {
    positive = false;
    ++i;
  }

  if (i == from.size()) {
    return false;
  }

  for (; i < from.size(); ++i) {
    char c = from[i];
    if (c == '.') {
      break;
    } else if (c < '0' || '9' < c) {
      return false;
    } else {
      *to *= 10;
      *to += c - '0';
    }
  }

  if (from[i] == '.') {
    i += 1;
    float_t power = 1.0;

    for (; i < from.size(); ++i) {
      char c = from[i];
      if (c < '0' || '9' < c) {
        return false;
      } else {
        power /= 10;
        *to += (c - '0') * power;
      }
    }
  }

  if (!positive) {
    *to *= -1;
  }

  return true;
}

void StringUtil::Decomment(const string& in, const string& comment_mark,
                           string* out) {
  for (unsigned i = 0; i < in.size() - comment_mark.size(); ++i) {
    for (unsigned j = 0; j < comment_mark.size(); ++j) {
      if (in[i + j] != comment_mark[j]) {
        goto fail;
      }
    }
    *out = in.substr(0, i);
    return;
fail:
    ;
  }
  *out = in;
}

#define _MIN(A, B) ((A) < (B) ? (A) : (B))

bool StringUtil::BeginsWith(const string& str, const string& with) {
  unsigned z = _MIN(str.size(), with.size());
  return str.substr(0, z) == with.substr(0, z);
}

inline void InternalStringPrintf(string* output, const char* format,
                                 va_list ap) {
  char space[128];    // try a small buffer and hope it fits

  // It's possible for methods that use a va_list to invalidate
  // the data in it upon use.  The fix is to make a copy
  // of the structure before using it and use that copy instead.
  va_list backup_ap;
  va_copy(backup_ap, ap);
  unsigned bytes_written = vsnprintf(space, sizeof(space), format, backup_ap);
  va_end(backup_ap);

  if ((bytes_written >= 0) && (bytes_written < sizeof(space))) {
    output->append(space, bytes_written);
    return;
  }

  // Repeatedly increase buffer size until it fits.
  unsigned length = sizeof(space);
  while (true) {
    if (bytes_written < 0) {
      // Older snprintf() behavior. :-(  Just try doubling the buffer size
      length *= 2;
    } else {
      // We need exactly "bytes_written+1" characters
      length = bytes_written+1;
    }
    char* buf = new char[length];

    // Restore the va_list before we use it again
    va_copy(backup_ap, ap);
    bytes_written = vsnprintf(buf, length, format, backup_ap);
    va_end(backup_ap);

    if ((bytes_written >= 0) && (bytes_written < length)) {
      output->append(buf, bytes_written);
      delete[] buf;
      return;
    }
    delete[] buf;
  }
}

inline void StringUtil::SStringPrintf(string* output, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  output->clear();
  InternalStringPrintf(output, format, ap);
  va_end(ap);
}

inline void StringUtil::StringAppendF(string* output, const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  InternalStringPrintf(output, format, ap);
  va_end(ap);
}

inline string StringUtil::StringPrintf(const char* format, ...) {
  va_list ap;
  va_start(ap, format);
  string output;
  InternalStringPrintf(&output, format, ap);
  va_end(ap);
  return output;
}
