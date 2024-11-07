#include "../s21_containers/map/s21_map.h"

#include <gtest/gtest.h>

#include <map>

#include "s21_test.h"

bool compare(std::map<int, int> &m, s21::map<int, int> s) {
  bool res = true;
  auto std_itr = m.begin();
  auto itr = s.begin();
  for (; std_itr != m.end() && res; ++std_itr, ++itr) {
    if ((*itr).first != (*std_itr).first) {
      res = false;
    }
  }
  return res;
}

TEST(map_modifiers_suite, merge) {
  s21::map<int, int> a = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}};
  s21::map<int, int> b = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}, {11, 1}};

  s21::map<int, int> result = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}, {11, 1}};

  a.merge(b);
  auto a_itr = a.begin();
  auto result_itr = result.begin();
  for (; a_itr != a.end(); ++a_itr, ++result_itr) {
    EXPECT_EQ(*a_itr, *result_itr);
  }
}

TEST(map_modifiers_suite, merge_empty) {
  s21::map<int, int> a = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}};
  s21::map<int, int> b;
  s21::map<int, int> result = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}};

  a.merge(b);
  auto a_itr = a.begin();
  auto result_itr = result.begin();
  for (; a_itr != a.end(); ++a_itr, ++result_itr) {
    EXPECT_EQ(*a_itr, *result_itr);
  }
}

TEST(map_modifiers_suite, merge_both_empty) {
  s21::map<int, int> a;
  s21::map<int, int> b;
  s21::map<int, int> result;

  a.merge(b);
  auto a_itr = a.begin();
  auto result_itr = result.begin();
  for (; a_itr != a.end(); ++a_itr, ++result_itr) {
    EXPECT_EQ(*a_itr, *result_itr);
  }
}

TEST(map_lookup_suite, contains) {
  s21::map<int, int> a = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}};

  EXPECT_TRUE(a.contains(1));
  EXPECT_TRUE(a.contains(2));
  EXPECT_TRUE(a.contains(3));
  EXPECT_TRUE(a.contains(4));
  EXPECT_TRUE(a.contains(5));

  EXPECT_FALSE(a.contains(8));
  EXPECT_FALSE(a.contains(6));
  EXPECT_FALSE(a.contains(123));
}

TEST(map_element_access, braces_and_at) {
  s21::map<int, int> a;
  std::map<int, int> std_a;

  std_a.insert({1, 1});
  std_a.insert({2, 34});
  std_a.insert({3, 234});

  a.insert({1, 1});
  a.insert({2, 34});
  a.insert({3, 234});

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());

  auto std_itr = std_a.begin();
  auto itr = a.begin();

  for (int i = 1; std_itr != std_a.end(); ++std_itr, ++itr, ++i) {
    EXPECT_EQ(a.at(i), std_a.at(i));
    EXPECT_EQ(a[i], std_a[i]);
    EXPECT_EQ((*itr).first, (*std_itr).first);
    EXPECT_EQ((*itr).second, (*std_itr).second);
  }
}

TEST(map_modifiers_insert, insert_or_assign) {
  s21::map<int, int> a;
  std::map<int, int> std_a;

  a.insert_or_assign(1, 1);
  a.insert_or_assign(2, 1);

  std_a.insert_or_assign(1, 1);
  std_a.insert_or_assign(2, 1);

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());
  EXPECT_EQ(compare(std_a, a), true);
}

TEST(map_erase_suite, erase_no_child) {
  std::map<int, int> std_a;
  s21::map<int, int> a;

  a.insert(1, 0);
  a.insert(2, 0);
  a.insert(3, 0);

  auto std_itr_1 = std_a.insert({1, 0}).first;
  auto std_itr_2 = std_a.insert({2, 0}).first;
  auto std_itr_3 = std_a.insert({3, 0}).first;

  a.erase(a.find(1));
  std_a.erase(std_itr_1);
  EXPECT_EQ(compare(std_a, a), true);

  a.erase(a.find(3));
  std_a.erase(std_itr_3);
  EXPECT_EQ(compare(std_a, a), true);

  a.erase(a.find(2));
  std_a.erase(std_itr_2);

  EXPECT_EQ(a.empty(), std_a.empty());
}

