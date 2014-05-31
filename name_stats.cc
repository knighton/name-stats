#include <map>
#include <string>
#include <vector>
#include "base/file_util.h"
#include "base/line_reader.h"
#include "base/string_util.h"

using std::map;
using std::string;
using std::vector;

// -----------------------------------------------------------------------------
// Populations by race at age.

#define FLATTEN_PLUS_TO 5

void SplitCountsInto(unsigned split_into, bool is_last,
                     PopulationsByRaceAtAge* stat) {
  stat->total /= split_into;
  stat->white /= split_into;
  stat->black /= split_into;
  stat->amerind /= split_into;
  stat->asian /= split_into;
  stat->pacific /= split_into;
  stat->two_plus /= split_into;
  stat->hispanic /= split_into;
  stat->nonhisp_white /= split_into;

  // If is_last, it gets the remainder after int division.
  if (is_last) {
    stat->total += stat->total % split_into;
    stat->white += stat->white % split_into;
    stat->black += stat->black % split_into;
    stat->amerind += stat->amerind % split_into;
    stat->asian += stat->asian % split_into;
    stat->pacific += stat->pacific % split_into;
    stat->two_plus += stat->two_plus % split_into;
    stat->hispanic += stat->hispanic % split_into;
    stat->nonhisp_white += stat->nonhisp_white % split_into;
  }
}

bool SetRestOfStat(const vector<string>& ss, PopulationsByRaceAtAge* stat) {
  if (!StringUtil::ToInt(ss[1], &(stat->total))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[2], &(stat->white))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[3], &(stat->black))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[4], &(stat->amerind))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[5], &(stat->asian))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[6], &(stat->pacific))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[6], &(stat->two_plus))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[6], &(stat->hispanic))) {
    return false;
  }
  if (!StringUtil::ToInt(ss[6], &(stat->nonhisp_white))) {
    return false;
  }

  // The counts are in thousands.
  stat->total *= 1000;
  stat->white *= 1000;
  stat->black *= 1000;
  stat->amerind *= 1000;
  stat->asian *= 1000;
  stat->pacific *= 1000;
  stat->two_plus *= 1000;
  stat->hispanic *= 1000;
  stat->nonhisp_white *= 1000;

  return true;
}

bool AppendSplitCounts(unsigned age, unsigned split_into,
                       const vector<string>& ss,
                       vector<PopulationsByRaceAtAge>* pop_stats,
                       bool is_last) {
  size_t n = pop_stats->size();
  pop_stats->resize(n + 1);
  PopulationsByRaceAtAge* stat = &(*pop_stats)[n];
  stat->age = age;
  if (!SetRestOfStat(ss, stat)) {
    return false;
  }
  SplitCountsInto(split_into, is_last, stat);
  return true;
}

bool HandlePlus(unsigned age_plus, const vector<string>& ss,
                vector<PopulationsByRaceAtAge>* pop_stats) {
  for (unsigned i = 0; i < FLATTEN_PLUS_TO; ++i) {
    unsigned split_into = FLATTEN_PLUS_TO;  // Flat.
    bool is_last = FLATTEN_PLUS_TO - 1;
    if (!AppendSplitCounts(age_plus + i, split_into, ss, pop_stats, is_last)) {
      return false;
    }
  }
  return true;
}

bool HandleRange(unsigned from_age, unsigned to_age,
                 const vector<string>& ss,
                 vector<PopulationsByRaceAtAge>* pop_stats) {
  for (unsigned i = 0; i < to_age - from_age + 1; ++i) {
    unsigned split_into = to_age - from_age + 1;  // Flat.
    bool is_last = to_age - from_age;
    if (!AppendSplitCounts(from_age + i, split_into, ss, pop_stats, is_last)) {
      return false;
    }
  }
  return true;
}

bool HandleInt(unsigned age, const vector<string>& ss,
               vector<PopulationsByRaceAtAge>* pop_stats) {
  size_t n = pop_stats->size();
  pop_stats->resize(n + 1);
  PopulationsByRaceAtAge* stat = &(*pop_stats)[n];
  stat->age = age;
  return SetRestOfStat(ss, stat);
}

