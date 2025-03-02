#include <gtest/gtest.h>

#include <array>

#include "s21_array.h"

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 5> arr;
  EXPECT_EQ(arr.size(), 5);
  EXPECT_TRUE(arr.empty() == false);
  for (size_t i = 0; i < arr.size(); ++i) {
    EXPECT_EQ(arr[i], 0);
  }
}

TEST(ArrayTest, InitializerListConstructor) {
  s21::array<int, 3> arr = {1, 2, 3};
  EXPECT_EQ(arr.size(), 3);
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
}

TEST(ArrayTest, CopyConstructor) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = arr1;
  EXPECT_EQ(arr2.size(), 4);
  for (size_t i = 0; i < arr2.size(); ++i) {
    EXPECT_EQ(arr2[i], arr1[i]);
  }
}

TEST(ArrayTest, MoveConstructor) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr1.data(), nullptr);
  EXPECT_EQ(arr1.size(), 0);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, MoveAssignmentOperator) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2;
  arr2 = std::move(arr1);
  EXPECT_EQ(arr2.size(), 4);
  EXPECT_EQ(arr1.data(), nullptr);
  EXPECT_EQ(arr1.size(), 0);
  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, At) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);
  EXPECT_THROW(arr.at(4), std::out_of_range);
}

TEST(ArrayTest, SubscriptOperator) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
}

TEST(ArrayTest, Front) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.front(), 1);
}

TEST(ArrayTest, Back) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.back(), 4);
}

TEST(ArrayTest, Data) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  int* data = arr.data();
  EXPECT_EQ(data[0], 1);
  EXPECT_EQ(data[1], 2);
  EXPECT_EQ(data[2], 3);
  EXPECT_EQ(data[3], 4);
}

TEST(ArrayTest, BeginEndItr) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  int expected_value = 1;
  for (auto it = arr.begin(); it != arr.end(); ++it) {
    EXPECT_EQ(*it, expected_value);
    ++expected_value;
  }
}

TEST(ArrayTest, Empty) {
  s21::array<int, 0> arr1;
  EXPECT_TRUE(arr1.empty());

  s21::array<int, 4> arr2 = {1, 2, 3, 4};
  EXPECT_FALSE(arr2.empty());
}

TEST(ArrayTest, Size) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  EXPECT_EQ(arr.size(), 4);

  s21::array<int, 0> arr_empty;
  EXPECT_EQ(arr_empty.size(), 0);
}

TEST(ArrayTest, MaxSize) {
  s21::array<int, 4> arr;
  EXPECT_EQ(arr.max_size(), 4);

  s21::array<int, 0> arr_empty;
  EXPECT_EQ(arr_empty.max_size(), 0);
}

TEST(ArrayTest, Swap) {
  s21::array<int, 4> arr1 = {1, 2, 3, 4};
  s21::array<int, 4> arr2 = {5, 6, 7, 8};
  arr1.swap(arr2);

  EXPECT_EQ(arr1[0], 5);
  EXPECT_EQ(arr1[1], 6);
  EXPECT_EQ(arr1[2], 7);
  EXPECT_EQ(arr1[3], 8);

  EXPECT_EQ(arr2[0], 1);
  EXPECT_EQ(arr2[1], 2);
  EXPECT_EQ(arr2[2], 3);
  EXPECT_EQ(arr2[3], 4);
}

TEST(ArrayTest, Fill) {
  s21::array<int, 4> arr = {1, 2, 3, 4};
  arr.fill(7);

  EXPECT_EQ(arr[0], 7);
  EXPECT_EQ(arr[1], 7);
  EXPECT_EQ(arr[2], 7);
  EXPECT_EQ(arr[3], 7);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}