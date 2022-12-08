#include "selection_algorithm.hpp"
#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace selection_algorithm;

// TODO soft-heap based min-heap selection algorithm
auto soft_heap_selection(std::input_iterator auto first,
                         std::input_iterator auto last) noexcept -> std::vector<int> {
  return std::vector<int>{};
};

// TODO
auto standard_heap_selection(std::input_iterator auto first,
                             std::input_iterator auto last, const size_t k) noexcept -> std::vector<int> {
      std::vector<int> k_elements;
      std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;
      min_heap.emplace(&first);

      while (k_elements.size() < k) {
        int min_elem = min_heap.top();
        min_heap.pop();
        k_elements.push_back(min_elem);

        auto min_elem_index = std::find(first, last, min_elem);

        if ((min_elem_index * 2 + 1) < last) {
          min_heap.emplace(first + (min_elem_index * 2 + 1));
        }

        if ((min_elem_index * 2 + 2) < last) {
          min_heap.emplace(first + (min_elem_index * 2 + 2));
        }
      }

  return k_elements;
};

auto selection_algorithm::standard_heap_selection(
    const std::vector<int>& input_heap, const size_t k) noexcept
    -> std::vector<int> {
      std::vector<int> k_elements;
      // std::priority_queue<int, std::vector<int>, std::greater<>> min_heap;
      std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<>> min_heap;
      min_heap.emplace(std::make_pair(input_heap.front(), 0));

      while (k_elements.size() < k) {
        // int min_elem = min_heap.top();
        int min_elem, min_elem_index;
        std::tie(min_elem, min_elem_index) = min_heap.top();
        min_heap.pop();
        k_elements.push_back(min_elem);

        // TODO: make more efficient?
        // auto min_elem_index = std::find(input_heap.begin(), input_heap.end(), min_elem) - input_heap.begin();

        if ((min_elem_index * 2 + 1) < std::ssize(input_heap)) {
          // min_heap.emplace(input_heap.at(min_elem_index * 2 + 1));
          min_heap.emplace(std::make_pair(input_heap.at(min_elem_index * 2 + 1),min_elem_index * 2 + 1));
        }

        if ((min_elem_index * 2 + 2) < std::ssize(input_heap)) {
          // min_heap.emplace(input_heap.at(min_elem_index * 2 + 2));
          min_heap.emplace(std::make_pair(input_heap.at(min_elem_index * 2 + 2),min_elem_index * 2 + 2));
        }
      }

  return k_elements;
};

// note: changes input to be a heap
auto selection_algorithm::standard_heap_selection_vector(
    std::vector<int>& input, const size_t k) noexcept
    -> std::vector<int> {
      std::make_heap(input.begin(), input.end(), std::greater<>{});
      return standard_heap_selection(input, k);
    }

auto selection_algorithm::soft_heap_selection(
    const std::priority_queue<int, std::vector<int>, std::greater<>>& input_heap, const size_t k) noexcept
    -> std::vector<int> {
  return std::vector<int>{};
};