bool GetAgeRacePopulationsFromFile(
    const string& filename, vector<PopulationsByRaceAtAge>* pop_stats) {
  LineReader in;
  if (!in.Open(filename)) {
    return false;
  }

  string line;
  while (in.Next(&line)) {
    int n = line.find('#');
    if (n != -1) {
      line = line.substr(0, n);
    }

    if (!line.size()) {
      continue;
    }

    vector<string> ss;
    StringUtil::SplitByWhitespace(line, &ss);
    if (ss.size() != 10) {
      return false;
    }

    const string& s = ss[0];
    if (s.empty()) {
      return false;
    }
    if (s[s.size() - 1] == '+') {  // "101+".
      unsigned n;
      if (!StringUtil::ToInt(s.substr(0, s.size() - 1), &n)) {
        return false;
      }
      if (!HandlePlus(n, ss, pop_stats)) {
        return false;
      }
    } else {
      unsigned n = s.find('-');
      if (1 <= n && n <= s.size() - 1) {  // "85-59".
        unsigned a;
        if (!StringUtil::ToInt(s.substr(0, n), &a)) {
          return false;
        }
        unsigned b;
        if (!StringUtil::ToInt(s.substr(n + 1), &b)) {
          return false;
        }
        if (!HandleRange(a, b, ss, pop_stats)) {
          return false;
        }
      } else {  // "84".
        unsigned n;
        if (!StringUtil::ToInt(s, &n)) {
          return false;
        }
        if (!HandleInt(n, ss, pop_stats)) {
          return false;
        }
      }
    }
  }
  return true;
}

bool GetAgeToPop(const string& filename, map<unsigned, unsigned>* age2pop) {
  vector<PopulationsByRaceAtAge> pop_stats;
  if (!GetAgeRacePopulationsFromFile(filename, &pop_stats)) {
    return false;
  }
  age2pop->clear();
  for (unsigned i = 0; i < pop_stats.size(); ++i) {
    const PopulationsByRaceAtAge& stat = pop_stats[i];
    if (age2pop->find(stat.age) != age2pop->end()) {
      return false;
    }
    (*age2pop)[stat.age] = stat.total;
  }
  return true;
}

// -----------------------------------------------------------------------------
// Baby name popularity.

bool LoadBabyNameFile(const string& filename, vector<BabyNameEntry>* entries) {
  entries->clear();
  LineReader reader;
  if (!reader.Open(filename)) {
    return false;
  }
  string line;
  while (reader.Next(&line)) {
    line.erase(line.find_last_not_of(" \n\r\t") + 1);
    vector<string> ss;
    StringUtil::Split(line, ',', &ss);
    if (ss.size() != 3) {
      return false;
    }
    size_t n = entries->size();
    entries->resize(n + 1);
    BabyNameEntry* entry = &(*entries)[n];
    entry->name = ss[0];
    if (ss[1].size() != 1) {
      return false;
    }
    entry->gender = ss[1][0];
    if (!StringUtil::ToInt(ss[2], &(entry->count))) {
      return false;
    }
    if (!entry->is_valid()) {
      return false;
    }
  }
  return true;
}

bool GetBabyNameEntries(const string& dirname,
                        map<unsigned, vector<BabyNameEntry> >* yob2entries) {
  if (!dirname.size() || dirname[dirname.size() - 1] != '/') {
    return false;
  }

  vector<string> names;
  FileUtil::ListDir(dirname, &names);
  vector<string> todos;
  for (unsigned i = 0; i < names.size(); ++i) {
    const string& s = names[i];
    if (7 < s.size() &&
        s.substr(0, 3) == "yob" &&
        s.substr(s.size() - 4) == ".txt") {
      todos.push_back(s);
    }
  }

  yob2entries->clear();
  for (unsigned i = 0; i < todos.size(); ++i) {
    const string& s = todos[i];
    string filename = dirname + s;
    unsigned yob;
    if (!StringUtil::ToInt(s.substr(3, s.size() - 4 - 3), &yob)) {
      return false;
    }

    vector<BabyNameEntry> ee;
    (*yob2entries)[yob] = ee;
    if (!LoadBabyNameFile(filename, &((*yob2entries)[yob]))) {
      return false;
    }
  }
  return true;
}

