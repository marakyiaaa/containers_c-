#include <gtest/gtest.h>

#include "s21_map.h"

TEST(mapTest, DefaultConstructorString) {
  s21::map<int, std::string> map;

  EXPECT_TRUE(map.empty());
  EXPECT_EQ(static_cast<int>(map.size()), 0);
}

TEST(mapTest, InitializerListConstructorString) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(static_cast<int>(map.size()), 3);

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map.at(2), "two");
  EXPECT_EQ(map.at(3), "three");

  map.clear();
}

TEST(mapTest, InitializerListConstructorEmptyString) {
  s21::map<int, std::string> map = {};

  EXPECT_TRUE(map.empty());
  EXPECT_EQ(static_cast<int>(map.size()), 0);
}

TEST(mapTest, DefaultConstructorInt) {
  s21::map<int, int> map;

  EXPECT_TRUE(map.empty());
  EXPECT_EQ(static_cast<int>(map.size()), 0);
}

TEST(mapTest, InitializerListConstructorInt) {
  s21::map<int, int> map = {{1, 10}, {2, 20}, {3, 30}};

  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
  EXPECT_EQ(map.at(3), 30);

  EXPECT_FALSE(map.empty());

  EXPECT_EQ(static_cast<int>(map.size()), 3);

  EXPECT_EQ(map.at(1), 10);
  EXPECT_EQ(map.at(2), 20);
  EXPECT_EQ(map.at(3), 30);

  EXPECT_THROW(map.at(4), std::out_of_range);
}

TEST(mapTest, InitializerListConstructorEmptyInt) {
  s21::map<int, int> map = {};
  EXPECT_TRUE(map.empty());
  EXPECT_EQ(static_cast<int>(map.size()), 0);
}

TEST(MapTest, InsertOrAssign) {
  s21::map<int, int> my_map;

  auto result1 = my_map.insert_or_assign(1, 100);
  EXPECT_TRUE(result1.second);
  EXPECT_EQ(result1.first->first, 1);
  EXPECT_EQ(result1.first->second, 100);

  auto result3 = my_map.insert_or_assign(2, 300);
  EXPECT_TRUE(result3.second);
  EXPECT_EQ(result3.first->first, 2);
  EXPECT_EQ(result3.first->second, 300);

  EXPECT_EQ(static_cast<int>(my_map.size()), 2);
}

TEST(MapTest, MergeNonOverlappingMaps) {
  s21::map<int, int> map1;
  s21::map<int, int> map2;

  map1.insert_or_assign(1, 10);
  map1.insert_or_assign(2, 20);

  map2.insert_or_assign(3, 30);
  map2.insert_or_assign(4, 40);

  map1.merge(map2);

  EXPECT_EQ(static_cast<int>(map1.size()), 4);

  EXPECT_EQ(map1.at(1), 10);
  EXPECT_EQ(map1.at(2), 20);
  EXPECT_EQ(map1.at(3), 30);
  EXPECT_EQ(map1.at(4), 40);
}

TEST(MapTest, EraseTest) {
  s21::map<int, int> my_map;

  my_map.insert(1, 100);
  my_map.insert(2, 200);
  my_map.insert(3, 300);

  auto it = my_map.find(2);
  my_map.erase(it);

  EXPECT_EQ(my_map.find(2), my_map.end());

  EXPECT_NE(my_map.find(1), my_map.end());
  EXPECT_NE(my_map.find(3), my_map.end());
}

TEST(MapTest, SwapTest) {
  s21::map<int, int> map1;
  s21::map<int, int> map2;

  map1.insert(1, 100);
  map1.insert(2, 200);

  map2.insert(3, 300);
  map2.insert(4, 400);

  map1.swap(map2);

  EXPECT_EQ(static_cast<int>(map1.size()), 2);
  EXPECT_EQ(static_cast<int>(map2.size()), 2);

  EXPECT_EQ(map1.at(3), 300);
  EXPECT_EQ(map1.at(4), 400);

  EXPECT_EQ(map2.at(1), 100);
  EXPECT_EQ(map2.at(2), 200);
}

TEST(MapTest, InsertMany) {
  s21::map<int, std::string> my_map;

  auto results =
      my_map.insert_many(std::make_pair(1, "one"), std::make_pair(2, "two"),
                         std::make_pair(3, "three"));

  EXPECT_EQ(my_map.size(), static_cast<size_t>(3));

  EXPECT_EQ(my_map.at(1), "one");
  EXPECT_EQ(my_map.at(2), "two");
  EXPECT_EQ(my_map.at(3), "three");

  EXPECT_EQ(results.size(), static_cast<size_t>(3));
  EXPECT_TRUE(results[0].second);
  EXPECT_TRUE(results[1].second);
  EXPECT_TRUE(results[2].second);

  for (const auto& result : results) {
    EXPECT_TRUE(result.second);
  }
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
