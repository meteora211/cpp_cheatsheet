#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <memory_resource>

#include "TrackNew.h"

int main() {
  {
    TrackNew::reset();

    std::vector<std::string> coll;
    for (int i = 0; i < 1000; ++i) {
      coll.emplace_back("just a non-sso string");
    }

    TrackNew::status();
  }
  {
    TrackNew::reset();

    std::array<std::byte, 200000> buf;

    std::pmr::monotonic_buffer_resource pool(buf.data(), buf.size());
    std::pmr::vector<std::string> coll {&pool};

    for (int i = 0; i < 1000; ++i) {
      coll.emplace_back("just a non-sso string");
    }

    TrackNew::status();
  }
  {
    TrackNew::reset();

    std::array<std::byte, 200000> buf;

    std::pmr::monotonic_buffer_resource pool(buf.data(), buf.size());
    // XXX: use pmr::string
    std::pmr::vector<std::pmr::string> coll {&pool};

    for (int i = 0; i < 1000; ++i) {
      coll.emplace_back("just a non-sso string");
    }

    TrackNew::status();
  }
}
