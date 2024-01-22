#include <filesystem>
#include <iostream>
#include <string>
#include <cstdlib> // exit failure

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  fs::path p{argv[1]};
  if (fs::is_regular_file(p)) {
    std::cout << p << " exits with: " << fs::file_size(p) << " bytes\n";
  } else if (fs::is_directory(p)) {
    std::cout << p << " is directory containing: \n";
    for (const auto& e : fs::directory_iterator{p}) {
      std::cout << "   " << e.path() << std::endl;
    }
  } else if (fs::exists(p)) {
    std::cout << p << " is spectial file.\n";
  } else {
    std::cout << p << " does not exist.\n";
  }
}