TEST(map_erase_suite, erase_one_child) {
  std::map<int, int> std_a;
  s21::map<int, int> a;

  std_a.insert({5, 0});
  std_a.insert({3, 0});

  a.insert(5, 0);
  a.insert(3, 0);

  a.erase(a.find(3));
  std_a.erase(std_a.find(3));
  EXPECT_EQ(compare(std_a, a), true);

  a.erase(a.find(5));
  std_a.erase(std_a.find(5));
  EXPECT_EQ(compare(std_a, a), true);
}

TEST(map_erase_suite, erase_two_child) {
  std::map<int, int> std_a;
  s21::map<int, int> a;
  std_a.insert({5, 0});
  std_a.insert({3, 0});

  a.insert(5, 0);
  a.insert(3, 0);

  a.erase(a.find(3));
  std_a.erase(std_a.find(3));
  EXPECT_EQ(compare(std_a, a), true);

  a.erase(a.find(5));
  std_a.erase(std_a.find(5));
  EXPECT_EQ(compare(std_a, a), true);
}

TEST(map_constructor_suite, default_constructor) {
  std::map<int, int> std_a;
  s21::map<int, int> a;

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(map_constructor_suite, copy_constructor) {
  std::map<int, int> std_a;
  s21::map<int, int> a;

  std_a.insert({1, 1});
  std_a.insert({3, 2});
  std_a.insert({4, 2});

  a.insert(1, 1);
  a.insert(3, 2);
  a.insert(4, 2);

  std::map<int, int> std_b(std_a);
  s21::map<int, int> b(a);

  EXPECT_EQ(b.empty(), std_b.empty());
  EXPECT_EQ(b.size(), std_b.size());
  EXPECT_EQ(compare(std_b, b), true);
}

TEST(map_constructor_suite, initializer_constructor) {
  std::map<int, int> std_a = {{1, 0}, {2, 0}, {3, 0}};

  s21::map<int, int> a = {{1, 0}, {2, 0}, {3, 0}};

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());

  EXPECT_EQ(compare(std_a, a), true);
}

TEST(map_constructor_suite, move_constructor) {
  std::map<int, int> std_a = {{1, 0}, {2, 0}, {3, 0}};

  s21::map<int, int> a = {{1, 0}, {2, 0}, {3, 0}};

  std::map<int, int> std_b(std::move(std_a));
  s21::map<int, int> b(std::move(a));

  EXPECT_EQ(b.empty(), std_b.empty());
  EXPECT_EQ(b.size(), std_b.size());

  EXPECT_EQ(compare(std_b, b), true);
}

TEST(map_constructor_suite, move_operator) {
  std::map<int, int> std_a = {{1, 0}, {2, 0}, {3, 0}};

  s21::map<int, int> a = {{1, 0}, {2, 0}, {3, 0}};

  std::map<int, int> std_b = std::move(std_a);
  s21::map<int, int> b = std::move(a);

  EXPECT_EQ(b.empty(), std_b.empty());
  EXPECT_EQ(b.size(), std_b.size());

  EXPECT_EQ(compare(std_b, b), true);
}

TEST(map_constructor_suite, initializer_constructor_2) {
  std::map<int, int> std_a = {};

  s21::map<int, int> a = {};

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());

  EXPECT_EQ(compare(std_a, a), true);
}

