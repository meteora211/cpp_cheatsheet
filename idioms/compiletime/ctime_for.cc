#include <iostream>  
#include <utility>  
#include <string>  

// Function template to be called  
template<std::size_t N>  
void template_print(const std::string& message) {  
  std::cout << "compiletime arg: " << N << ", runtime arg: " << message << std::endl;  
}  

// The function receiving the callable  
template<typename Func, std::size_t... Nums, typename... Args>  
void for_loop(Func func, std::index_sequence<Nums...>, Args&&... args) {  
  (func.template operator()<Nums>(std::forward<Args>(args)...), ...);  // Call the function for each index  
}  

int main() {  
  std::string message = "Hello, World!";  
  
  // Create an index_sequence with numbers 0, 1, 2 and pass the message  
  for_loop([]<std::size_t N>(const std::string& msg) { template_print<N>(msg); },   
           std::index_sequence<0, 1, 2>{},   
           message);  

  return 0;  
}  
