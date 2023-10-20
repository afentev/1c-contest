#ifndef HASHUTILS
#define HASHUTILS

#include <vector>
#include <string>
#include <fstream>

// this data structure stores 2 hashes of the same string
struct HashHolder {
  uint64_t hash1;
  uint64_t hash2;

  // we also need comparison operator, so we can sort these objects
  bool operator< (const HashHolder& other) const {
    if (hash1 < other.hash1) {
      return true;
    } else if (hash1 > other.hash1) {
      return false;
    }
    if (hash2 < other.hash2) {
      return true;
    }
    return false;
  }
};

// this data structure receives a string and computes hash of any substring in O(1)
class Hash {
 public:
  Hash() = delete;
  Hash(std::ifstream&& stream, size_t length);

  // compute hash on substring [left_index, right_index)
  HashHolder operator()(size_t left_index, size_t right_index, size_t max_length) const;

  ~Hash() = default;

 private:
  std::vector<uint64_t> base_powers_mod1, base_powers_mod2;  // powers of base (% mod)
  std::vector<uint64_t> pref_hashes_mod1, pref_hashes_mod2;  // hashes of all prefexies of the given string

  static size_t base;  // base for polynomial hash
  static size_t modulo1, modulo2;  // 2 modulas for hash functions. we use 2 hashes to reduce collisions
};

#endif  // HASHUTILS