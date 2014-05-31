#include <map>
#include "object_store.h"

using std::map;

template <typename Object, typename Id>
Id ObjectStore<Object, Id>::GetOrCreateId(const Object& obj) {
  typename map<Object, Id>::const_iterator it = obj2id_.find(obj);
  if (it == obj2id_.end()) {
    Id t = (Id)obj2id_.size();
    obj2id_[obj] = t;
    objs_.push_back(obj);
    return t;
  } else {
    return obj2id_.find(obj)->second;
  }
}

template <typename Object, typename Id>
bool ObjectStore<Object, Id>::GetId(const Object& obj, Id* id) const {
  typename map<Object, Id>::const_iterator it = obj2id_.find(obj);
  if (it == obj2id_.end()) {
    return false;
  } else {
    *id = it->second;
    return true;
  }
}

template <typename Object, typename Id>
bool ObjectStore<Object, Id>::GetObject(Id id, Object* obj) const {
  if (0 <= id && id < objs_.size()) {
    *obj = objs_[id];
    return true;
  } else {
    return false;
  }
}
