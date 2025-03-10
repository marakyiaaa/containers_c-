#include <queue>

#include "gtest/gtest.h"
#include "s21_queue.h"

TEST(default_constructor_suite, int_true_test) {
  s21::queue<int> s21_a;
  std::queue<int> std_a;

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
}

TEST(default_constructor_suite, double_true_test) {
  s21::queue<double> s21_a;
  std::queue<double> std_a;

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
}

TEST(default_constructor_suite, float_true_test) {
  s21::queue<float> s21_a;
  std::queue<float> std_a;

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
}

TEST(default_constructor_suite, struct_true_test) {
  struct test_struct {
    int a;
    double b;
    float c;
  };

  s21::queue<test_struct> s21_a;
  std::queue<test_struct> std_a;

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
}

TEST(initializer_constructor_suite, int_true_test) {
  s21::queue<int> s21_a({1, 2, 3, 4, 5});
  std::queue<int> std_a({1, 2, 3, 4, 5});

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_a.front() == std_a.front());
  EXPECT_TRUE(s21_a.back() == std_a.back());
}

TEST(initializer_constructor_suite, double_true_test) {
  s21::queue<double> s21_a({1, 2, 3, 4, 5});
  std::queue<double> std_a({1, 2, 3, 4, 5});

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_a.front() == std_a.front());
  EXPECT_TRUE(s21_a.back() == std_a.back());
}

TEST(initializer_constructor_suite, float_true_test) {
  s21::queue<float> s21_a({1, 2, 3, 4, 5});
  std::queue<float> std_a({1, 2, 3, 4, 5});

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_a.front() == std_a.front());
  EXPECT_TRUE(s21_a.back() == std_a.back());
}

TEST(initializer_constructor_suite, struct_true_test) {
  struct test_struct {
    int a;
    double b;
    float c;
  };
  test_struct a{}, b{}, c{}, d{}, e{};
  s21::queue<test_struct> s21_a({a, b, c, d, e});
  std::queue<test_struct> std_a({a, b, c, d, e});

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
}

TEST(copy_constructor_suite, int_true_test) {
  s21::queue<int> s21_b({1, 2, 3, 4, 5});
  s21::queue<int> s21_a(s21_b);
  std::queue<int> std_b({1, 2, 3, 4, 5});
  std::queue<int> std_a(std_b);

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());

  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(copy_constructor_suite, double_true_test) {
  s21::queue<double> s21_b({1, 2, 3, 4, 5});
  s21::queue<double> s21_a(s21_b);
  std::queue<double> std_b({1, 2, 3, 4, 5});
  std::queue<double> std_a(std_b);

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());

  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(copy_constructor_suite, float_true_test) {
  s21::queue<float> s21_b({1, 2, 3, 4, 5});
  s21::queue<float> s21_a(s21_b);
  std::queue<float> std_b({1, 2, 3, 4, 5});
  std::queue<float> std_a(std_b);

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());

  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(copy_constructor_suite, struct_true_test) {
  struct test_struct {
    int a;
    double b;
    float c;
  };
  test_struct a{}, b{}, c{}, d{}, e{};
  s21::queue<test_struct> s21_a({a, b, c, d, e});
  std::queue<test_struct> std_a({a, b, c, d, e});
  s21::queue<test_struct> s21_b(s21_a);
  std::queue<test_struct> std_b(std_a);

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(move_constructor_suite, int_true_test) {
  s21::queue<int> s21_a({1, 2, 3});
  s21::queue<int> s21_b(std::move(s21_a));
  std::queue<int> std_a({1, 2, 3});
  std::queue<int> std_b(std::move(std_a));

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(move_constructor_suite, double_true_test) {
  s21::queue<double> s21_a({1, 2, 3});
  s21::queue<double> s21_b(std::move(s21_a));
  std::queue<double> std_a({1, 2, 3});
  std::queue<double> std_b(std::move(std_a));

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(move_constructor_suite, flaot_true_test) {
  s21::queue<float> s21_a({1, 2, 3});
  s21::queue<float> s21_b(std::move(s21_a));
  std::queue<float> std_a({1, 2, 3});
  std::queue<float> std_b(std::move(std_a));

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(move_constructor_suite, struct_true_test) {
  struct test_struct {
    int a;
    double b;
    float c;
  };
  test_struct a{}, b{}, c{}, d{}, e{};
  s21::queue<test_struct> s21_a({a, b, c, d, e});
  s21::queue<test_struct> s21_b(std::move(s21_a));
  std::queue<test_struct> std_a({a, b, c, d, e});
  std::queue<test_struct> std_b(std::move(std_a));

  EXPECT_TRUE(s21_a.empty() == std_a.empty());
  EXPECT_TRUE(s21_a.size() == std_a.size());
  EXPECT_TRUE(s21_b.empty() == std_b.empty());
  EXPECT_TRUE(s21_b.size() == std_b.size());
}

TEST(queue_insert_many_back, insert) {
  s21::queue<float> s21_a({1, 2, 3});
  s21_a.insert_many_back(4, 5, 6);
  EXPECT_TRUE(s21_a.front() == 1);
  EXPECT_TRUE(s21_a.back() == 6);
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}