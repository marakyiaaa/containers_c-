#include "tree.h"

#include <gtest/gtest.h>

TEST(BinaryTreeConstructorsTest, DefaultConstructor) {
  s21::BinaryTree<int> tree;
  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));
}

TEST(BinaryTreeConstructorsTest, CopyConstructor) {
  s21::BinaryTree<int> tree1;
  tree1.insert(10);
  tree1.insert(20);
  tree1.insert(5);

  s21::BinaryTree<int> tree2(tree1);

  EXPECT_FALSE(tree2.empty());
  EXPECT_EQ(tree2.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  auto it1 = tree2.find(10);
  EXPECT_NE(it1, tree2.end());
  EXPECT_EQ(*it1, 10);

  auto it2 = tree2.find(20);
  EXPECT_NE(it2, tree2.end());
  EXPECT_EQ(*it2, 20);

  auto it3 = tree2.find(5);
  EXPECT_NE(it3, tree2.end());
  EXPECT_EQ(*it3, 5);
}

TEST(BinaryTreeConstructorsTest, InitializerListConstructor) {
  s21::BinaryTree<int> tree = {10, 20, 5};

  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  auto it1 = tree.find(10);
  EXPECT_NE(it1, tree.end());
  EXPECT_EQ(*it1, 10);

  auto it2 = tree.find(20);
  EXPECT_NE(it2, tree.end());
  EXPECT_EQ(*it2, 20);

  auto it3 = tree.find(5);
  EXPECT_NE(it3, tree.end());
  EXPECT_EQ(*it3, 5);
}

TEST(BinaryTreeConstructorsTest, MoveConstructor) {
  s21::BinaryTree<int> tree1;
  tree1.insert(10);
  tree1.insert(20);
  tree1.insert(5);

  s21::BinaryTree<int> tree2(std::move(tree1));

  EXPECT_TRUE(tree1.empty());
  EXPECT_FALSE(tree2.empty());
  EXPECT_EQ(tree2.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  auto it1 = tree2.find(10);
  EXPECT_NE(it1, tree2.end());
  EXPECT_EQ(*it1, 10);

  auto it2 = tree2.find(20);
  EXPECT_NE(it2, tree2.end());
  EXPECT_EQ(*it2, 20);

  auto it3 = tree2.find(5);
  EXPECT_NE(it3, tree2.end());
  EXPECT_EQ(*it3, 5);
}

TEST(BinaryTreeConstructorsTest, MoveAssignmentOperator) {
  s21::BinaryTree<int> tree1;
  tree1.insert(10);
  tree1.insert(20);
  tree1.insert(5);

  s21::BinaryTree<int> tree2;
  tree2 = std::move(tree1);

  EXPECT_TRUE(tree1.empty());
  EXPECT_FALSE(tree2.empty());
  EXPECT_EQ(tree2.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  auto it1 = tree2.find(10);
  EXPECT_NE(it1, tree2.end());
  EXPECT_EQ(*it1, 10);

  auto it2 = tree2.find(20);
  EXPECT_NE(it2, tree2.end());
  EXPECT_EQ(*it2, 20);

  auto it3 = tree2.find(5);
  EXPECT_NE(it3, tree2.end());
  EXPECT_EQ(*it3, 5);
}

TEST(BinaryTreeConstructorsTest, CopyAssignmentOperator) {
  s21::BinaryTree<int> tree1;
  tree1.insert(10);
  tree1.insert(20);
  tree1.insert(5);

  s21::BinaryTree<int> tree2;
  tree2 = tree1;

  EXPECT_FALSE(tree2.empty());
  EXPECT_EQ(tree2.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  auto it1 = tree2.find(10);
  EXPECT_NE(it1, tree2.end());
  EXPECT_EQ(*it1, 10);

  auto it2 = tree2.find(20);
  EXPECT_NE(it2, tree2.end());
  EXPECT_EQ(*it2, 20);

  auto it3 = tree2.find(5);
  EXPECT_NE(it3, tree2.end());
  EXPECT_EQ(*it3, 5);
}

TEST(BinaryTreeConstructorsTest, Destructor) {
  s21::BinaryTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(5);

  EXPECT_NO_THROW({ tree.clear(); });
}

TEST(BinaryTreeMethodsTest, Empty) {
  s21::BinaryTree<int> tree;

  EXPECT_TRUE(tree.empty());

  tree.insert(10);
  EXPECT_FALSE(tree.empty());

  tree.clear();
  EXPECT_TRUE(tree.empty());
}

TEST(BinaryTreeMethodsTest, Size) {
  s21::BinaryTree<int> tree;

  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));

  tree.insert(10);
  tree.insert(20);
  tree.insert(5);
  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  tree.clear();
  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));
}

