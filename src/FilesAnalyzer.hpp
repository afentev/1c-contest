#ifndef FILESANALYZER
#define FILESANALYZER

#include <filesystem>

// Class that recieves 2 correct path objects and provides
// their analytics. It does no checks, therefore
// it is unsafe and not included in "include" dir
class FilesAnalyzer {
 public:
  FilesAnalyzer() = delete;
  FilesAnalyzer(const std::filesystem::path& file1, const std::filesystem::path& file2);

  float analyze();

  ~FilesAnalyzer() = default;

 private:
  static size_t get_longest_common_substring(std::ifstream&& stream1, std::ifstream&& stream2,
                                             size_t length1, size_t length2);

  std::filesystem::path file1, file2;
};

#endif  // FILESANALYZER