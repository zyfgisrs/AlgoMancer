#include <iostream>
#include <string>

#include "head.hpp"

int main() {
  Tree<int, std::string> tree;
  tree.insert(7, "bar");
  tree.insert(1, "foo");
  tree.insert(2, "bar");
  tree.insert(3, "baz");
  tree.insert(4, "bar");
  tree.insert(5, "baz");
  tree.insert(6, "bar");
  tree.insert(17, "baz");
  tree.insert(8, "foo");
  tree.insert(9, "bar");
  tree.insert(10, "baz");
  tree.insert(11, "bar");
  tree.remove(7);
  if (tree.contains(7)) {
    std::cout << "yes" << std::endl;
  } else {
    std::cout << "no" << std::endl;
  }
}