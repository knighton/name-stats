#ifndef BASE_DATA_CUBE_H_
#define BASE_DATA_CUBE_H_

#include <stdint.h>
#include <map>
#include <set>
#include <vector>
#include "tuples.h"

using std::map;
using std::set;
using std::vector;

template <typename KeyTuple, typename Key, typename Sum>
class DataCube {
 public:
  bool Init(const Key& star);
  void Show() const;

  bool AddEntry(const KeyTuple& tuple, const Sum& sum);

  void GetSum(const KeyTuple& tuple, Sum* sum) const;
  bool GetDistribution(const KeyTuple& tuple, unsigned key_index,
                       map<Key, Sum>* key2sum) const;
 private:
  map<KeyTuple, Sum> tuple2sum_;
  Key star_;
  vector<set<Key> > key_values_by_index_;
};

#endif  // BASE_DATA_CUBE_H_
