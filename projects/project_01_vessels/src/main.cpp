#include <cstdint>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "backend/algorithms/BTree.hpp"
#include "backend/algorithms/RedBlackTree.hpp"

int main(void) {
  bTree* tree1 = new bTree(5);
  redBlackTree* tree2 = new redBlackTree();

  size_t insertInteractionsBTree = tree1->insert(10);
  insertInteractionsBTree += tree1->insert(31);
  insertInteractionsBTree += tree1->insert(67);
  printf("Insert Interactions BTree: %zu\n", insertInteractionsBTree);

  size_t searchInteractionsBTree = tree1->search(10);
  searchInteractionsBTree += tree1->search(31);
  insertInteractionsBTree += tree1->search(67);
  printf("Search Interactions Btree: %zu\n", searchInteractionsBTree);

  size_t deleteInteractionsBTree = tree1->remove(10);
  deleteInteractionsBTree += tree1->remove(31);
  insertInteractionsBTree += tree1->remove(67);
  printf("Delete Interactions Btree: %zu\n\n", deleteInteractionsBTree);

  size_t insertInteractionsRedBlackTree = tree2->insert(30);
  insertInteractionsRedBlackTree += tree2->insert(44);
  insertInteractionsRedBlackTree += tree2->insert(25);
  printf("Insert Interactions Red Black Tree: %zu\n",
    insertInteractionsRedBlackTree);

  size_t searchInteractionsRedBlackTree = tree2->search(30);
  searchInteractionsRedBlackTree += tree2->search(44);
  insertInteractionsRedBlackTree += tree2->search(25);
  printf("Search Interactions Red Black Tree: %zu\n",
    searchInteractionsRedBlackTree);

  size_t deleteInteractionsRedBlackTree = tree2->remove(30);
  deleteInteractionsRedBlackTree += tree2->remove(44);
  insertInteractionsRedBlackTree += tree2->remove(25);
  printf("Delete Interactions Red Black Tree: %zu\n\n",
    deleteInteractionsRedBlackTree);

  return EXIT_SUCCESS;
}
