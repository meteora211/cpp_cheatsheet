#pragma once
#include <iostream>
#include <string>
#include <memory>
#include <atomic>

template<typename T>
class RingBuffer {
public:
  RingBuffer(size_t capacity, std::string name) : capacity_(capacity), slot_(std::make_unique<T[]>(capacity_)) {}
  ~RingBuffer();
  RingBuffer(const RingBuffer& rhs) = delete;
  RingBuffer(RingBuffer&& rhs) = delete;
  RingBuffer& operator=(const RingBuffer& rhs) = delete;
  RingBuffer& operator=(RingBuffer&& rhs) = delete;

  void put();
  void get();

private:
  const size_t capacity_;
  const string name_;
  std::unique_ptr<T[]> slot_;
};
