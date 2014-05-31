#include <cassert>
#include <iostream>
#include <string>
#include <vector>

#include "string_util.h"

using namespace std;

void TestSplit() {
  string s = "";
  char c = 'c';
  vector<string> v;
  StringUtil::Split(s, c, &v);
  assert(v.size() == 1);
  assert(v[0] == "");

  s = "c";
  StringUtil::Split(s, c, &v);
  assert(v.size() == 2);
  assert(v[0] == "");
  assert(v[1] == "");

  s = "cc";
  StringUtil::Split(s, c, &v);
  assert(v.size() == 3);
  assert(v[0] == "");
  assert(v[1] == "");
  assert(v[2] == "");

  s = "    what the   fuck   ";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 3);
  assert(v[0] == "what");
  assert(v[1] == "the");
  assert(v[2] == "fuck");
}

void TestDecomment() {
  string s = "# hi";
  string s2;
  StringUtil::Decomment(s, "#", &s2);
  assert(s2 == "");

  s = "         # hot";
  StringUtil::Decomment(s, "#", &s2);
  assert(s2 == "         ");

  s = "  what # nice";
  StringUtil::Decomment(s, "#", &s2);
  assert(s2 == "  what ");
}

void TestSplitByWhitespace() {
  vector<string> v;

  string s = "a";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 1);
  assert(v[0] == "a");

  s = " abba ";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 1);
  assert(v[0] == "abba");

  s = "who are ";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 2);
  assert(v[0] == "who");
  assert(v[1] == "are");

  s = "\ttight  kites\nmight&nbsp;   ";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 3);
  assert(v[0] == "tight");
  assert(v[1] == "kites");
  assert(v[2] == "might&nbsp;");

  s = "\n\t\t\ta\t[            \n";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 2);
  assert(v[0] == "a");
  assert(v[1] == "[");

  s = " 0 1 2\n";
  StringUtil::SplitByWhitespace(s, &v);
  assert(v.size() == 3);
  assert(v[0] == "0");
  assert(v[1] == "1");
  assert(v[2] == "2");
}

int main() {
  TestSplit();
  TestDecomment();
  TestSplitByWhitespace();
}
