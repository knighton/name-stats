#include <cstdio>
#include <stdint.h>
#include <map>
#include "tuples.h"
#include "data_cube.h"

using std::map;

#define BIT_ISSET(var, pos) ((var) & (1 << (pos)))

template <typename KeyTuple, typename Key, typename Sum>
bool DataCube<KeyTuple, Key, Sum>::Init(const Key& star) {
  star_ = star;
  KeyTuple tmp;
  key_values_by_index_.resize(tmp.size());
  return true;
}

template <typename KeyTuple, typename Key, typename Sum>
void DataCube<KeyTuple, Key, Sum>::Show() const {
  printf("%zu\n", sizeof(KeyTuple));
  printf("%zu\n", tuple2sum_.size());
  printf("%zu", key_values_by_index_[0].size());
  for (unsigned i = 1; i < key_values_by_index_.size(); ++i) {
    printf(", %zu", key_values_by_index_[i].size());
  }
  printf("\n");
}

template <typename KeyTuple, typename Key, typename Sum>
bool DataCube<KeyTuple, Key, Sum>::AddEntry(const KeyTuple& orig_tuple,
                                            const Sum& sum) {
  // Initialize the key tuple for setting data, and note key values.
  KeyTuple tuple;
  for (unsigned i = 0; i < orig_tuple.size(); ++i) {
    const Key& value = orig_tuple.values[i];

    // Cannot be the magic value used for 'match everything' lookups.
    if (value == star_) {
      return false;
    }

    // Set value in our local copy for insertions.
    tuple.values[i] = value;

    // Note key value.
    key_values_by_index_[i].insert(value);
  }

  // Walk the powerset for insertion with catchalls.
  for (unsigned i = 0; i < ((unsigned)1 << tuple.size()); ++i) {
    // Set catchall key fields.
    for (unsigned j = 0; j < tuple.size(); ++j) {
      if (BIT_ISSET(i, j)) {
        tuple.values[j] = star_;
      }
    }

    // Add to mapping.
    tuple2sum_[tuple] += sum;

    // Restore the fields.
    for (unsigned j = 0; j < tuple.size(); ++j) {
      if (BIT_ISSET(i, j)) {
        tuple.values[j] = orig_tuple.values[j];
      }
    }
  }

  return true;
}

template <typename KeyTuple, typename Key, typename Sum>
void DataCube<KeyTuple, Key, Sum>::GetSum(const KeyTuple& tuple,
                                          Sum* sum) const {
  typename map<KeyTuple, Sum>::const_iterator it = tuple2sum_.find(tuple);
  if (it == tuple2sum_.end()) {
    *sum = 0;
  } else {
    *sum = it->second;
  }
}

template <typename KeyTuple, typename Key, typename Sum>
bool DataCube<KeyTuple, Key, Sum>::GetDistribution(
    const KeyTuple& tuple, unsigned key_index,
    map<Key, Sum>* key2sum) const {
  // key_index must be an index in the tuple's key values.
  if (!(0 <= key_index && key_index < tuple.size())) {
    return false;
  }

  // The column/key having its distribution being gotten needs to be a catchall
  // (not have a specific value).
  if (tuple.values[key_index] != star_) {
    return false;
  }

  // Get sum for each known value of that field to build the distribution.
  key2sum->clear();
  KeyTuple tmp_tuple = tuple;
  for (typename set<Key>::const_iterator it =
       key_values_by_index_[key_index].begin(); it !=
       key_values_by_index_[key_index].end(); ++it) {
    tmp_tuple.values[key_index] = *it;
    Sum sum;
    GetSum(tmp_tuple, &sum);
    if (0.0 < sum) {
      (*key2sum)[*it] = sum;
    }
  }
  return true;
}
