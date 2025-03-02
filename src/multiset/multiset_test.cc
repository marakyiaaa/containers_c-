#include "gtest/gtest.h"
#include "s21_multiset.h"

TEST(multisetTest, DefaultConstructor) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), static_cast<size_t>(0));
}

TEST(multisetTest, InitializerListConstructor) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5};
  EXPECT_FALSE(ms.empty());
  EXPECT_EQ(ms.size(), static_cast<size_t>(5));
}

TEST(multisetTest, CopyConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(ms1);
  EXPECT_EQ(ms2.size(), ms1.size());
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
}

TEST(multisetTest, MoveConstructor) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2(std::move(ms1));
  EXPECT_EQ(ms2.size(), static_cast<size_t>(3));
  EXPECT_TRUE(ms2.contains(1));
  EXPECT_TRUE(ms2.contains(2));
  EXPECT_TRUE(ms2.contains(3));
  EXPECT_TRUE(ms1.empty());
}

TEST(multisetTest, Erase) {
  s21::multiset<int> ms = {1, 2, 3, 4};
  auto it = ms.find(2);
  ms.erase(it);
  EXPECT_FALSE(ms.contains(2));
  EXPECT_EQ(ms.size(), static_cast<size_t>(3));
}

TEST(multisetTest, EraseNonExistent) {
  s21::multiset<int> ms = {1, 2, 3};
  auto it = ms.find(4);
  if (it != ms.end()) {
    ms.erase(it);
  }
  EXPECT_EQ(ms.size(), static_cast<size_t>(3));
}

TEST(multisetTest, BeginAndEnd) {
  s21::multiset<int> ms = {1, 2, 3};
  auto it = ms.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
  ++it;
  EXPECT_EQ(it, ms.end());
}

TEST(multisetTest, Clear) {
  s21::multiset<int> ms = {1, 2, 3};
  ms.clear();
  EXPECT_TRUE(ms.empty());
  EXPECT_EQ(ms.size(), static_cast<size_t>(0));
}

TEST(multisetTest, Find) {
  s21::multiset<int> ms = {1, 2, 3};
  auto it = ms.find(2);
  EXPECT_NE(it, ms.end());
  EXPECT_EQ(*it, 2);
  it = ms.find(4);
  EXPECT_EQ(it, ms.end());
}

TEST(multisetTest, Count) {
  s21::multiset<int> ms = {1, 2, 2, 3};
  EXPECT_EQ(ms.count(1), static_cast<size_t>(1));
  EXPECT_EQ(ms.count(4), static_cast<size_t>(0));
}

TEST(multisetTest, Contains) {
  s21::multiset<int> ms = {1, 2, 3};
  EXPECT_TRUE(ms.contains(2));
  EXPECT_FALSE(ms.contains(4));
}

TEST(multisetTest, LowerUpperBound) {
  s21::multiset<int> ms = {1, 2, 3, 4, 5};
  auto it_lower = ms.lower_bound(3);
  EXPECT_EQ(*it_lower, 3);
  auto it_upper = ms.upper_bound(3);
  EXPECT_EQ(*it_upper, 4);
}

TEST(multisetTest, Swap) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {4, 5, 6};
  ms1.swap(ms2);
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms2.contains(1));
}

TEST(multisetTest, Merge) {
  s21::multiset<int> ms1 = {1, 2, 3};
  s21::multiset<int> ms2 = {7, 4, 5};
  ms1.merge(ms2);

  EXPECT_EQ(ms1.count(3), static_cast<size_t>(1));
  EXPECT_TRUE(ms1.contains(4));
  EXPECT_TRUE(ms1.contains(5));

  EXPECT_EQ(ms2.size(), static_cast<size_t>(0));
}

TEST(SetTest, InsertMany) {
  s21::multiset<int> s;

  auto results = s.insert_many(1, 2, 3, 4, 5);

  EXPECT_EQ(s.size(), static_cast<size_t>(5));

  EXPECT_EQ(s.count(1), static_cast<size_t>(1));
  EXPECT_EQ(s.count(2), static_cast<size_t>(1));
  EXPECT_EQ(s.count(3), static_cast<size_t>(1));
  EXPECT_EQ(s.count(4), static_cast<size_t>(1));
  EXPECT_EQ(s.count(5), static_cast<size_t>(1));

  EXPECT_EQ(results.size(), static_cast<size_t>(5));

  EXPECT_EQ(results[0].second, true);
  EXPECT_EQ(results[1].second, true);
  EXPECT_EQ(results[2].second, true);
  EXPECT_EQ(results[3].second, true);
  EXPECT_EQ(results[4].second, true);

  auto it = s.find(1);
  EXPECT_NE(it, s.end());

  it = s.find(2);
  EXPECT_NE(it, s.end());

  it = s.find(3);
  EXPECT_NE(it, s.end());

  it = s.find(4);
  EXPECT_NE(it, s.end());

  it = s.find(5);
  EXPECT_NE(it, s.end());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}