TEST(map_constructor_suite, move_constructor_2) {
  std::map<int, int> std_a;

  s21::map<int, int> a;

  std_a.insert({1, 1});
  std_a.insert({2, 0});
  std_a.insert({3, 0});
  std_a.insert({4, 10});
  std_a.insert({12, 4});
  std_a.insert({10, 0});
  std_a.insert({1, 8});
  std_a.insert({21, 1});
  std_a.insert({12, 9});
  std_a.insert({100, 9});

  a.insert({1, 1});
  a.insert({2, 0});
  a.insert({3, 0});
  a.insert({4, 10});
  a.insert({12, 4});
  a.insert({10, 0});
  a.insert({1, 8});
  a.insert({21, 1});
  a.insert({12, 9});
  a.insert({100, 9});

  std::map<int, int> std_b(std::move(std_a));
  s21::map<int, int> b(std::move(a));

  EXPECT_EQ(b.empty(), std_b.empty());
  EXPECT_EQ(b.size(), std_b.size());

  EXPECT_EQ(compare(std_b, b), true);
}

TEST(map_constructor_suite, move_operator_2) {
  std::map<int, int> std_a = {};

  s21::map<int, int> a = {};

  std::map<int, int> std_b = std::move(std_a);
  s21::map<int, int> b = std::move(a);

  EXPECT_EQ(b.empty(), std_b.empty());
  EXPECT_EQ(b.size(), std_b.size());

  EXPECT_EQ(compare(std_b, b), true);
}

TEST(map_iterator_suite, begin) {
  std::map<int, int> std_a = {{1, 0}, {2, 0}, {3, 0}};
  s21::map<int, int> a = {{1, 0}, {2, 0}, {3, 0}};

  EXPECT_EQ((*a.begin()).first, (*std_a.begin()).first);
  EXPECT_EQ((*a.begin()).second, (*std_a.begin()).second);
}

TEST(map_iterator_suite, end) {
  std::map<int, int> s21map = {{1, 0}, {2, 0}, {3, 0}};
  s21::map<int, int> stdmap = {{1, 0}, {2, 0}, {3, 0}};

  auto s21_end = s21map.end();
  auto std_end = stdmap.end();

  ASSERT_NE(s21map.begin(), s21_end);
  ASSERT_NE(stdmap.begin(), std_end);

  auto s21_it = s21map.begin();
  auto std_it = stdmap.begin();
  while (s21_it != s21_end && std_it != std_end) {
    ASSERT_EQ(s21_it->first, std_it->first);
    ASSERT_EQ(s21_it->second, std_it->second);
    ++s21_it;
    ++std_it;
  }
  ASSERT_EQ(s21_it, s21_end);
  ASSERT_EQ(std_it, std_end);
}

TEST(map_iterator_suite, end_empty_container) {
  s21::map<int, double> s21map;
  std::map<int, double> stdmap;

  ASSERT_EQ(s21map.begin(), s21map.end());
  ASSERT_EQ(stdmap.begin(), stdmap.end());
}

TEST(map_modifiers_suite, clear_1) {
  std::map<int, int> std_a = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};

  s21::map<int, int> a = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 0}};

  std_a.clear();
  a.clear();

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(map_modifiers_suite, clear_2) {
  std::map<int, int> std_a;
  s21::map<int, int> a;

  std_a.clear();
  a.clear();

  EXPECT_EQ(a.empty(), std_a.empty());
  EXPECT_EQ(a.size(), std_a.size());
}

TEST(map_modifiers_suite, insert) {
  std::map<int, int> std_a;
  s21::map<int, int> a;

  std_a.insert({1, 1});
  std_a.insert({2, 0});
  std_a.insert({3, 0});
  std_a.insert({4, 10});
  std_a.insert({12, 4});
  std_a.insert({10, 0});
  std_a.insert({1, 8});
  std_a.insert({21, 1});
  std_a.insert({12, 9});
  std_a.insert({100, 9});

  a.insert({1, 1});
  a.insert({2, 0});
  a.insert({3, 0});
  a.insert({4, 10});
  a.insert({12, 4});
  a.insert({10, 0});
  a.insert({1, 8});
  a.insert({21, 1});
  a.insert({12, 9});
  a.insert({100, 9});

  EXPECT_EQ(compare(std_a, a), true);
}

