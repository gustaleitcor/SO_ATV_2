#ifndef ALGO_SET_H
#define ALGO_SET_H

#include <filesystem>
#include <string>
#include <sys/types.h>
#include <utility>
#include <vector>

std::pair<std::vector<size_t>, size_t>
reader(const std::filesystem::path &file_path);

namespace ALGO {
std::string fifo(std::vector<size_t> pages, size_t frame_size);
std::string otm(std::vector<size_t> pages, size_t frame_size);
std::string lru(std::vector<size_t> pages, size_t frame_size);
}; // namespace ALGO

#endif // ALGO_SET_H
