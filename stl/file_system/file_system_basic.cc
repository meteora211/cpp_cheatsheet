#include <filesystem>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib> // exit failure

namespace fs = std::filesystem;

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cout << "Usage: " << argv[0] << " <path>\n";
    return EXIT_FAILURE;
  }

  {
    // basic
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
  {
    // create folder
    fs::path testDir{"tmp/test"};
    std::cout << testDir.string() << std::endl;
    // XXX: note the difference

    // mkdir tmp/test. Error if tmp is not exists.
    // fs::create_directory(testDir);

    // mkdir -p tmp/test.
    fs::create_directories(testDir);

    // create file
    auto testFile = testDir / "data.txt";
    std::ofstream dataFile{testFile};

    if (!dataFile) {
      std::cerr << "Can't open \"" << testFile.string() << "\"\n";
      std::exit(EXIT_FAILURE);
    }
    dataFile << "The answer is 42.\n";

    // create symbol link
    fs::create_symlink("test", testDir.parent_path() / "slink");

    // delete
    fs::remove(testFile);
    fs::remove_all("tmp");
  }
  {
    // iterate
    std::cout << fs::current_path().string() << "\n";
    auto iterOpts {fs::directory_options::follow_directory_symlink};
    for (const auto& e : fs::recursive_directory_iterator(".", iterOpts)) {
      std::cout << "    " << e.path().lexically_normal().string() << "\n";
    }
  }
}
