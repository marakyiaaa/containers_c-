#include <gtest/gtest.h>

#include "s21_set.h"

TEST(SetConstructorTest, DefaultConstructor) {
  s21::set<int> mySet;
  EXPECT_TRUE(mySet.empty());
  EXPECT_EQ(mySet.size(), 0u);
}

TEST(SetConstructorTest, CopyConstructor) {
  s21::set<int> originalSet;

  originalSet.insert(10);
  originalSet.insert(20);
  originalSet.insert(30);

  s21::set<int> copiedSet(originalSet);

  EXPECT_EQ(copiedSet.size(), 3u);
  EXPECT_NE(copiedSet.find(10), copiedSet.end());
  EXPECT_NE(copiedSet.find(20), copiedSet.end());
  EXPECT_NE(copiedSet.find(30), copiedSet.end());
}

TEST(SetConstructorTest, MoveConstructor) {
  s21::set<int> originalSet;
  originalSet.insert(10);
  originalSet.insert(20);
  originalSet.insert(30);

  s21::set<int> movedSet(std::move(originalSet));

  EXPECT_EQ(movedSet.size(), 3u);
  EXPECT_NE(movedSet.find(10), movedSet.end());
  EXPECT_NE(movedSet.find(20), movedSet.end());
  EXPECT_NE(movedSet.find(30), movedSet.end());

  EXPECT_TRUE(originalSet.empty());
}

TEST(SetConstructorTest, InitializerListConstructor) {
  s21::set<int> mySet = {10, 20, 30};

  EXPECT_EQ(mySet.size(), 3u);
  EXPECT_NE(mySet.find(10), mySet.end());
  EXPECT_NE(mySet.find(20), mySet.end());
  EXPECT_NE(mySet.find(30), mySet.end());
}

TEST(SetDestructorTest, Destructor) {
  s21::set<int>* mySet = new s21::set<int>;
  mySet->insert(10);
  mySet->insert(20);
  mySet->insert(30);

  EXPECT_EQ(mySet->size(), 3u);
  delete mySet;
  SUCCEED();
}

TEST(SetConstructorTest, CopyAssignmentOperator) {
  s21::set<int> originalSet;
  originalSet.insert(10);
  originalSet.insert(20);
  originalSet.insert(30);

  s21::set<int> assignedSet;
  assignedSet = originalSet;

  EXPECT_EQ(assignedSet.size(), 3u);
  EXPECT_NE(assignedSet.find(10), assignedSet.end());
  EXPECT_NE(assignedSet.find(20), assignedSet.end());
  EXPECT_NE(assignedSet.find(30), assignedSet.end());
}

TEST(SetConstructorTest, MoveAssignmentOperator) {
  s21::set<int> originalSet;
  originalSet.insert(10);
  originalSet.insert(20);
  originalSet.insert(30);

  s21::set<int> assignedSet;
  assignedSet = std::move(originalSet);

  EXPECT_EQ(assignedSet.size(), 3u);
  EXPECT_NE(assignedSet.find(10), assignedSet.end());
  EXPECT_NE(assignedSet.find(20), assignedSet.end());
  EXPECT_NE(assignedSet.find(30), assignedSet.end());

  originalSet.clear();
  EXPECT_TRUE(originalSet.empty());
}

TEST(SetTest, Insert) {
  s21::set<int> my_set;

  auto result1 = my_set.insert(10);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(*result1.first, 10);

  auto result2 = my_set.insert(10);
  EXPECT_FALSE(result2.second);
}

TEST(SetTest, Erase) {
  s21::set<int> my_set = {1, 2, 3};
  auto it = my_set.find(2);
  ASSERT_NE(it, my_set.end());

  my_set.erase(it);
  EXPECT_EQ(my_set.size(), static_cast<s21::set<int>::size_type>(2));

  it = my_set.find(2);
  EXPECT_EQ(it, my_set.end());
}

TEST(SetTest, Clear) {
  s21::set<int> my_set = {1, 2, 3};
  my_set.clear();

  EXPECT_TRUE(my_set.empty());
  EXPECT_EQ(my_set.size(), static_cast<s21::set<int>::size_type>(0));
}

TEST(SetTest, Swap) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {4, 5};

  set1.swap(set2);

  EXPECT_EQ(set1.size(), static_cast<s21::set<int>::size_type>(2));
  EXPECT_EQ(set2.size(), static_cast<s21::set<int>::size_type>(3));

  EXPECT_NE(set1.find(4), set1.end());
  EXPECT_NE(set2.find(1), set2.end());
}

TEST(SetTest, Find) {
  s21::set<int> my_set = {1, 2, 3};

  auto it = my_set.find(2);
  EXPECT_NE(it, my_set.end());
  EXPECT_EQ(*it, 2);

  it = my_set.find(4);
  EXPECT_EQ(it, my_set.end());
}

TEST(SetTest, Empty) {
  s21::set<int> my_set;
  EXPECT_TRUE(my_set.empty());

  my_set.insert(1);
  EXPECT_FALSE(my_set.empty());
}

TEST(SetTest, Size) {
  s21::set<int> my_set;
  EXPECT_EQ(my_set.size(), static_cast<s21::set<int>::size_type>(0));

  my_set.insert(1);
  EXPECT_EQ(my_set.size(), static_cast<s21::set<int>::size_type>(1));

  my_set.insert(2);
  EXPECT_EQ(my_set.size(), static_cast<s21::set<int>::size_type>(2));
}

TEST(SetTest, BeginEnd) {
  s21::set<int> my_set = {1, 2, 3};

  auto it = my_set.begin();
  EXPECT_EQ(*it, 1);

  ++it;
  EXPECT_EQ(*it, 2);

  ++it;
  EXPECT_EQ(*it, 3);

  ++it;
  EXPECT_EQ(it, my_set.end());
}

TEST(SetTest, ContainsElementExists) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  EXPECT_TRUE(set.contains(1));
  EXPECT_TRUE(set.contains(3));
  EXPECT_TRUE(set.contains(5));
}

TEST(SetTest, ContainsElementNotExists) {
  s21::set<int> set = {1, 2, 3, 4, 5};

  EXPECT_FALSE(set.contains(0));
  EXPECT_FALSE(set.contains(6));
  EXPECT_FALSE(set.contains(10));
}

TEST(SetTest, MergeBasic) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2 = {3, 4, 5};

  set1.merge(set2);

  EXPECT_EQ(static_cast<int>(set1.size()), 5);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
  EXPECT_TRUE(set1.contains(4));
  EXPECT_TRUE(set1.contains(5));
}

TEST(SetTest, MergeWithEmptySet) {
  s21::set<int> set1 = {1, 2, 3};
  s21::set<int> set2;

  set1.merge(set2);

  EXPECT_EQ(static_cast<int>(set1.size()), 3);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
}

TEST(SetTest, MergeWithSelf) {
  s21::set<int> set1 = {1, 2, 3};

  set1.merge(set1);

  EXPECT_EQ(static_cast<int>(set1.size()), 3);
  EXPECT_TRUE(set1.contains(1));
  EXPECT_TRUE(set1.contains(2));
  EXPECT_TRUE(set1.contains(3));
}

TEST(SetTest, InsertMany) {
  s21::set<int> s;

  auto results = s.insert_many(1, 2, 3, 4);

  EXPECT_EQ(s.size(), static_cast<size_t>(4));

  EXPECT_EQ(results.size(), static_cast<size_t>(4));
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);
  EXPECT_TRUE(results[3].second);

  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
  EXPECT_TRUE(s.contains(4));
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}