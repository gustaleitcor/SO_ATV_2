#include "algoset.h"

#include <iostream>
#include <stdexcept>
#include <vector>

int main(int argc, char *argv[]) {
  std::vector<std::string_view> args = {argv + 1, argv + argc};

  if (args.size() != 1) {
    std::cerr << "Wrong parameters" << "\n";
    return 1;
  }

  try {
    std::pair<std::vector<size_t>, size_t> instance = reader(args[0]);
    std::cout << "FIFO " << ALGO::fifo(instance.first, instance.second) << '\n';
    std::cout << "OTM " << ALGO::otm(instance.first, instance.second) << '\n';
    std::cout << "LRU " << ALGO::lru(instance.first, instance.second) << '\n';
  } catch (std::runtime_error &error) {
    std::cerr << error.what() << "\n";
    return 1;
  }

  return 0;
}
