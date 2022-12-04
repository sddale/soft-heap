#pragma once
#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <algorithm>
#include <cmath>
#include <memory>

#include "node.hpp"
#include "policies.hpp"
#include "tree.hpp"

namespace soft_heap::test {

template <policy::TotalOrdered Element = int,
          policy::TotalOrderedContainer List = std::vector<Element>,
          int inverse_epsilon>
[[maybe_unused]] static void EXPECT_NODE_EQ(
    const std::unique_ptr<Node<Element, List, inverse_epsilon>>& node,
    const Node<Element, List, inverse_epsilon>& expect) {
  ASSERT_NE(node, nullptr)
      << "\033[1;31mError: Node passed in as nullptr!\033[0m";
  EXPECT_EQ(node->rank, expect.rank);
  EXPECT_EQ(node->size, expect.size);
  EXPECT_EQ(node->elements.size(), expect.elements.size());
  for (auto&& x : expect.elements) {
    EXPECT_FALSE(std::find(node->elements.begin(), node->elements.end(), x) ==
                 node->elements.end())
        << "\033[1;31mCouldn't find element: " << x << "\033[0m";
  }
  EXPECT_EQ(node->ckey, expect.ckey);
}

// [[maybe_unused]] static void EXPECT_TREE_EQ(
//     const TreePtr& tree, const Tree<std::vector, int>& expect) {
//   EXPECT_NODE_EQ(tree->root, expect.root);

//                                             }

}  // namespace soft_heap::test