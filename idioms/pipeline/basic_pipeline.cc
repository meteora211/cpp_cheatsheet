#include "blocking_queue.h"
#include <vector>
#include <iostream>
#include <thread>
#include <memory>
#include <mutex>

void preprocess(int input, std::shared_ptr<BlockingQueue<int>> input_queue) {
  std::cout << "preprocess" << std::endl;
  input_queue->push(input * 2);
}

void execute(std::shared_ptr<BlockingQueue<int>> input_queue,
             std::shared_ptr<BlockingQueue<int>> output_queue) {
  std::cout << "execute" << std::endl;
  int input;
  input_queue->pop(input);
  output_queue->push(input + 2);
}

void postprocess(std::shared_ptr<BlockingQueue<int>> output_queue) {
  std::cout << "postprocess" << std::endl;

}

int main() {
  auto input_queue = std::make_shared<BlockingQueue<int>>();
  auto output_queue = std::make_shared<BlockingQueue<int>>();

  // auto preproces_thread = std::thread(preprocess);
  // auto execute_thread = std::thread(execute);
  // auto postprocess_thread = std::thread(postprocess);
}
