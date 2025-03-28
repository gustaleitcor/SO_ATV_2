#include "algoset.h"
#include <algorithm>
#include <cstddef>
#include <deque>
#include <fstream>
#include <iostream>
#include <iterator>
#include <list>
#include <queue>
#include <vector>

std::pair<std::vector<size_t>, size_t>
reader(const std::filesystem::path &file_path) {
  std::ifstream file(file_path);

  if (!file) {
    throw std::runtime_error("ERROR ON FILE OPENING");
  }

  std::vector<size_t> pages;
  size_t page;
  size_t frame_cap;

  file >> frame_cap;

  while (file >> page) {
    pages.push_back(page);
  }

  return {pages, frame_cap};
}

size_t ALGO::fifo(std::vector<size_t> pages, size_t frame_cap) {
  // Inicialização das estruturas
  // page_faults: quantidade de faltas de página, dado pelo mínimo entre a
  // quantidade de páginas e o tamanho da tabela
  // frames: tabela de páginas, inicializada com as primeiras páginas não
  // repetidas
  size_t page_faults = 0;
  size_t off_set = 0;
  std::deque<size_t> frames;
  for (size_t i = 0; i < pages.size() && frames.size() != frame_cap; i++) {
    if (std::find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
      page_faults++;
      frames.push_back(pages[i]);
    } else {
      off_set++;
    }
  }

  if (frames.size() != frame_cap) {
    return page_faults;
  }

  // Iteração sobre as páginas restantes
  for (size_t i = frame_cap + off_set; i < pages.size(); i++) {
    // Se a página não está na tabela, incrementa a quantidade de faltas de
    // página e remove a página mais antiga da tabela do topo e insere a página
    // mais recente no final
    if (std::find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
      page_faults++;
      frames.pop_front();
      frames.push_back(pages[i]);
    }
  }

  // Retorna a quantidade de faltas de página
  return page_faults;
}

size_t ALGO::otm(std::vector<size_t> pages, size_t frame_cap) {
  // Inicialização das estruturas
  // page_faults: quantidade de faltas de página, dado pelo mínimo entre a
  // quantidade de páginas e o tamanho da tabela
  // frames: tabela de páginas, inicializada com as primeiras páginas não
  // repetidas
  size_t page_faults = 0;
  size_t off_set = 0;
  std::vector<size_t> frames;
  for (size_t i = 0; i < pages.size() && frames.size() != frame_cap; i++) {
    if (std::find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
      page_faults++;
      frames.push_back(pages[i]);
    } else {
      off_set++;
    }
  }

  if (frames.size() != frame_cap) {
    return page_faults;
  }

  // Iteração sobre as páginas restantes
  for (size_t i = frame_cap; i < pages.size(); i++) {
    // Se a página não está na tabela, incrementa a quantidade de faltas de
    // página e substitui a página mais distante de ser referenciada
    if (std::find(frames.begin(), frames.end(), pages[i]) == frames.end()) {
      page_faults++;
      // Itera sobre as páginas da tabela e retorna o primeiro encontro da
      // página mais distante de ser referenciada e a substitui pela página
      // atual
      auto e = std::min_element(
          frames.begin(), frames.end(), [&pages, i](size_t a, size_t b) {
            auto p_a = std::find(pages.begin() + i + 1, pages.end(), a);
            auto p_b = std::find(pages.begin() + i + 1, pages.end(), b);

            return std::distance(pages.end(), p_a) >
                   std::distance(pages.end(), p_b);
          });
      *e = pages[i];
    }
  }

  // Retorna a quantidade de faltas de página
  return page_faults;
}

size_t ALGO::lru(std::vector<size_t> pages, size_t frame_cap) {
  // Inicialização das estruturas
  // page_faults: quantidade de faltas de página, dado pelo mínimo entre a
  // quantidade de páginas e o tamanho da tabela
  // frames: tabela de páginas, inicializada com as primeiras páginas não
  // repetidas
  size_t page_faults = 0;
  size_t off_set = 0;
  std::list<size_t> frames;
  for (size_t i = 0; i < pages.size() && frames.size() != frame_cap; i++) {
    if (auto p = std::find(frames.begin(), frames.end(), pages[i]);
        p == frames.end()) {
      page_faults++;
      frames.push_back(pages[i]);
    } else {
      frames.erase(p);
      frames.push_back(pages[i]);
      off_set++;
    }
  }

  if (frames.size() != frame_cap) {
    return page_faults;
  }

  // Iteração sobre as páginas restantes
  for (size_t i = frame_cap + off_set; i < pages.size(); i++) {
    // Se a página não está na tabela, incrementa a quantidade de faltas de
    // página e remove a página mais antiga da tabela do topo e insere a página
    // mais recente no final
    // Se a página está na tabela, remove a página e insere a página no final
    // da tabela
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

  // Retorna a quantidade de faltas de página
  return page_faults;
}
