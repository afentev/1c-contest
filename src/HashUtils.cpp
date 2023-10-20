#include "HashUtils.hpp"

#include <random>
#include <iostream>

Hash::Hash(std::ifstream&& stream, size_t length)
    : base_powers_mod1(length + 1, 0), base_powers_mod2(length + 1, 0),
      pref_hashes_mod1(length + 1, 0), pref_hashes_mod2(length + 1, 0) {
  // calculating powers of base
  base_powers_mod1[0] = base_powers_mod2[0] = 1;
  for (size_t i = 1; i <= length; ++i) {
    base_powers_mod1[i] = (base_powers_mod1[i - 1] * base) % modulo1;
    base_powers_mod2[i] = (base_powers_mod2[i - 1] * base) % modulo2;
  }

  // calculating prefexies hashes
  for (size_t i = 0; i < length; ++i) {
    char symbol;
    stream >> symbol;
    size_t hash = (pref_hashes_mod1[i] + static_cast<size_t>(symbol) * base_powers_mod1[i]) % modulo1;
    pref_hashes_mod1[i + 1] = hash;
    hash = (pref_hashes_mod2[i] + static_cast<size_t>(symbol) * base_powers_mod2[i]) % modulo2;
    pref_hashes_mod2[i + 1] = hash;
  }
}

HashHolder Hash::operator()(size_t left_index, size_t right_index, size_t max_length) const {
  uint64_t hash1 = pref_hashes_mod1[right_index] - pref_hashes_mod1[left_index];
  uint64_t hash2 = pref_hashes_mod2[right_index] - pref_hashes_mod2[left_index];
  if (hash1 < 0) {
    hash1 += modulo1;
  }
  if (hash2 < 0) {
    hash2 += modulo2;
  }
  hash1 = 1LL * hash1 * base_powers_mod1[max_length - right_index] % modulo1;
  hash2 = 1LL * hash2 * base_powers_mod2[max_length - right_index] % modulo2;

  return {hash1, hash2};
}

// // generating base for polynomial hash
//   auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
//   std::mt19937 mt_rand(seed);
//   base = std::uniform_int_distribution<int>(1024, std::max(modulo1, modulo2))(mt_rand);
//   if (base % 2 == 0) {
//     --base;
//   }

// 2 classic modulos for polynomial hashes
constexpr size_t MODULO1 = 1'000'000'123;
constexpr size_t MODULO2 = 1'000'000'007;
constexpr size_t BASE    =   123'456'789;  // any big odd random number < mod is fine

size_t Hash::modulo1 = MODULO1;
size_t Hash::modulo2 = MODULO2;
size_t Hash::base = BASE;