TEST(BinaryTreeMethodsTest, MaxSize) {
  s21::BinaryTree<int> tree;

  EXPECT_GT(tree.max_size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));

  tree.insert(10);
  tree.insert(20);
  tree.insert(5);
  EXPECT_GT(tree.max_size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));

  tree.clear();
  EXPECT_GT(tree.max_size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));
}

TEST(BinaryTreeModifiersTest1, Clear) {
  s21::BinaryTree<int> tree;
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);

  EXPECT_FALSE(tree.empty());
  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  tree.clear();

  EXPECT_TRUE(tree.empty());
  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(0));
}

TEST(BinaryTreeModifiersTest1, Erase) {
  s21::BinaryTree<int> tree;
  auto insert_result1 = tree.insert(10);
  auto insert_result2 = tree.insert(20);
  auto insert_result3 = tree.insert(30);

  (void)insert_result2;
  (void)insert_result3;

  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));

  auto it = insert_result1.first;
  tree.erase(it);

  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(2));
  EXPECT_EQ(tree.find(10), tree.end());
}

TEST(BinaryTreeModifiersTest1, Swap) {
  s21::BinaryTree<int> tree1;
  tree1.insert(10);
  tree1.insert(20);

  s21::BinaryTree<int> tree2;
  tree2.insert(30);
  tree2.insert(40);

  tree1.swap(tree2);

  EXPECT_EQ(tree1.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(2));
  EXPECT_EQ(tree2.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(2));

  EXPECT_EQ(tree1.find(10), tree1.end());
  EXPECT_EQ(tree1.find(20), tree1.end());
  EXPECT_NE(tree1.find(30), tree1.end());
  EXPECT_NE(tree1.find(40), tree1.end());

  EXPECT_EQ(tree2.find(30), tree2.end());
  EXPECT_EQ(tree2.find(40), tree2.end());
  EXPECT_NE(tree2.find(10), tree1.end());
  EXPECT_NE(tree2.find(20), tree1.end());
}

TEST(BinaryTreeModifiersTest1, Merge) {
  s21::BinaryTree<int> tree1;
  tree1.insert(10);
  tree1.insert(20);

  s21::BinaryTree<int> tree2;
  tree2.insert(5);
  tree2.insert(15);

  tree1.merge(tree2);

  EXPECT_EQ(tree1.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(4));
  EXPECT_NE(tree1.find(10), tree1.end());
  EXPECT_NE(tree1.find(20), tree1.end());
  EXPECT_NE(tree1.find(5), tree1.end());
  EXPECT_NE(tree1.find(15), tree1.end());
  EXPECT_TRUE(tree2.empty());
}

TEST(BinaryTreeModifiersTest1, Insert) {
  s21::BinaryTree<int> tree;

  auto result1 = tree.insert(10);
  EXPECT_EQ(*result1.first, 10);
  EXPECT_TRUE(result1.second);

  auto result2 = tree.insert(20);
  EXPECT_EQ(*result2.first, 20);
  EXPECT_TRUE(result2.second);

  auto result3 = tree.insert(30);
  EXPECT_EQ(*result3.first, 30);
  EXPECT_TRUE(result3.second);

  for (auto it : tree) std::cout << it << " \n";

  EXPECT_EQ(tree.size(),
            static_cast<typename s21::BinaryTree<int>::size_type>(3));
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}