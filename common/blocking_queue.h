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

  void wait_pop(T& elem) {
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.wait(lock, [&]{return !queue_.empty();});
    elem = std::move(queue_.front());
    queue_.pop();
  }

  bool try_pop(T& elem) {
    std::unique_lock<std::mutex> lock(mutex_);
    if (queue_.empty()) return false;
    elem = std::move(queue_.front());
    queue_.pop();
    return true;
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