TEST(map_modifiers_suite, swap) {
  s21::map<int, int> a = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}};

  s21::map<int, int> b = {{11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 5}};

  s21::map<int, int> b_swap = {{1, 1}, {2, 0}, {3, 0}, {4, 0}, {5, 5}};

  s21::map<int, int> a_swap = {{11, 1}, {12, 0}, {13, 0}, {14, 0}, {15, 5}};

  a.swap(b);
  auto a_itr = a.begin();
  auto a_swap_itr = a_swap.begin();
  for (; a_itr != a.end(); ++a_itr, ++a_swap_itr) {
    EXPECT_EQ(*a_itr, *a_swap_itr);
  }

  auto b_itr = b.begin();
  auto b_swap_itr = b_swap.begin();
  for (; b_itr != b.end(); ++b_itr, ++b_swap_itr) {
    EXPECT_EQ(*b_itr, *b_swap_itr);
  }
}

template <typename Key, typename T>
void compare_s21_std_map(s21::map<Key, T> s21map, std::map<Key, T> stdmap) {
  ASSERT_EQ(s21map.size(), stdmap.size());
  auto s21i = s21map.begin();
  auto stdi = stdmap.begin();
  for (; s21i != s21map.end(); s21i++, stdi++)
    ASSERT_EQ(s21i->first, stdi->first);
}

template <typename Key, typename T>
void compare_s21_std_map(std::map<Key, T> stdmap, s21::map<Key, T> s21map) {
  ASSERT_EQ(s21map.size(), stdmap.size());
  auto s21i = s21map.begin();
  auto stdi = stdmap.begin();
  for (; s21i != s21map.end(); s21i++, stdi++)
    ASSERT_EQ(s21i->first, stdi->first);
}

template <typename Key, typename T>
void compare_s21_s21_map(s21::map<Key, T> s21map_1, s21::map<Key, T> s21map_2) {
  ASSERT_EQ(s21map_1.size(), s21map_2.size());
  auto s21_i_1 = s21map_1.begin();
  auto s21_i_2 = s21map_2.begin();
  for (; s21_i_1 != s21map_1.end(); s21_i_1++, s21_i_2++)
    ASSERT_EQ(s21_i_1->first, s21_i_2->first);
}

TEST(map, size1) {
  s21::map<int, double> s21map = {};
  ASSERT_EQ(s21map.size(), 0UL);
}

TEST(map, size2) {
  s21::map<int, double> s21map = {{1, 1.3}};
  ASSERT_EQ(s21map.size(), 1UL);
}

TEST(map, size3) {
  s21::map<int, double> s21map = {{1, 1.3}, {2, 2.3}};
  ASSERT_EQ(s21map.size(), 2UL);
}

TEST(map, simple1) {
  s21::map<int, double> s21map = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                  {4, 4.3}, {5, 5.3}, {6, 6.3},
                                  {7, 7.3}, {8, 8.3}, {9, 9.3}};
  std::map<int, double> stdmap = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                  {4, 4.3}, {5, 5.3}, {6, 6.3},
                                  {7, 7.3}, {8, 8.3}, {9, 9.3}};
  compare_s21_std_map(stdmap, s21map);
}

TEST(map, simple2) {
  s21::map<int, double> s21map = {
      {1, 1.3}, {2, 2.3}, {3, 3.3}, {4, 4.3}, {5, 5.3}, {6, 6.3},
      {7, 7.3}, {8, 8.3}, {9, 9.3}, {1, 1.5}, {2, 2.5}, {3, 3.5},
      {4, 4.3}, {5, 5.3}, {6, 6.5}, {7, 7.5}, {8, 8.5}, {9, 9.5}};
  std::map<int, double> stdmap = {
      {1, 1.3}, {2, 2.3}, {3, 3.3}, {4, 4.3}, {5, 5.3}, {6, 6.3},
      {7, 7.3}, {8, 8.3}, {9, 9.3}, {1, 1.5}, {2, 2.5}, {3, 3.5},
      {4, 4.3}, {5, 5.3}, {6, 6.5}, {7, 7.5}, {8, 8.5}, {9, 9.5}};
  compare_s21_std_map(stdmap, s21map);
}

