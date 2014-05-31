#include "fcntl.h"
#include <cassert>
#include "file_util.h"

const string kTestFile = "file_test_tmp";

void TestFile() {
  const string in = "one\ntwo";
  string out;
  uint64_t sz = 1337;

  assert(!FileUtil::FileSize(kTestFile, &sz));
  assert(sz == 1337);
  assert(!FileUtil::FileToString(kTestFile, &out));
  assert(out == "");

  FileUtil::StringToFile(in, kTestFile);
  assert(FileUtil::FileToString(kTestFile, &out));
  assert(out == in);
  assert(FileUtil::FileSize(kTestFile, &sz));
  assert(sz == in.size());

  unlink(kTestFile.c_str());
  assert(!FileUtil::FileSize(kTestFile, &sz));
}

int main() {
  TestFile();
}
