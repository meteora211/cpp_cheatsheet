#pragma once
#include <queue>
#include <mutex>

template<typename T>
class BlockingQueue {
public:
  BlockingQueue() = default;
  T front() {
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.front();
  }

  void push(T&& arg) {
    {
      std::unique_lock<std::mutex> lock(mutex_);
      queue_.push(std::forward<T>(arg));
    }
    cv_.notify_one();
  }

  // void pop() {
  //   std::unique_lock<std::mutex> lock(mutex_);
  //   queue_.pop();
  // }

  bool pop(T& elem) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [&]{return !queue_.empty();});
    if (!queue_.empty()) {
      elem = queue_.front();
      queue_.pop();
      return true;
    }
    return false;
  }

  bool empty() {
    std::unique_lock<std::mutex> lock(mutex_);
    return queue_.empty();
  }
  

private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cv_;
};
