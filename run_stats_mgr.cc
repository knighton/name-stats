#include <cassert>
#include <gflags/gflags.h>
#include "name_stats.h"

DEFINE_string(age2pop_filename, "data/pop_by_age.dat",
              "local path of age2pop data file.");

DEFINE_string(yob_dirname, "data/us_names/",
              "local path of yob2entries data dir.");

DEFINE_int32(current_year, 2012, "");

int main(int argc, char* argv[]) {
  gflags::ParseCommandLineFlags(&argc, &argv, true);

  map<unsigned, unsigned> age2pop;
  assert(GetAgeToPop(FLAGS_age2pop_filename, &age2pop));

  map<unsigned, vector<BabyNameEntry> > yob2entries;
  assert(GetBabyNameEntries(FLAGS_yob_dirname, &yob2entries));

  NameStatisticsManager name_stats_mgr;
  assert(name_stats_mgr.Init(FLAGS_current_year, age2pop, yob2entries));

  map<char, float> gender2freq;
  float sum_freq;
  assert(name_stats_mgr.GetGenderCounts(
      "James", 1986, BORN_HERE, &gender2freq, &sum_freq));
  printf("sum: %f\n", sum_freq);
  for (map<char, float>::const_iterator it = gender2freq.begin();
       it != gender2freq.end(); ++it) {
    printf("%c %f\n", it->first, it->second);
  }
}
