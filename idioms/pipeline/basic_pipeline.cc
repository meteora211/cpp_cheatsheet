#include "blocking_queue.h"
#include <vector>
#include <iostream>
#include <thread>
#include <memory>
#include <mutex>

void preprocess(const std::vector<int>& inputs, std::shared_ptr<BlockingQueue<int>> input_queue) {
  std::cout << "preprocess" << std::endl;
  for(auto&& input : inputs) {
    input_queue->push(input * 2);
  }
}

void execute(std::shared_ptr<BlockingQueue<int>> input_queue,
             std::shared_ptr<BlockingQueue<int>> output_queue) {
  static std::mutex local_mutex;
  std::cout << "execute" << std::endl;
  {
    std::scoped_lock lock(local_mutex);
    int input;
    while(input_queue->try_pop(input)) {
      output_queue->push(input + 2);
    }
  }
}

void postprocess(std::vector<int>& outputs, std::shared_ptr<BlockingQueue<int>> output_queue) {
  static std::mutex local_mutex;
  std::cout << "postprocess" << std::endl;
  {
    std::scoped_lock lock(local_mutex);
    int output;
    while(output_queue->try_pop(output)) {
      std::cout << "output: " << output << std::endl;
      outputs.push_back(output);
    }
  }
}

int main() {
  auto input_queue = std::make_shared<BlockingQueue<int>>();
  auto output_queue = std::make_shared<BlockingQueue<int>>();

  std::vector<int> inputs{1, 2, 3, 4, 5};
  std::vector<int> outputs;
  auto preproces_thread = std::thread(preprocess, std::ref(inputs), input_queue);
  auto execute_thread = std::thread(execute, input_queue, output_queue);
  auto postprocess_thread = std::thread(postprocess, std::ref(outputs), output_queue);

  preproces_thread.join();
  execute_thread.join();
  postprocess_thread.join();
}