TEST(map, simple3) {
  s21::map<int, double> s21map = {{3, 3.3}, {1, 1.3}, {4, 4.3},
                                  {7, 7.3}, {8, 8.3}, {9, 9.3},
                                  {5, 5.3}, {6, 6.3}, {2, 2.3}};
  std::map<int, double> stdmap = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                  {4, 4.3}, {5, 5.3}, {6, 6.3},
                                  {7, 7.3}, {8, 8.3}, {9, 9.3}};
  compare_s21_std_map(stdmap, s21map);
}

TEST(map, simple4) {
  s21::map<int, double> s21map_orig = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                       {4, 4.3}, {5, 5.3}, {6, 6.3},
                                       {7, 7.3}, {8, 8.3}, {9, 9.3}};
  s21::map<int, double> s21map_target = s21map_orig;
  compare_s21_s21_map(s21map_target, s21map_orig);
}

TEST(map, simple5) {
  s21::map<int, double> s21map = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                  {4, 4.3}, {5, 5.3}, {6, 6.3},
                                  {7, 7.3}, {8, 8.3}, {9, 9.3}};
  std::map<int, double> stdmap = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                  {4, 4.3}, {5, 5.3}, {6, 6.3},
                                  {7, 7.3}, {8, 8.3}, {9, 9.3}};
  // s21map = s21map;
  compare_s21_std_map(stdmap, s21map);
}

TEST(map, empty1) {
  s21::map<int, double> s21map = {};
  ASSERT_EQ(s21map.empty(), true);
}

TEST(map, empty2) {
  s21::map<int, double> s21map = {{1, 1.3}};
  ASSERT_EQ(s21map.empty(), false);
}

TEST(map, clear) {
  s21::map<int, double> s21map = {{1, 1.3}, {2, 2.3}, {3, 3.3}};
  s21map.clear();
  ASSERT_EQ(s21map.empty(), true);
}

TEST(map, max_size) {
  s21::map<int, double> s21map = {};
  std::map<int, double> stdmap = {};
  ASSERT_EQ(s21map.max_size(), stdmap.max_size());
}

TEST(map, swap) {
  s21::map<int, double> s21map_1 = {{5, 5.3}, {3, 3.3}};
  s21::map<int, double> s21map_2 = {{7, 7.3}, {8, 8.3}, {9, 9.3}};
  std::map<int, double> stdmap_1 = {{5, 5.3}, {3, 3.3}};
  std::map<int, double> stdmap_2 = {{7, 7.3}, {8, 8.3}, {9, 9.3}};
  stdmap_1.swap(stdmap_2);
  s21map_1.swap(s21map_2);
  compare_s21_std_map(stdmap_1, s21map_1);
  compare_s21_std_map(stdmap_2, s21map_2);
}

TEST(map, merge1) {
  s21::map<int, double> s21map_1 = {{5, 5.3}, {3, 3.3}};
  s21::map<int, double> s21map_2 = {{7, 7.3}, {8, 8.3}, {9, 9.3}};
  std::map<int, double> stdmap_1 = {{5, 5.3}, {3, 3.3}};
  std::map<int, double> stdmap_2 = {{7, 7.3}, {8, 8.3}, {9, 9.3}};
  s21map_1.merge(s21map_2);
  stdmap_1.merge(stdmap_2);
  compare_s21_std_map(s21map_1, stdmap_1);
}

TEST(map, merge2) {
  s21::map<int, double> s21map_1 = {{5, 5.3}, {3, 3.3}};
  s21::map<int, double> s21map_2 = {{7, 7.3}, {8, 8.3}, {9, 9.3}};
  std::map<int, double> stdmap = {
      {5, 5.3}, {3, 3.3}, {7, 7.3}, {8, 8.3}, {9, 9.3}};
  s21map_1.merge(s21map_2);
  compare_s21_std_map(s21map_1, stdmap);
}

