#ifndef BASE_TUPLES_H_
#define BASE_TUPLES_H_

#include <cstddef>  // For size_t.

// =============================================================================
// 1-tuples.

template <typename T>
struct OneTuple {
  T values[1];

  size_t size() const { return 1; }

  void Init(T v0) {
    values[0] = v0;
  }

  int compare(const OneTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const OneTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const OneTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const OneTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const OneTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const OneTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
OneTuple<T> MakeTuple(T v0) {
  OneTuple<T> tuple;
  tuple.Init(v0);
  return tuple;
}

// =============================================================================
// 2-tuples.

template <typename T>
struct TwoTuple {
  T values[2];

  size_t size() const { return 2; }

  void Init(T v0, T v1) {
    values[0] = v0;
    values[1] = v1;
  }

  int compare(const TwoTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const TwoTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const TwoTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const TwoTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const TwoTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const TwoTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
TwoTuple<T> MakeTuple(T v0, T v1) {
  TwoTuple<T> tuple;
  tuple.Init(v0, v1);
  return tuple;
}

// =============================================================================
// 3-tuples.

template <typename T>
struct ThreeTuple {
  T values[3];

  size_t size() const { return 3; }

  void Init(T v0, T v1, T v2) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
  }

  int compare(const ThreeTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const ThreeTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const ThreeTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const ThreeTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const ThreeTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const ThreeTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
ThreeTuple<T> MakeTuple(T v0, T v1, T v2) {
  ThreeTuple<T> tuple;
  tuple.Init(v0, v1, v2);
  return tuple;
}

// =============================================================================
// 4-tuples.

template <typename T>
struct FourTuple {
  T values[4];

  size_t size() const { return 4; }

  void Init(T v0, T v1, T v2, T v3) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
  }

  int compare(const FourTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const FourTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const FourTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const FourTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const FourTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const FourTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
FourTuple<T> MakeTuple(T v0, T v1, T v2, T v3) {
  FourTuple<T> tuple;
  tuple.Init(v0, v1, v2, v3);
  return tuple;
}

// =============================================================================
// 5-tuples.

template <typename T>
struct FiveTuple {
  T values[5];

  size_t size() const { return 5; }

  void Init(T v0, T v1, T v2, T v3, T v4) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
    values[4] = v4;
  }

  int compare(const FiveTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const FiveTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const FiveTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const FiveTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const FiveTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const FiveTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
FiveTuple<T> MakeTuple(T v0, T v1, T v2, T v3, T v4) {
  FiveTuple<T> tuple;
  tuple.Init(v0, v1, v2, v3, v4);
  return tuple;
}

// =============================================================================
// 6-tuples.

template <typename T>
struct SixTuple {
  T values[6];

  size_t size() const { return 6; }

  void Init(T v0, T v1, T v2, T v3, T v4, T v5) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
    values[4] = v4;
    values[5] = v5;
  }

  int compare(const SixTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const SixTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const SixTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const SixTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const SixTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const SixTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
SixTuple<T> MakeTuple(T v0, T v1, T v2, T v3, T v4, T v5) {
  SixTuple<T> tuple;
  tuple.Init(v0, v1, v2, v3, v4, v5);
  return tuple;
}

// =============================================================================
// 7-tuples.

template <typename T>
struct SevenTuple {
  T values[7];

  size_t size() const { return 7; }

  void Init(T v0, T v1, T v2, T v3, T v4, T v5, T v6) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
    values[4] = v4;
    values[5] = v5;
    values[6] = v6;
  }

  int compare(const SevenTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const SevenTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const SevenTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const SevenTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const SevenTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const SevenTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
SevenTuple<T> MakeTuple(T v0, T v1, T v2, T v3, T v4, T v5, T v6) {
  SevenTuple<T> tuple;
  tuple.Init(v0, v1, v2, v3, v4, v5, v6);
  return tuple;
}

// =============================================================================
// 8-tuples.

template <typename T>
struct EightTuple {
  T values[8];

  size_t size() const { return 8; }

  void Init(T v0, T v1, T v2, T v3, T v4, T v5, T v6, T v7) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
    values[4] = v4;
    values[5] = v5;
    values[6] = v6;
    values[7] = v7;
  }

  int compare(const EightTuple& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const EightTuple& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const EightTuple& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const EightTuple& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const EightTuple& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const EightTuple& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
EightTuple<T> MakeTuple(T v0, T v1, T v2, T v3, T v4, T v5, T v6, T v7) {
  EightTuple<T> tuple;
  tuple.Init(v0, v1, v2, v3, v4, v5, v6, v7);
  return tuple;
}

// =============================================================================
// 17-tuples.

/*
template <typename T>
struct Tuple17 {
  T values[17];

  size_t size() const { return 17; }

  void Init(T v0, T v1, T v2, T v3, T v4, T v5, T v6, T v7, T v8, T v9, T v10,
            T v11, T v12, T v13, T v14, T v15, T v16) {
    values[0] = v0;
    values[1] = v1;
    values[2] = v2;
    values[3] = v3;
    values[4] = v4;
    values[5] = v5;
    values[6] = v6;
    values[7] = v7;
    values[8] = v8;
    values[9] = v9;
    values[10] = v10;
    values[11] = v11;
    values[12] = v12;
    values[13] = v13;
    values[14] = v14;
    values[15] = v15;
    values[16] = v16;
  }

  int compare(const Tuple17& rhs) const {
    for (unsigned i = 0; i < size(); ++i) {
      if (values[i] < rhs.values[i]) {
        return -1;
      } else if (values[i] > rhs.values[i]) {
        return +1;
      }
    }
    return 0;
  }

  bool operator<(const Tuple17& rhs) const { return compare(rhs) < 0; }
  bool operator<=(const Tuple17& rhs) const { return compare(rhs) <= 0; }
  bool operator==(const Tuple17& rhs) const { return compare(rhs) == 0; }
  bool operator>=(const Tuple17& rhs) const { return compare(rhs) >= 0; }
  bool operator>(const Tuple17& rhs) const { return compare(rhs) > 0; }
};

template <typename T>
Tuple17<T> MakeTuple(T v0, T v1, T v2, T v3, T v4, T v5, T v6, T v7) {
  Tuple17<T> tuple;
  tuple.Init(v0, v1, v2, v3, v4, v5, v6, v7);
  return tuple;
}
*/

#endif  // BASE_TUPLES_H_
