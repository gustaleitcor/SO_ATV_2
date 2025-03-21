#ifndef ALGO_SET_H
#define ALGO_SET_H

#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>
namespace ALGO {
std::string fifo(std::vector<size_t> pages, size_t frame_size);
std::string otm(std::vector<size_t> pages, size_t frame_size);
std::string lru(std::vector<size_t> pages, size_t frame_size);
}; // namespace ALGO

#endif // ALGO_SET_H
