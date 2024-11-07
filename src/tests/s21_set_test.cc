#include "../s21_containers/set/s21_set.h"

#include <gtest/gtest.h>

#include <set>

#include "s21_test.h"

TEST(set, ConstructorDefaultSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
}

TEST(set, ConstructorInitializerSet) {
  s21::set<char> my_set{'x', 'b', 'z', 'y'};
  std::set<char> orig_set{'x', 'b', 'z', 'y'};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorInitializer2Set) {
  s21::set<char> my_set{};
  std::set<char> orig_set{};
  EXPECT_EQ(my_set.size(), orig_set.size());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorCopySet) {
  s21::set<int> my_set{1, 2, 3, 4, 5};
  std::set<int> orig_set{1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = my_set;
  std::set<int> orig_set_copy = orig_set;
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, ConstructorMoveSet) {
  s21::set<int> my_set{1, 2, 3, 4, 5};
  std::set<int> orig_set{1, 2, 3, 4, 5};
  s21::set<int> my_set_copy = std::move(my_set);
  std::set<int> orig_set_copy = std::move(orig_set);
  EXPECT_EQ(my_set.size(), orig_set.size());
  EXPECT_EQ(my_set_copy.size(), orig_set_copy.size());
  auto my_it = my_set_copy.begin();
  auto orig_it = orig_set_copy.begin();
  for (; my_it != my_set_copy.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SetIteratorsSet) {
  s21::set<std::string> my_set{"This", "is", "my", "set"};
  std::set<std::string> orig_set{"This", "is", "my", "set"};
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  EXPECT_TRUE(*orig_it == *my_it);
  my_it = my_set.end();
  orig_it = orig_set.end();
  --my_it;
  --orig_it;
}

TEST(set, CapacitySet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('b');
  orig_empty_set.insert('c');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, ClearSet) {
  s21::set<char> my_empty_set;
  std::set<char> orig_empty_set;
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.insert('a');
  orig_empty_set.insert('b');
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
  my_empty_set.clear();
  orig_empty_set.clear();
  EXPECT_EQ(my_empty_set.empty(), orig_empty_set.empty());
  EXPECT_EQ(my_empty_set.size(), orig_empty_set.size());
}

TEST(set, EraseSet) {
  s21::set<int> my_set{5, 4, 3, 2, 7, 8, 9};
  std::set<int> orig_set{5, 4, 3, 2, 7, 8, 9};
  my_set.erase(my_set.begin());
  orig_set.erase(orig_set.begin());
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
}

TEST(set, SwapSet) {
  s21::set<int> my_set{1};
  s21::set<int> my_swap_set{3, 4, 5};

  my_set.swap(my_swap_set);
  EXPECT_EQ(my_set.size(), 3UL);
  EXPECT_EQ(my_swap_set.size(), 1UL);
  EXPECT_EQ(*my_set.begin(), 3);
  EXPECT_EQ(*my_swap_set.begin(), 1);
}

TEST(set, MergeSet) {
  s21::set<int> my_set{1};
  s21::set<int> my_merge_set{3, 4, 5};
  my_set.merge(my_merge_set);

  std::set<int> orig_set{1};
  std::set<int> orig_merge_set{3, 4, 5};
  orig_set.merge(orig_merge_set);
  auto my_it = my_set.begin();
  auto orig_it = orig_set.begin();
  for (; my_it != my_set.end(); ++my_it, ++orig_it) {
    EXPECT_TRUE(*orig_it == *my_it);
  }
  EXPECT_EQ(orig_set.size(), my_set.size());
  EXPECT_EQ(my_merge_set.size(), orig_merge_set.size());
}

TEST(set, FindSet) {
  s21::set<double> my_set{2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set{2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  auto my_it = my_set.find(2.4);
  auto orig_it = orig_set.find(2.4);
  EXPECT_TRUE(*orig_it == *my_it);
}

TEST(set, ContainsSet) {
  s21::set<double> my_set{2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  s21::set<double> orig_set{2.1, 2.2, 2.3, 2.4, 2.5, 2.6};
  EXPECT_EQ(my_set.contains(2), orig_set.contains(2));
  EXPECT_EQ(my_set.contains(2.1), orig_set.contains(2.1));
}

template <class Key>
void compare_s21_std_set(s21::set<Key> s21set, std::set<Key> stdset) {
  ASSERT_EQ(s21set.size(), stdset.size());
  auto s21i = s21set.begin();
  auto stdi = stdset.begin();
  for (; s21i != s21set.end(); s21i++, stdi++) ASSERT_EQ(*s21i, *stdi);
}

template <class Key>
void compare_s21_std_set(std::set<Key> stdset, s21::set<Key> s21set) {
  ASSERT_EQ(s21set.size(), stdset.size());
  auto s21i = s21set.begin();
  auto stdi = stdset.begin();
  for (; s21i != s21set.end(); s21i++, stdi++) ASSERT_EQ(*s21i, *stdi);
}

template <class Key>
void compare_s21_s21_set(s21::set<Key> s21set_1, s21::set<Key> s21set_2) {
  ASSERT_EQ(s21set_1.size(), s21set_2.size());
  auto s21_i_1 = s21set_1.begin();
  auto s21_i_2 = s21set_2.begin();
  for (; s21_i_1 != s21set_1.end(); s21_i_1++, s21_i_2++)
    ASSERT_EQ(*s21_i_1, *s21_i_2);
}

TEST(set, size1) {
  s21::set<int> s21set = {};
  ASSERT_EQ(s21set.size(), 0UL);
}

TEST(set, size2) {
  s21::set<int> s21set = {1};
  ASSERT_EQ(s21set.size(), 1UL);
}

TEST(set, size3) {
  s21::set<int> s21set = {1, 2};
  ASSERT_EQ(s21set.size(), 2UL);
}

TEST(set, simple1) {
  s21::set<int> s21set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> stdset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_set(stdset, s21set);
}

TEST(set, simple2) {
  s21::set<int> s21set = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> stdset = {1, 2, 3, 4, 5, 6, 7, 8, 9, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_set(stdset, s21set);
}

TEST(set, simple3) {
  s21::set<int> s21set = {3, 1, 4, 7, 8, 9, 5, 6, 2};
  std::set<int> stdset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_set(stdset, s21set);
}

TEST(set, simple4) {
  s21::set<int> s21set_orig = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::set<int> s21set_target = s21set_orig;
  compare_s21_s21_set(s21set_target, s21set_orig);
}

TEST(set, simple5) {
  s21::set<int> s21set = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::set<int> stdset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_set(stdset, s21set);
}

TEST(set, empty1) {
  s21::set<int> s21set = {};
  ASSERT_EQ(s21set.empty(), true);
}

TEST(set, empty2) {
  s21::set<int> s21set = {1};
  ASSERT_EQ(s21set.empty(), false);
}

TEST(set, clear) {
  s21::set<int> s21set = {1, 2, 3};
  s21set.clear();
  ASSERT_EQ(s21set.empty(), true);
}

TEST(set, swap) {
  s21::set<int> s21set_1 = {5, 3};
  s21::set<int> s21set_2 = {7, 8, 9};
  std::set<int> stdset_1 = {5, 3};
  std::set<int> stdset_2 = {7, 8, 9};
  stdset_1.swap(stdset_2);
  s21set_1.swap(s21set_2);
  compare_s21_std_set(stdset_1, s21set_1);
  compare_s21_std_set(stdset_2, s21set_2);
}

TEST(set, merge1) {
  s21::set<int> s21set_1 = {5, 3};
  s21::set<int> s21set_2 = {7, 8, 9};
  std::set<int> stdset = {5, 3, 7, 8, 9};
  s21set_1.merge(s21set_2);
  compare_s21_std_set(s21set_1, stdset);
}

TEST(set, merge2) {
  s21::set<int> s21set_1 = {5, 3};
  s21::set<int> s21set_2 = {7, 8, 9};
  std::set<int> stdset = {5, 3, 7, 8, 9};
  s21set_1.merge(s21set_2);
  compare_s21_std_set(s21set_1, stdset);
}

TEST(set, insert1) {
  s21::set<int> s21set_1 = {1};
  s21::set<int> s21set_2 = {};
  auto pair = s21set_2.insert(1);
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(*(pair.first), 1);
  pair = s21set_2.insert(1);
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(*(pair.first), 1);
  compare_s21_s21_set(s21set_1, s21set_2);
}

TEST(set, insert2) {
  s21::set<int> s21set_1 = {1, 2, 3, 4, 5, 6, 7};
  s21::set<int> s21set_2 = {2, 4, 7};
  s21set_2.insert(3);
  s21set_2.insert(4);
  s21set_2.insert(3);
  s21set_2.insert(2);
  s21set_2.insert(5);
  s21set_2.insert(7);
  s21set_2.insert(6);
  auto pair = s21set_2.insert(1);
  ASSERT_EQ(pair.second, true);
  ASSERT_EQ(*(pair.first), 1);
  pair = s21set_2.insert(1);
  ASSERT_EQ(pair.second, false);
  ASSERT_EQ(*(pair.first), 1);
  compare_s21_s21_set(s21set_1, s21set_2);
}

TEST(set, insert3) {
  std::set<int> s21set_1 = {0,  -100, 100, -50, 50, -25, 25, -12,
                            12, -6,   6,   -3,  3,  -1,  1};
  s21::set<int> s21set_2 = {};
  s21set_2.insert(0);
  s21set_2.insert(-100);
  s21set_2.insert(100);
  s21set_2.insert(-50);
  s21set_2.insert(50);
  s21set_2.insert(-25);
  s21set_2.insert(25);
  s21set_2.insert(-12);
  s21set_2.insert(12);
  s21set_2.insert(-6);
  s21set_2.insert(6);
  s21set_2.insert(-3);
  s21set_2.insert(3);
  s21set_2.insert(-1);
  s21set_2.insert(1);
  compare_s21_std_set(s21set_1, s21set_2);
}

TEST(set, insert4) {
  std::set<int> s21set_1 = {0, -100, 100, -50, 50, -75, 75};
  s21::set<int> s21set_2 = {};
  s21set_2.insert(0);
  s21set_2.insert(-100);
  s21set_2.insert(100);
  s21set_2.insert(-50);
  s21set_2.insert(50);
  s21set_2.insert(-75);
  s21set_2.insert(75);
  compare_s21_std_set(s21set_1, s21set_2);
}

TEST(set, erase1) {
  s21::set<int> s21set_1 = {};
  s21::set<int> s21set_2 = {1};
  s21set_2.erase(s21set_2.begin());
  compare_s21_s21_set(s21set_1, s21set_2);
}

TEST(set, erase2) {
  s21::set<int> s21set_1 = {};
  s21::set<int> s21set_2 = {};
  s21set_2.erase(s21set_2.begin());
  compare_s21_s21_set(s21set_1, s21set_2);
}

TEST(set, erase3) {
  std::set<int> stdset = {1, 2, 4, 5, 6};
  s21::set<int> s21set = {1, 2, 3, 4, 5, 6};
  auto i = s21set.begin();
  i++;
  i++;
  s21set.erase(i);
  compare_s21_std_set(stdset, s21set);
}

TEST(set, find1) {
  std::set<int> stdset = {0,  -100, 100, -50, 50, -25, 25, -12,
                          12, -6,   6,   -3,  3,  -1,  1};
  s21::set<int> s21set = {0,  -100, 100, -50, 50, -25, 25, -12,
                          12, -6,   6,   -3,  3,  -1,  1};
  ASSERT_EQ(*(stdset.find(-100)), *(s21set.find(-100)));
  ASSERT_EQ(*(stdset.find(50)), *(s21set.find(50)));
  ASSERT_EQ(*(stdset.find(-25)), *(s21set.find(-25)));
  ASSERT_EQ(*(stdset.find(12)), *(s21set.find(12)));
  ASSERT_EQ(*(stdset.find(-6)), *(s21set.find(-6)));
  ASSERT_EQ(*(stdset.find(3)), *(s21set.find(3)));
  ASSERT_EQ(*(stdset.find(-1)), *(s21set.find(-1)));
  ASSERT_EQ(*(stdset.find(0)), *(s21set.find(0)));
}

TEST(set, find2) {
  std::set<int> stdset = {0, -100, 100, -50, 50, -75, 75};
  s21::set<int> s21set = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(*(stdset.find(-100)), *(s21set.find(-100)));
  ASSERT_EQ(*(stdset.find(50)), *(s21set.find(50)));
  ASSERT_EQ(*(stdset.find(-75)), *(s21set.find(-75)));
  ASSERT_EQ(*(stdset.find(0)), *(s21set.find(0)));
}

TEST(set, find3) {
  s21::set<int> s21set = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(s21set.find(25) == s21set.end(), true);
  ASSERT_EQ(s21set.find(-25) == s21set.end(), true);
  ASSERT_EQ(s21set.find(10) == s21set.end(), true);
}

TEST(set, contains1) {
  s21::set<int> s21set = {0,  -100, 100, -50, 50, -25, 25, -12,
                          12, -6,   6,   -3,  3,  -1,  1};
  ASSERT_EQ(s21set.contains(-100), true);
  ASSERT_EQ(s21set.contains(100), true);
  ASSERT_EQ(s21set.contains(-50), true);
  ASSERT_EQ(s21set.contains(50), true);
  ASSERT_EQ(s21set.contains(-25), true);
  ASSERT_EQ(s21set.contains(25), true);
  ASSERT_EQ(s21set.contains(-12), true);
  ASSERT_EQ(s21set.contains(12), true);
  ASSERT_EQ(s21set.contains(-6), true);
  ASSERT_EQ(s21set.contains(6), true);
  ASSERT_EQ(s21set.contains(-3), true);
  ASSERT_EQ(s21set.contains(3), true);
  ASSERT_EQ(s21set.contains(-1), true);
  ASSERT_EQ(s21set.contains(1), true);
  ASSERT_EQ(s21set.contains(0), true);
}

TEST(set, contains2) {
  s21::set<int> s21set = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(s21set.contains(-100), true);
  ASSERT_EQ(s21set.contains(100), true);
  ASSERT_EQ(s21set.contains(-50), true);
  ASSERT_EQ(s21set.contains(50), true);
  ASSERT_EQ(s21set.contains(-75), true);
  ASSERT_EQ(s21set.contains(75), true);
  ASSERT_EQ(s21set.contains(0), true);
}

TEST(set, contains3) {
  s21::set<int> s21set = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(s21set.contains(0), true);
  ASSERT_EQ(s21set.contains(100), true);
  ASSERT_EQ(s21set.contains(-100), true);
  ASSERT_EQ(s21set.contains(11), false);
  ASSERT_EQ(s21set.contains(-1000), false);
  ASSERT_EQ(s21set.contains(1000), false);
}

TEST(set, insert_many1) {
  s21::set<int> s21set_1 = {1};
  s21::set<int> s21set_2 = {};
  auto res = s21set_2.insert_many(1);
  compare_s21_s21_set(s21set_1, s21set_2);
  ASSERT_TRUE(*(res[0].first) == 1);
}

TEST(set, insert_many2) {
  std::set<int> s21set_1 = {0, -100, 100, -50, 50, -75, 75};
  s21::set<int> s21set_2 = {};
  auto res = s21set_2.insert_many(0, -100, 100, -50, 50, -75, 75);
  compare_s21_std_set(s21set_1, s21set_2);
  std::vector req = {0, -100, 100, -50, 50, -75, 75};
  for (size_t i = 0; i < req.size(); ++i) {
    if (res[i].second) {
      ASSERT_TRUE(*(res[i].first) == req[i]);
    }
  }
}