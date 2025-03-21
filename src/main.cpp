#include "algoset.h"

#include <vector>
#include <iostream>

int main() {

  std::vector<size_t> pages = {1, 2, 3, 4, 1, 2, 5, 1, 2, 3, 4, 5};
  std::cout << ALGO::fifo(pages, 3) << std::endl;
  std::cout << ALGO::otm(pages, 3) << std::endl;
  std::cout << ALGO::lru(pages, 3) << std::endl;

  return 0;
}
