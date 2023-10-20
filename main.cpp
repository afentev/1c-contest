#include <iostream>

#include "include/DirectoryAnalyzer.hpp"

int main() {
  std::string filepath1, filepath2;
  float simmilarity_trashhold;
  std::cout << "Enter 1st directory path" << std::endl;
  std::cin >> filepath1;
  std::cout << "Enter 2nd directory path" << std::endl;
  std::cin >> filepath2;
  std::cout << "Enter minimal simmilarity index to consider 2 files different"
               "(value between 0 to 1)" << std::endl;
  std::cin >> simmilarity_trashhold;
  std::cout << "Computing... please wait." << std::endl;
  DirectoryAnalyzer analyzer(filepath1, filepath2);
  analyzer.analyze(simmilarity_trashhold);

  return 0;
}
