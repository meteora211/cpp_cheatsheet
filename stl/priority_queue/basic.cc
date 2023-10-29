#include <iostream>
#include <queue>
#include <concepts>
#include <string_view>
#include <ranges>
#include <vector>

template <typename T>
void print(std::string_view name, const T& q) {
  std::cout << "iterate " << name << ": \t";
  for (const auto& elem : q) {
    std::cout << elem << " ";
  }
  std::cout << "\n";
}

template <typename Adaptor>
requires (std::ranges::input_range<typename Adaptor::container_type>)
void print(std::string_view name, const Adaptor& adaptor) {
  struct Printer : public Adaptor {
    void print(std::string_view name) const {
      ::print(name, this->c);
    }
  };
  static_cast<Printer const&>(adaptor).print(name);
}

template<typename T>
void loop(std::string_view name, T& q) {
  std::cout << "loop " << name << ": \t";
  while(!q.empty()) {
    std::cout << q.top() << " ";
    q.pop();
  }
  std::cout << "\n";
}

int main() {
  const auto data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
  print("data", data);

  // max priority queue as default
  std::priority_queue<int> max_queue;
  for (int n : data) {
    max_queue.push(n);
  }
  print("max_queue", max_queue);
  loop("max_queue", max_queue);

  // min priority queue
  std::priority_queue<int, std::vector<int>, std::greater<int>> min_queue(data.begin(), data.end());
  print("min_queue", min_queue);
  loop("min_queue", min_queue);

  // pass lambda to queue
  auto lambda = [](int left, int right){ return (left ^ 1) < (right ^ 1);};
  // equalent to:
  // std::priority_queue<int, std::vector<int>, decltype(lambda)> lambda_queue(data.begin(), data.end(), lambda);
  std::priority_queue lambda_queue(data.begin(), data.end(), lambda);
  print("lambda_queue", lambda_queue);
  loop("lambda_queue", lambda_queue);

  // pass callable custom function to queue
  struct Callable {
    bool operator()(int x, int y) {
      return x < y;
    }
  };

  std::priority_queue callable_queue(data.begin(), data.end(), Callable());
  print("callable_queue", callable_queue);
  loop("callable_queue", callable_queue);
}
