#ifndef NAME_STATS_H_
#define NAME_STATS_H_

#include <cstdio>
#include <map>
#include <string>
#include <vector>
#include "base/data_cube.h"
#include "base/object_store.h"

using std::map;
using std::string;
using std::vector;

// -----------------------------------------------------------------------------
// Populations by race at age.
//
// The race information is not useful for name, gender, etc. prediction since we
// don't have info to correlate it with, so we just drop it.

struct PopulationsByRaceAtAge {
  // Age in years, starting at zero.
  unsigned age;

  // Total population at this age of all races.
  unsigned total;

  // Sub-populations by race that together constitute the total pop.
  unsigned white;
  unsigned black;
  unsigned amerind;
  unsigned asian;
  unsigned pacific;
  unsigned two_plus;

  // Separate hispanic-related counts.
  unsigned hispanic;
  unsigned nonhisp_white;

  bool is_valid() const {
    return total == white + black + amerind + asian + pacific + two_plus;
  }
};

bool GetAgeRacePopulationsFromFile(const string& filename,
                                   vector<PopulationsByRaceAtAge>* pops);

bool GetAgeToPop(const string& filename, map<unsigned, unsigned>* age2pop);

// -----------------------------------------------------------------------------
// Info about baby name popularity in a certain year.
//
// Note that these are year-specific, whereas PopulationsByRaceAtAge are
// age-specific.

struct BabyNameEntry {
  string name;
  char gender;
  unsigned count;

  bool is_valid() const {
    if (name.empty()) {
      return false;
    }
    if (gender != 'M' && gender != 'F') {
      return false;
    }
    if (!count) {
      return false;
    }
    return true;
  }

  void Show() const {
    printf("(name=%s gender=%c count=%u)", name.c_str(), gender, count);
  }
};

bool GetBabyNameEntries(const string& dirname,  // Must end with slash.
                        map<unsigned, vector<BabyNameEntry> >* yob2entries);

// -----------------------------------------------------------------------------

enum PresenceStatus {
  // Born here: is on US census birth name tables for that year.  May still be
  // here (see PRESENT_NOW), may have left, may be dead.
  BORN_HERE = 1,

  // Present: is on most recent US census data with an age corresponding to that
  // year.  Born somewhere, usually here (see BORN_HERE).  Usually more people
  // present than born here.
  PRESENT_NOW,
};

class NameStatisticsManager {
 public:
  // Create the internal data cubes from the data.
  bool Init(int current_year,
            const map<unsigned, unsigned>& age2pop,
            const map<unsigned, vector<BabyNameEntry> >& yob2entries);

  // Create internal data cubes from the data from the files.
  // Calls Init().
  bool InitFromFiles(int current_year, const string& age2pop_filename,
                     const string& yob2entries_dirname);

  // Get the number of people with certain attributes.
  bool GetSum(const string& name_or_empty, char gender_or_neg1,
              unsigned yob_or_neg1, PresenceStatus status, float* sum);

  // Get distributions of people with certain attributes.
  //
  // In the following lookups, set gender or yob to ~0, or name to be empty, to
  // match everything instead of a specific value.

  // Get name -> counts of people (with the given gender and birth year).
  bool GetNameCounts(
      char gender_or_neg1, unsigned yob_or_neg1, PresenceStatus status,
      map<string, float>* name2pop, float* sum_pop);

  // Get gender -> counts of people (with the given name and birth year).
  bool GetGenderCounts(
      const string& name_or_empty, unsigned yob_or_neg1, PresenceStatus status,
      map<char, float>* gender2pop, float* sum_pop);

  // Get birth year -> counts of people (with that name and gender).
  bool GetBirthYearCounts(
      const string& name_or_empty, char gender_or_neg1, PresenceStatus status,
      map<uint32_t, float>* yob2pop, float* sum_pop);

 private:
  ObjectStore<string, uint32_t> str_store_;
  DataCube<ThreeTuple<uint32_t>, uint32_t, float> born_cube_;
  DataCube<ThreeTuple<uint32_t>, uint32_t, float> present_cube_;
};

#include "name_stats.cc"

#endif  // NAME_STATS_H_