TEST(map, insert1) {
  s21::map<int, double> s21map_1 = {{1, 1.3}};
  s21::map<int, double> s21map_2 = {};
  auto pair = s21map_2.insert({1, 1.3});
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(pair.first->first, 1);
  pair = s21map_2.insert({1, 1.5});
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(pair.first->first, 1);
  compare_s21_s21_map(s21map_1, s21map_2);
}

TEST(map, insert2) {
  s21::map<int, double> s21map_1 = {{1, 1.3}, {2, 2.3}, {3, 3.3}, {4, 4.3},
                                    {5, 5.3}, {6, 6.3}, {7, 7.3}};
  s21::map<int, double> s21map_2 = {{2, 2.3}, {4, 4.3}, {7, 7.3}};
  s21map_2.insert({3, 3.3});
  s21map_2.insert({4, 4.3});
  s21map_2.insert({3, 3.5});
  s21map_2.insert({2, 2.5});
  s21map_2.insert({5, 5.3});
  s21map_2.insert({7, 7.5});
  s21map_2.insert({6, 6.3});
  auto pair = s21map_2.insert({1, 1.3});
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(pair.first->first, 1);
  pair = s21map_2.insert({1, 1.5});
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(pair.first->first, 1);
  compare_s21_s21_map(s21map_1, s21map_2);
}

TEST(map, insert3) {
  std::map<int, double> s21map_1 = {
      {0, 0.3},     {-100, -100.3}, {100, 100.3}, {-50, -50.3}, {50, 50.3},
      {-25, -25.3}, {25, 25.3},     {-12, -12.3}, {12, 12.3},   {-6, -6.3},
      {6, 6.3},     {-3, -3.3},     {3, 3.3},     {-1, -1.3},   {1, 1.3}};
  s21::map<int, double> s21map_2 = {};
  s21map_2.insert({0, 0.3});
  s21map_2.insert({-100, -100.3});
  s21map_2.insert({100, 100.3});
  s21map_2.insert({-50, -50.3});
  s21map_2.insert({50, 50.3});
  s21map_2.insert({-25, -25.3});
  s21map_2.insert({25, 25.3});
  s21map_2.insert({-12, -12.3});
  s21map_2.insert({12, 12.3});
  s21map_2.insert({-6, -6.3});
  s21map_2.insert({6, 6.3});
  s21map_2.insert({-3, -3.3});
  s21map_2.insert({3, 3.3});
  s21map_2.insert({-1, -1.3});
  s21map_2.insert({1, 1.3});
  compare_s21_std_map(s21map_1, s21map_2);
}

TEST(map, insert4) {
  std::map<int, double> s21map_1 = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                    {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                    {75, 75.3}};
  s21::map<int, double> s21map_2 = {};
  s21map_2.insert({0, 0.3});
  s21map_2.insert({-100, -100.3});
  s21map_2.insert({100, 100.3});
  s21map_2.insert({-50, -50.3});
  s21map_2.insert({50, 50.3});
  s21map_2.insert({-75, -75.3});
  s21map_2.insert({75, 75.3});
  compare_s21_std_map(s21map_1, s21map_2);
}

TEST(map, insert_or_assign1) {
  s21::map<int, double> s21map_1 = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                    {4, 4.3}, {5, 5.3}, {6, 6.3},
                                    {7, 7.3}, {8, 8.3}, {9, 9.3}};
  s21::map<int, double> s21map_2 = {{1, 1.5}, {2, 2.5}, {3, 3.5},
                                    {4, 4.3}, {5, 5.3}, {6, 6.5},
                                    {7, 7.5}, {8, 8.5}, {9, 9.5}};
  s21::map<int, double> s21map_target = {};
  s21map_target.insert_or_assign(1, 1.3);
  s21map_target.insert_or_assign(2, 2.3);
  s21map_target.insert_or_assign(3, 3.3);
  s21map_target.insert_or_assign(4, 4.3);
  s21map_target.insert_or_assign(5, 5.3);
  s21map_target.insert_or_assign(6, 6.3);
  s21map_target.insert_or_assign(7, 7.3);
  s21map_target.insert_or_assign(8, 8.3);
  s21map_target.insert_or_assign(9, 9.3);
  compare_s21_s21_map(s21map_1, s21map_target);
  s21map_target.insert_or_assign(1, 1.5);
  s21map_target.insert_or_assign(2, 2.5);
  s21map_target.insert_or_assign(3, 3.5);
  s21map_target.insert_or_assign(4, 4.5);
  s21map_target.insert_or_assign(5, 5.3);
  s21map_target.insert_or_assign(6, 6.5);
  s21map_target.insert_or_assign(7, 7.5);
  s21map_target.insert_or_assign(8, 8.5);
  s21map_target.insert_or_assign(9, 9.5);
  compare_s21_s21_map(s21map_1, s21map_target);
}

