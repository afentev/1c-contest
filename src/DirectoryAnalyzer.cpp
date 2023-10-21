#include <filesystem>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>

#include "../include/DirectoryAnalyzer.hpp"
#include "FilesAnalyzer.hpp"

// inernal datastructure that stores 2 files and metainfo about them
struct DirectoryAnalyzer::PairOfFiles {
  std::filesystem::path path1;
  std::filesystem::path file1;
  std::filesystem::path path2;
  std::filesystem::path file2;
  float simmilarity;
};

DirectoryAnalyzer::DirectoryAnalyzer(const std::string& filepath1, const std::string& filepath2)
  : path1(filepath1), path2(filepath2) {
    check_correctness(filepath1, filepath2);
}

void DirectoryAnalyzer::analyze(float simmilarity_trashhold) const {
  std::vector<PairOfFiles> identical;
  std::vector<PairOfFiles> simmilar;
  std::set<std::filesystem::path> different_first;
  std::set<std::filesystem::path> different_second;
  for (const auto& file1: std::filesystem::directory_iterator(path1)) {
    for (const auto& file2: std::filesystem::directory_iterator(path2)) {
      FilesAnalyzer filesAnalyzer(file1, file2);
      float simmilarity = filesAnalyzer.analyze();
      if (simmilarity < simmilarity_trashhold) {
        different_first.insert(file1);
        different_second.insert(file2);
      } else if (simmilarity < 1) {
        simmilar.emplace_back(PairOfFiles{path1, file1, path2,
                                          file2, simmilarity});
      } else {
        identical.emplace_back(PairOfFiles{path1, file1, path2,
                                           file2, simmilarity});
      }
    }
  }
  std::cout << "The following files are identical:" << "\n";
  for (const auto& filepair: identical) {
    different_first.erase(filepair.file1);
    different_second.erase(filepair.file2);
    std::cout << filepair.file1.c_str() << " - ";
    std::cout << filepair.file2.c_str() << "\n";
  }

  std::cout << "The following files are simmilar:" << "\n";
  for (const auto& filepair: simmilar) {
    different_first.erase(filepair.file1);
    different_second.erase(filepair.file2);
    std::cout << filepair.file1.c_str() << " - ";
    std::cout << filepair.file2.c_str();
    std::cout << " " << filepair.simmilarity * 100 << "% \n";
  }

  std::cout << "The following files are presented only in the first directory:" << "\n";
  for (const auto& file: different_first) {
    std::cout << file.filename().c_str() << "\n";
  }

  std::cout << "The following files are presented only in the second directory:" << "\n";
  for (const auto& file: different_second) {
    std::cout << file.filename().c_str() << "\n";
  }

  std::cout << std::endl;
}

void DirectoryAnalyzer::check_correctness(const std::string& filepath1, const std::string& filepath2) {
  check_existance(filepath1, filepath2);
  check_isdir(filepath1, filepath2);
}

void DirectoryAnalyzer::check_existance(const std::string& filepath1, const std::string& filepath2) {
  if (!std::filesystem::exists(path1)) {
    throw std::logic_error("Given path #1 \"" + filepath1 + "\" is incorrect.");
  }
  if (!std::filesystem::exists(path2)) {
    throw std::logic_error("Given path #2 \"" + filepath2 + "\" is incorrect.");
  }
}

void DirectoryAnalyzer::check_isdir(const std::string& filepath1, const std::string& filepath2) {
  if (!std::filesystem::is_directory(path1)) {
    throw std::logic_error("Given path \"" + filepath1 + "\" is not a directory.");
  }
  if (!std::filesystem::is_directory(path2)) {
    throw std::logic_error("Given path \"" + filepath2 + "\" is not a directory.");
  }
}
