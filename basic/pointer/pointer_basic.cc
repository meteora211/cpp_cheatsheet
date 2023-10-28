#include <iostream>

struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right)
      : val(x), left(left), right(right) {}
};

std::ostream &operator<<(std::ostream &os, const TreeNode &node) {
  os << "node val: " << node.val;
  return os;
}

template <typename T> T *change_ptr(T *ptr) {
  ptr = new T(10);
  return ptr;
}

template <typename T> void print_ptr(T *ptr) {
  std::cout << "ptr addr: " << ptr << " with value: " << *ptr << std::endl;
}

int main() {
  int *ptr1 = new int(42);
  int *ptr2 = ptr1;

  auto *new_ptr = change_ptr(ptr1);

  print_ptr(ptr1);
  print_ptr(ptr2);
  print_ptr(new_ptr);

  delete ptr1;
  delete new_ptr;

  auto *root = new TreeNode(1);
  root->left = new TreeNode(2);
  root->right = new TreeNode(3);

  print_ptr(root->left);
  change_ptr(root->left);
  print_ptr(root->left);
}
