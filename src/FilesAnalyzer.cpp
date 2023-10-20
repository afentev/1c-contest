#include <fstream>
#include <algorithm>
#include <iostream>

#include "FilesAnalyzer.hpp"
#include "HashUtils.hpp"

FilesAnalyzer::FilesAnalyzer(const std::filesystem::path& file1, const std::filesystem::path& file2)
  : file1(file1), file2(file2) {
}

float FilesAnalyzer::analyze() {
  std::ifstream stream1(file1, std::ios_base::in);
  std::ifstream stream2(file2, std::ios_base::in);
  size_t size1 = std::filesystem::file_size(file1);
  size_t size2 = std::filesystem::file_size(file2);

  size_t length = get_longest_common_substring(std::move(stream1),
                                               std::move(stream2),
                                               size1, size2);

  size_t max_length = std::max(size1, size2);
  
  return static_cast<float>(length) / max_length;
}

// this function finds the longset common substring of 2 given strings
// in order to do it binary search over the length of such substring is perfomed
size_t FilesAnalyzer::get_longest_common_substring(std::ifstream&& stream1, std::ifstream&& stream2,
                                                   size_t length1, size_t length2) {
  Hash hasher1(std::move(stream1), length1);
  Hash hasher2(std::move(stream2), length2);

  size_t max_length = std::max(length1, length2);

  ssize_t low_value = 0;
  ssize_t high_value = std::min(length1, length2) + 1;
  while (high_value - low_value > 1) {
    size_t current_length = (high_value + low_value) / 2;
    std::vector<HashHolder> file1_hashes;

    for (size_t substring_start = 0; substring_start + current_length <= length1; ++substring_start) {
      size_t right_index = substring_start + current_length;
      file1_hashes.emplace_back(hasher1(substring_start, right_index, max_length));
    }
    std::sort(file1_hashes.begin(), file1_hashes.end());

    bool substring_found = false;
    for (size_t substring_start = 0; substring_start + current_length <= length2; ++substring_start) {
      size_t right_index = substring_start + current_length;
      HashHolder current_hash = hasher2(substring_start, right_index, max_length);
      if (std::binary_search(file1_hashes.begin(), file1_hashes.end(), current_hash)) {
        // success, we've found the same substring of length current_length

        substring_found = true;
        break;
      }
    }

    if (substring_found) {
      low_value = current_length;
    } else {
      high_value = current_length;
    }
  }
  return low_value;
}