TEST(map, erase1) {
  s21::map<int, double> s21map_1 = {};
  s21::map<int, double> s21map_2 = {{1, 1.3}};
  s21map_2.erase(s21map_2.begin());
  compare_s21_s21_map(s21map_1, s21map_2);
}

TEST(map, erase2) {
  s21::map<int, double> s21map_1 = {};
  s21::map<int, double> s21map_2 = {};
  s21map_2.erase(s21map_2.begin());
  compare_s21_s21_map(s21map_1, s21map_2);
}

TEST(map, erase3) {
  std::map<int, double> stdmap = {
      {1, 1.3}, {2, 2.3}, {4, 4.3}, {5, 5.3}, {6, 6.3}};
  s21::map<int, double> s21map = {{1, 1.3}, {2, 2.3}, {3, 3.3},
                                  {4, 4.3}, {5, 5.3}, {6, 6.3}};
  auto i = s21map.begin();
  i++;
  i++;
  s21map.erase(i);
  compare_s21_std_map(stdmap, s21map);
}

TEST(map, at1) {
  std::map<int, double> stdmap = {
      {0, 0.3},     {-100, -100.3}, {100, 100.3}, {-50, -50.3}, {50, 50.3},
      {-25, -25.3}, {25, 25.3},     {-12, -12.3}, {12, 12.3},   {-6, -6.3},
      {6, 6.3},     {-3, -3.3},     {3, 3.3},     {-1, -1.3},   {1, 1.3}};
  s21::map<int, double> s21map = {
      {0, 0.3},     {-100, -100.3}, {100, 100.3}, {-50, -50.3}, {50, 50.3},
      {-25, -25.3}, {25, 25.3},     {-12, -12.3}, {12, 12.3},   {-6, -6.3},
      {6, 6.3},     {-3, -3.3},     {3, 3.3},     {-1, -1.3},   {1, 1.3}};
  ASSERT_EQ(stdmap.at(-100), s21map.at(-100));
  ASSERT_EQ(stdmap.at(50), s21map.at(50));
  ASSERT_EQ(stdmap.at(-25), s21map.at(-25));
  ASSERT_EQ(stdmap.at(12), s21map.at(12));
  ASSERT_EQ(stdmap.at(-6), s21map.at(-6));
  ASSERT_EQ(stdmap.at(3), s21map.at(3));
  ASSERT_EQ(stdmap.at(-1), s21map.at(-1));
  ASSERT_EQ(stdmap.at(0), s21map.at(0));
}

TEST(map, at2) {
  std::map<int, double> stdmap = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                  {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                  {75, 75.3}};
  s21::map<int, double> s21map = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                  {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                  {75, 75.3}};
  ASSERT_EQ(stdmap.at(-100), s21map.at(-100));
  ASSERT_EQ(stdmap.at(50), s21map.at(50));
  ASSERT_EQ(stdmap.at(-75), s21map.at(-75));
  ASSERT_EQ(stdmap.at(0), s21map.at(0));
}

TEST(map, at3) {
  s21::map<int, double> s21map = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                  {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                  {75, 75.3}};
  ASSERT_ANY_THROW(s21map.at(25));
  EXPECT_ANY_THROW(s21map.at(-25));
  EXPECT_ANY_THROW(s21map.at(10));
}

