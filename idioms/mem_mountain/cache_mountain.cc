#include <chrono>
#include <iostream>
#include <vector>
using namespace std;
using namespace std::chrono;

constexpr int kb = 1024;
constexpr int mb = 1024 * 1024;
constexpr int max_stride = 64;

void access_mem(vector<double>& data, int elems, int stride) {
  double result;
  volatile double sink;
  for (int i = 0; i < elems; i += stride) {
    result += data[i];
  }
  sink = result;
}

void init_data(vector<double>& data) {
  for (int i = 0; i < data.size(); ++i) data[i] = i;
}

void execute(vector<double>& data, int elems) {
  // warm up
  access_mem(data, elems, 1);
  auto start = high_resolution_clock::now();
  for (int time = 0; time < 10; ++time) {
    for (int stride = 1; stride < max_stride; ++stride) {
      access_mem(data, elems, stride);
    }
  }
  auto end = high_resolution_clock::now();
  auto duration = duration_cast<nanoseconds>(end - start);
  std::cout << "size: " << elems * sizeof(double) / kb << " kb. time: " << duration.count() / 10 << "." << std::endl;
}

int main() {

  const int min_size = 1 * kb;
  const int max_size = 128 * mb;
  vector<double> data(max_size / sizeof(double), 0);
  init_data(data);

  for (int size = min_size; size < max_size; size <<= 1) {
    execute(data, size / sizeof(double));
  }
}
