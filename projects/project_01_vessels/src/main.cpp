#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "backend/algorithms/BTree.hpp"
#include "backend/algorithms/RedBlackTree.hpp"

int main(void) {
  BTree* BTree = new BTree(3);
  for (int64_t i = 0; i < 50; ++i) {
    BTree->insert(i);
    printf("Passed\n");
  }
  printf("\n");
}
