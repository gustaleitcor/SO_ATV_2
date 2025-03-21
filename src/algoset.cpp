#include "algoset.h"
#include <algorithm>
#include <cstddef>
#include <deque>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

std::string ALGO::fifo(std::vector<size_t> pages, size_t frame_size) {
  size_t page_faults = std::min(pages.size(), frame_size);
  std::deque<size_t> frames(pages.begin(),
                            pages.begin() + std::min(pages.size(), frame_size));

  for (size_t i = frame_size; i < pages.size(); i++) {
    if (std::find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
      page_faults++;
      frames.pop_front();
      frames.push_back(pages[i]);
    }
  }

  return "FIFO " + std::to_string(page_faults);
}

std::string ALGO::otm(std::vector<size_t> pages, size_t frame_size) {
  size_t page_faults = std::min(pages.size(), frame_size);
  std::vector<size_t> frames(
      pages.begin(), pages.begin() + std::min(pages.size(), frame_size));

  for (size_t i = frame_size; i < pages.size(); i++) {
    if (std::find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
      page_faults++;
      auto e = std::min_element(
          pages.begin() + i, pages.end(), [&frames](size_t a, size_t b) {
            auto p_a = std::find(frames.begin(), frames.end(), a);
            auto p_b = std::find(frames.begin(), frames.end(), b);

            return std::distance(frames.end(), p_a) >
                   std::distance(frames.end(), p_b);
          });
      *e = pages[i];
    }
  }

  return "OTM " + std::to_string(page_faults);
}

std::string ALGO::lru(std::vector<size_t> pages, size_t frame_size) {
  size_t page_faults = std::min(pages.size(), frame_size);
  std::deque<size_t> frames(pages.begin(),
                            pages.begin() + std::min(pages.size(), frame_size));

  for (size_t i = frame_size; i < pages.size(); i++) {
    auto it = std::find(frames.begin(), frames.end(), pages[i]);
    if (it == frames.end()) {
      page_faults++;
      frames.pop_front();
      frames.push_back(pages[i]);
    } else {
      frames.erase(it);
      frames.push_back(pages[i]);
    }
  }

  return "LRU " + std::to_string(page_faults);
}