TEST(map, contains1) {
  s21::map<int, double> s21map = {
      {0, 0.3},     {-100, -100.3}, {100, 100.3}, {-50, -50.3}, {50, 50.3},
      {-25, -25.3}, {25, 25.3},     {-12, -12.3}, {12, 12.3},   {-6, -6.3},
      {6, 6.3},     {-3, -3.3},     {3, 3.3},     {-1, -1.3},   {1, 1.3}};
  ASSERT_EQ(s21map.contains(-100), true);
  ASSERT_EQ(s21map.contains(100), true);
  ASSERT_EQ(s21map.contains(-50), true);
  ASSERT_EQ(s21map.contains(50), true);
  ASSERT_EQ(s21map.contains(-25), true);
  ASSERT_EQ(s21map.contains(25), true);
  ASSERT_EQ(s21map.contains(-12), true);
  ASSERT_EQ(s21map.contains(12), true);
  ASSERT_EQ(s21map.contains(-6), true);
  ASSERT_EQ(s21map.contains(6), true);
  ASSERT_EQ(s21map.contains(-3), true);
  ASSERT_EQ(s21map.contains(3), true);
  ASSERT_EQ(s21map.contains(-1), true);
  ASSERT_EQ(s21map.contains(1), true);
  ASSERT_EQ(s21map.contains(0), true);
}

TEST(map, contains2) {
  s21::map<int, double> s21map = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                  {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                  {75, 75.3}};
  ASSERT_EQ(s21map.contains(-100), true);
  ASSERT_EQ(s21map.contains(100), true);
  ASSERT_EQ(s21map.contains(-50), true);
  ASSERT_EQ(s21map.contains(50), true);
  ASSERT_EQ(s21map.contains(-75), true);
  ASSERT_EQ(s21map.contains(75), true);
  ASSERT_EQ(s21map.contains(0), true);
}

TEST(map, contains3) {
  s21::map<int, double> s21map = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                  {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                  {75, 75.3}};
  ASSERT_EQ(s21map.contains(0), true);
  ASSERT_EQ(s21map.contains(100), true);
  ASSERT_EQ(s21map.contains(-100), true);
  ASSERT_EQ(s21map.contains(11), false);
  ASSERT_EQ(s21map.contains(-1000), false);
  ASSERT_EQ(s21map.contains(1000), false);
}

TEST(map, insert_many1) {
  s21::map<int, double> s21map_1 = {{1, 1.3}};
  s21::map<int, double> s21map_2 = {};
  auto res = s21map_2.insert_many(std::pair{1, 1.3});
  compare_s21_s21_map(s21map_1, s21map_2);
  ASSERT_TRUE(res[0].first->first == 1);
  ASSERT_TRUE(res[0].first->second == 1.3);
}

TEST(map, insert_many2) {
  std::map<int, double> s21map_1 = {{0, 0.3},     {-100, -100.3}, {100, 100.3},
                                    {-50, -50.3}, {50, 50.3},     {-75, -75.3},
                                    {75, 75.3}};
  s21::map<int, double> s21map_2 = {};
  auto res = s21map_2.insert_many(std::pair{0, 0.3}, std::pair{-100, -100.3},
                                  std::pair{100, 100.3}, std::pair{-50, -50.3},
                                  std::pair{50, 50.3}, std::pair{-75, -75.3},
                                  std::pair{75, 75.3});
  compare_s21_std_map(s21map_1, s21map_2);
  std::vector<std::pair<int, double>> req = {
      std::pair{0, 0.3},     std::pair{-100, -100.3}, std::pair{100, 100.3},
      std::pair{-50, -50.3}, std::pair{50, 50.3},     std::pair{-75, -75.3},
      std::pair{75, 75.3}};
  for (size_t i = 0; i < req.size(); ++i)
    if (res[i].second) {
      ASSERT_TRUE(res[i].first->first == req[i].first);
      ASSERT_TRUE(res[i].first->second == req[i].second);
    }
}