// -----------------------------------------------------------------------------
// Name statistics manager.

bool NameStatisticsManager::Init(
    int current_year,
    const map<unsigned, unsigned>& age2pop,
    const map<unsigned, vector<BabyNameEntry> >& yob2entries) {
  // Create the 'born then' data cube.
  printf("NameStatisticsManager::Init\n");
  printf("Building the \"born\" cube...\n");
  born_cube_.Init(~0);
  unsigned entries = 0;
  for (map<unsigned, vector<BabyNameEntry> >::const_iterator it =
       yob2entries.begin(); it != yob2entries.end(); ++it) {
    ThreeTuple<uint32_t> tuple;
    const unsigned& year = it->first;
    tuple.values[2] = year;
    for (unsigned i = 0; i < it->second.size(); ++i) {
      const BabyNameEntry& e = (it->second)[i];
      if (e.name.empty()) {
        return false;
      }
      uint32_t name_id = str_store_.GetOrCreateId(e.name);
      tuple.values[0] = name_id;
      tuple.values[1] = e.gender;
      float sum = e.count;
      ++entries;
      if (!born_cube_.AddEntry(tuple, sum)) {
        return false;
      }
    }
  }

/*
  printf("added %u entries:\n", entries);
  born_cube_.Show();
  {
    ThreeTuple<uint32_t> all = MakeTuple<uint32_t>(~0, ~0, ~0);
    float sum;
    born_cube_.GetSum(all, &sum);
    printf("sum of all: %f\n", sum);
  }
*/

  // Create the 'present now' data cube.
  printf("Building the \"present\" cube...\n");
  present_cube_.Init(~0);
  for (map<unsigned, vector<BabyNameEntry> >::const_iterator it =
       yob2entries.begin(); it != yob2entries.end(); ++it) {
    const unsigned& yob = it->first;
    const vector<BabyNameEntry>& entries = it->second;
    ThreeTuple<uint32_t> tuple;
    tuple.values[2] = yob;

    // Get how many people were born in that year.
    unsigned sum_present = 0;
    for (unsigned i = 0; i < entries.size(); ++i) {
      sum_present += entries[i].count;
    }

    // Get how many people are present of that age.
    unsigned int age = current_year - yob;
    map<unsigned, unsigned>::const_iterator jt = age2pop.find(age);
    float pct_present = 0.0;
    if (jt != age2pop.end()) {
      pct_present = (float)sum_present / jt->second;
    }

    // Multiply birth name counts by percent present to make 'present now' map.
    for (unsigned i = 0; i < entries.size(); ++i) {
      const BabyNameEntry& e = entries[i];
      if (e.name.empty()) {
        return false;
      }
      uint32_t name_id = str_store_.GetOrCreateId(e.name);
      tuple.values[0] = name_id;
      tuple.values[1] = e.gender;
      float sum = e.count * pct_present;
      if (!present_cube_.AddEntry(tuple, sum)) {
        return false;
      }
    }
  }

/*
  printf("Done with present cube:\n");
  present_cube_.Show();
*/

  printf("Done with Init.\n");
  return true;
}

bool NameStatisticsManager::InitFromFiles(
    int current_year, const string& age2pop_filename,
    const string& yob2entries_dirname) {
  // Load data from files.
  map<unsigned, unsigned> age2pop;
  if (!GetAgeToPop(age2pop_filename, &age2pop)) {
    return false;
  }

  map<unsigned, vector<BabyNameEntry> > yob2entries;
  if (!GetBabyNameEntries(yob2entries_dirname, &yob2entries)) {
    return false;
  }

  // Call Init with data.
  return Init(current_year, age2pop, yob2entries);
}

