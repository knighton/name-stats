#include <dirent.h>
#include <cassert>
#include <cstdio>
#include <string>
#include "file_util.h"

bool FileUtil::FileSize(const string& file_name, uint64_t* file_size) {
  FILE *f = fopen(file_name.c_str(), "rb");
  if (f == NULL) {
    return false;
  }

  fseek(f, 0, SEEK_END);
  *file_size = ftell(f);
  fclose(f);
  return true;
}

bool FileUtil::FileToString(const string& file_name, string* text) {
  uint64_t file_size;
  if (!FileUtil::FileSize(file_name, &file_size)) {
    return false;
  }

  char* buf = new char[file_size];
  if (buf == NULL) {
    return false;
  }

  FILE *f = fopen(file_name.c_str(), "rb");
  if (f == NULL) {
    return false;
  }

  if (fread(buf, sizeof(*buf), file_size, f) != file_size) {
    delete buf;
    fclose(f);
    return false;
  }

  text->assign(buf, file_size);
  delete buf;
  fclose(f);
  return true;
}

bool FileUtil::StringToFile(const string& text, const string& file_name) {
  FILE* f = fopen(file_name.c_str(), "wb");
  if (!f) {
    return false;
  }

  if (fwrite(text.data(), 1, text.size(), f) != text.size()) {
    return false;
  }

  fclose(f);
  return true;
}

bool FileUtil::ListDir(const string& dir_name, vector<string>* names) {
  DIR* dir = opendir(dir_name.c_str());
  if (dir) {
    dirent* ent;
    while ((ent = readdir(dir))) {
      names->push_back(ent->d_name);
    }
    closedir(dir);
    return true;
  } else {
    return false;
  }
}
