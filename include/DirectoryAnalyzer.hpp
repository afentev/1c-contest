#ifndef DIRECTORYANALYZER
#define DIRECTORYANALYZER

#include <string>
#include <filesystem>

class DirectoryAnalyzer {
 public:
  DirectoryAnalyzer() = delete;
  DirectoryAnalyzer(const std::string& filepath1, const std::string& filepath2);

  void analyze(float simmilarity_trashhold) const;

  ~DirectoryAnalyzer() = default;

 private:
  // inernal datastructure that stores 2 files and metainfo about them
  struct PairOfFiles;

  void check_existance(const std::string& filepath1, const std::string& filepath2);
  void check_isdir(const std::string& filepath1, const std::string& filepath2);
  void check_correctness(const std::string& filepath1, const std::string& filepath2);

  std::filesystem::path path1, path2;
};

#endif  // DIRECTORYANALYZER