bool NameStatisticsManager::GetSum(
    const string& name_or_empty, char gender_or_neg1, unsigned yob_or_neg1,
    PresenceStatus status, float* sum) {
  if (!(gender_or_neg1 == 'M' || gender_or_neg1 == 'F' ||
        gender_or_neg1 == ~0)) {
    return false;
  }

  unsigned name_id = ~0;
  if (!name_or_empty.empty()) {
    name_id = str_store_.GetOrCreateId(name_or_empty);
  }

  ThreeTuple<uint32_t> tuple;
  tuple.values[0] = name_id;
  tuple.values[1] = gender_or_neg1;
  tuple.values[2] = yob_or_neg1;

  if (status == BORN_HERE) {
    born_cube_.GetSum(tuple, sum);
  } else if (status == PRESENT_NOW) {
    present_cube_.GetSum(tuple, sum);
  } else {
    return false;
  }

  return true;
}

bool NameStatisticsManager::GetNameCounts(
    char gender, unsigned yob, PresenceStatus status,
    map<string, float>* name2pop, float* sum_pop) {
  ThreeTuple<uint32_t> tuple;
  tuple.values[0] = ~0;
  tuple.values[1] = gender;
  tuple.values[2] = yob;

  map<uint32_t, float> int2pop;
  if (status == BORN_HERE) {
    if (!born_cube_.GetDistribution(tuple, 0, &int2pop)) {
      return false;
    }
  } else if (status == PRESENT_NOW) {
    if (!present_cube_.GetDistribution(tuple, 0, &int2pop)) {
      return false;
    }
  } else {
    return false;
  }

  *sum_pop = 0.0;
  for (map<uint32_t, float>::const_iterator it = int2pop.begin();
       it != int2pop.end(); it++) {
    string name;
    if (!str_store_.GetObject(it->first, &name)) {
      return false;
    }
    float pop = it->second;
    (*name2pop)[name] = pop;
    *sum_pop += pop;
  }
  return true;
}

bool NameStatisticsManager::GetGenderCounts(
    const string& name, unsigned yob, PresenceStatus status,
    map<char, float>* gender2pop, float* sum_pop) {
  ThreeTuple<uint32_t> tuple;
  uint32_t name_id = ~0;
  if (!name.empty()) {
    name_id = str_store_.GetOrCreateId(name);
  }
  tuple.values[0] = name_id;
  tuple.values[1] = ~0;
  tuple.values[2] = yob;

  // Get the internal data distribution.
  map<uint32_t, float> int2pop;
  if (status == BORN_HERE) {
    if (!born_cube_.GetDistribution(tuple, 1, &int2pop)) {
      return false;
    }
  } else if (status == PRESENT_NOW) {
    if (!present_cube_.GetDistribution(tuple, 1, &int2pop)) {
      return false;
    }
  } else {
    return false;
  }

  // Convert gender uint32_t to gender char.
  *sum_pop = 0.0;
  for (map<uint32_t, float>::const_iterator it = int2pop.begin();
       it != int2pop.end(); it++) {
    char gender = it->first;
    float pop = it->second;
    (*gender2pop)[gender] = pop;
    *sum_pop += pop;
  }
  return true;
}

bool NameStatisticsManager::GetBirthYearCounts(
    const string& name, char gender, PresenceStatus status,
    map<uint32_t, float>* yob2pop, float* sum_pop) {
  ThreeTuple<uint32_t> tuple;
  uint32_t name_id = ~0;
  if (!name.empty()) {
    name_id = str_store_.GetOrCreateId(name);
  }
  tuple.values[0] = name_id;
  tuple.values[1] = gender;
  tuple.values[2] = ~0;
  if (status == BORN_HERE) {
    if (!born_cube_.GetDistribution(tuple, 2, yob2pop)) {
      return false;
    }
  } else if (status == PRESENT_NOW) {
    if (!present_cube_.GetDistribution(tuple, 2, yob2pop)) {
      return false;
    }
  } else {
    return false;
  }

  *sum_pop = 0.0;
  for (map<uint32_t, float>::const_iterator it = yob2pop->begin();
       it != yob2pop->end(); ++it) {
    *sum_pop += it->second;
  }
  return true;
}
