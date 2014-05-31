#ifndef BASE_OBJECT_STORE_H_
#define BASE_OBJECT_STORE_H_

#include <map>
#include <string>
#include <vector>

using std::map;
using std::string;
using std::vector;

template <typename Object, typename Id>
class ObjectStore {
 public:
  Id GetOrCreateId(const Object& obj);
  bool GetId(const Object& obj, Id* id) const;
  bool GetObject(Id t, Object* s) const;
 private:
  map<Object, Id> obj2id_;
  vector<Object> objs_;
};

#endif  // BASE_OBJECT_STORE_H_
