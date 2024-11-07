#include "../s21_containers/multiset/s21_multiset.h"

#include <gtest/gtest.h>

#include <set>

#include "s21_test.h"

class multisetTest : public ::testing::Test {
 protected:
  s21::multiset<int> multiset;
  s21::multiset<int> multiset1;
  s21::multiset<int> multiset2;
};

TEST_F(multisetTest, EmptymultisetBegin) {
  auto iterator = multiset.begin();

  EXPECT_EQ(iterator, multiset.end());
}

TEST_F(multisetTest, NonEmptymultiset) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  auto iterator = multiset.begin();

  EXPECT_NE(iterator, multiset.end());

  EXPECT_EQ(*iterator, 5);
}

TEST_F(multisetTest, IncrementEmptymultiset) {
  auto iterator = multiset.begin();

  ++iterator;

  EXPECT_EQ(iterator, multiset.end());
}

TEST_F(multisetTest, IncrementNonEmptymultiset) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);
  auto iterator = multiset.begin();

  iterator++;

  EXPECT_NE(iterator, multiset.end());
  EXPECT_EQ(*iterator, 10);
}

TEST_F(multisetTest, DecrementEmptymultiset) {
  auto iterator = multiset.end();

  iterator--;

  EXPECT_EQ(iterator, multiset.end());
}

TEST_F(multisetTest, IncrementMultipleLevels) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);
  multiset.insert(20);
  multiset.insert(25);
  multiset.insert(30);
  multiset.insert(35);
  multiset.insert(40);
  multiset.insert(45);
  multiset.insert(50);
  auto iterator = multiset.begin();

  ++iterator;
  ++iterator;
  ++iterator;

  EXPECT_NE(iterator, multiset.end());
  EXPECT_EQ(*iterator, 20);
}

TEST_F(multisetTest, IncrementEdgeValues) {
  multiset.insert(std::numeric_limits<int>::min());
  multiset.insert(std::numeric_limits<int>::max());
  auto iterator = multiset.begin();

  ++iterator;

  EXPECT_NE(iterator, multiset.end());
  EXPECT_EQ(*iterator, std::numeric_limits<int>::max());
}

TEST_F(multisetTest, EmptymultisetEmpty) { EXPECT_TRUE(multiset.empty()); }

TEST_F(multisetTest, NonEmptymultisetEmpty) {
  multiset.insert(5);

  EXPECT_FALSE(multiset.empty());
}

TEST_F(multisetTest, EmptymultisetSize) {
  EXPECT_TRUE(multiset.empty());
  EXPECT_EQ(multiset.size(), 0UL);
}

TEST_F(multisetTest, SizeOne) {
  multiset.insert(5);

  EXPECT_FALSE(multiset.empty());
  EXPECT_EQ(multiset.size(), 1UL);
}

TEST_F(multisetTest, SizeMultiple) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  EXPECT_FALSE(multiset.empty());
  EXPECT_EQ(multiset.size(), 3UL);
}

TEST_F(multisetTest, ClearEmptymultiset) {
  multiset.clear();

  EXPECT_TRUE(multiset.empty());
}

TEST_F(multisetTest, ClearNonEmptymultiset) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  multiset.clear();

  EXPECT_TRUE(multiset.empty());
}

TEST_F(multisetTest, ExistingValues) {
  int value1 = 5;
  int value2 = 10;
  int value3 = 15;

  multiset.insert(value1);
  multiset.insert(value2);
  multiset.insert(value3);

  EXPECT_EQ(multiset.size(), 3UL);
}

TEST_F(multisetTest, EraseEmptymultiset) {
  s21::multiset<int>::iterator pos = multiset.begin();

  multiset.erase(pos);

  EXPECT_TRUE(multiset.empty());
}

TEST_F(multisetTest, EraseOneElement) {
  multiset.insert(5);
  s21::multiset<int>::iterator pos = multiset.begin();

  multiset.erase(pos);

  EXPECT_TRUE(multiset.empty());
}

TEST_F(multisetTest, EraseMultipleElements) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);
  s21::multiset<int>::iterator pos = multiset.find(10);

  multiset.erase(pos);

  EXPECT_EQ(multiset.size(), 2UL);
  EXPECT_FALSE(multiset.contains(10));
  EXPECT_TRUE(multiset.contains(15));
}

TEST_F(multisetTest, SwapEmptymultisets) {
  multiset1.swap(multiset2);

  EXPECT_TRUE(multiset1.empty());
  EXPECT_TRUE(multiset2.empty());
}

TEST_F(multisetTest, SwapmultisetsOneElement) {
  multiset1.insert(5);
  multiset2.insert(10);

  multiset1.swap(multiset2);

  EXPECT_EQ(multiset1.size(), 1UL);
  EXPECT_EQ(*multiset1.begin(), 10);
  EXPECT_EQ(multiset2.size(), 1UL);
  EXPECT_EQ(*multiset2.begin(), 5);
}

TEST_F(multisetTest, SwapmultisetsMultipleElements) {
  multiset1.insert(5);
  multiset1.insert(10);
  multiset1.insert(15);
  multiset2.insert(20);
  multiset2.insert(25);
  multiset2.insert(30);

  multiset1.swap(multiset2);

  EXPECT_EQ(multiset1.size(), 3UL);
  EXPECT_EQ(*multiset1.begin(), 20);
  EXPECT_EQ(*(++multiset1.begin()), 25);
  EXPECT_EQ(*(++(++multiset1.begin())), 30);
  EXPECT_EQ(multiset2.size(), 3UL);
  EXPECT_EQ(*multiset2.begin(), 5);
  EXPECT_EQ(*(++multiset2.begin()), 10);
  EXPECT_EQ(*(++(++multiset2.begin())), 15);
}

TEST_F(multisetTest, MergeEmptymultisets) {
  multiset1.merge(multiset2);

  EXPECT_TRUE(multiset1.empty());
  EXPECT_TRUE(multiset2.empty());
}

TEST_F(multisetTest, MergemultisetsOneElement) {
  multiset1.insert(5);
  multiset2.insert(10);

  multiset1.merge(multiset2);

  EXPECT_EQ(multiset1.size(), 2UL);
  EXPECT_TRUE(multiset1.contains(5));
  EXPECT_TRUE(multiset1.contains(10));
  EXPECT_TRUE(multiset2.empty());
}

TEST_F(multisetTest, MergemultisetsMultipleElements) {
  multiset1.insert(5);
  multiset1.insert(10);
  multiset1.insert(15);
  multiset2.insert(20);
  multiset2.insert(25);
  multiset2.insert(30);

  multiset1.merge(multiset2);

  EXPECT_EQ(multiset1.size(), 6UL);
  EXPECT_TRUE(multiset1.contains(5));
  EXPECT_TRUE(multiset1.contains(10));
  EXPECT_TRUE(multiset1.contains(15));
  EXPECT_TRUE(multiset1.contains(20));
  EXPECT_TRUE(multiset1.contains(25));
  EXPECT_TRUE(multiset1.contains(30));
  EXPECT_TRUE(multiset2.empty());
}

TEST_F(multisetTest, MergemultisetsOverlappingElements) {
  s21::multiset<int> multiset1;
  s21::multiset<int> multiset2;
  multiset1.insert(5);
  multiset1.insert(10);
  multiset1.insert(15);
  multiset2.insert(10);
  multiset2.insert(20);
  multiset2.insert(25);

  multiset1.merge(multiset2);

  EXPECT_EQ(multiset1.size(), 5UL);
  EXPECT_TRUE(multiset1.contains(5));
  EXPECT_TRUE(multiset1.contains(10));
  EXPECT_TRUE(multiset1.contains(15));
  EXPECT_TRUE(multiset1.contains(20));
  EXPECT_TRUE(multiset1.contains(25));
  EXPECT_EQ(multiset2.size(), 1UL);
  EXPECT_TRUE(multiset2.contains(10));
}

TEST_F(multisetTest, FindExistingKey) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  auto it = multiset.find(10);

  EXPECT_NE(it, multiset.end());
  EXPECT_EQ(*it, 10);
}

TEST_F(multisetTest, FindNonExistingKey) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  auto it = multiset.find(20);

  EXPECT_EQ(it, multiset.end());
}

TEST_F(multisetTest, ContainsExistingKey) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  bool result = multiset.contains(10);

  EXPECT_TRUE(result);
}

TEST_F(multisetTest, ContainsNonExistingKey) {
  multiset.insert(5);
  multiset.insert(10);
  multiset.insert(15);

  bool result = multiset.contains(20);

  EXPECT_FALSE(result);
}

template <class Key>
void compare_s21_std_multiset(s21::multiset<Key> s21multiset,
                              std::multiset<Key> stdmultiset) {
  ASSERT_EQ(s21multiset.size(), stdmultiset.size());
  auto s21i = s21multiset.begin();
  auto stdi = stdmultiset.begin();
  for (; s21i != s21multiset.end(); s21i++, stdi++) ASSERT_EQ(*s21i, *stdi);
}

template <class Key>
void compare_s21_std_multiset(std::multiset<Key> stdmultiset,
                              s21::multiset<Key> s21multiset) {
  ASSERT_EQ(s21multiset.size(), stdmultiset.size());
  auto s21i = s21multiset.begin();
  auto stdi = stdmultiset.begin();
  for (; s21i != s21multiset.end(); s21i++, stdi++) ASSERT_EQ(*s21i, *stdi);
}

template <class Key>
void compare_s21_s21_multiset(s21::multiset<Key> s21multiset_1,
                              s21::multiset<Key> s21multiset_2) {
  ASSERT_EQ(s21multiset_1.size(), s21multiset_2.size());
  auto s21_i_1 = s21multiset_1.begin();
  auto s21_i_2 = s21multiset_2.begin();
  for (; s21_i_1 != s21multiset_1.end(); s21_i_1++, s21_i_2++)
    ASSERT_EQ(*s21_i_1, *s21_i_2);
}

TEST(multiset, size1) {
  s21::multiset<int> s21multiset = {};
  ASSERT_EQ(s21multiset.size(), 0UL);
}

TEST(multiset, size2) {
  s21::multiset<int> s21multiset = {1};
  ASSERT_EQ(s21multiset.size(), 1UL);
}

TEST(multiset, size3) {
  s21::multiset<int> s21multiset = {1, 2};
  ASSERT_EQ(s21multiset.size(), 2UL);
}

TEST(multiset, simple1) {
  s21::multiset<int> s21multiset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::multiset<int> stdmultiset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_multiset(stdmultiset, s21multiset);
}

TEST(multiset, simple2) {
  s21::multiset<int> s21multiset = {1, 2, 3, 4, 5, 6, 7, 8, 9,
                                    1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::multiset<int> stdmultiset = {1, 2, 3, 4, 5, 6, 7, 8, 9,
                                    1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_multiset(stdmultiset, s21multiset);
}

TEST(multiset, simple3) {
  s21::multiset<int> s21multiset = {3, 1, 4, 7, 8, 9, 5, 6, 2};
  std::multiset<int> stdmultiset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_multiset(stdmultiset, s21multiset);
}

TEST(multiset, simple4) {
  s21::multiset<int> s21multiset_orig = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  s21::multiset<int> s21multiset_target = s21multiset_orig;
  compare_s21_s21_multiset(s21multiset_target, s21multiset_orig);
}

TEST(multiset, simple5) {
  s21::multiset<int> s21multiset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::multiset<int> stdmultiset = {1, 2, 3, 4, 5, 6, 7, 8, 9};
  compare_s21_std_multiset(stdmultiset, s21multiset);
}

TEST(multiset, empty1) {
  s21::multiset<int> s21multiset = {};
  ASSERT_EQ(s21multiset.empty(), true);
}

TEST(multiset, empty2) {
  s21::multiset<int> s21multiset = {1};
  ASSERT_EQ(s21multiset.empty(), false);
}

TEST(multiset, clear) {
  s21::multiset<int> s21multiset = {1, 2, 3};
  s21multiset.clear();
  ASSERT_EQ(s21multiset.empty(), true);
}

// TEST(multiset, max_size) {
//   s21::multiset<int> s21multiset = {};
//   std::multiset<int> stdmultiset = {};
//   std::cout << "s21 max_size: " << s21multiset.max_size() << std::endl
//             << "std max_size: " << stdmultiset.max_size() << std::endl;
//   ASSERT_EQ(s21multiset.empty(), true);
// }

TEST(multiset, swap) {
  s21::multiset<int> s21multiset_1 = {5, 3};
  s21::multiset<int> s21multiset_2 = {7, 8, 9};
  std::multiset<int> stdmultiset_1 = {5, 3};
  std::multiset<int> stdmultiset_2 = {7, 8, 9};
  stdmultiset_1.swap(stdmultiset_2);
  s21multiset_1.swap(s21multiset_2);
  compare_s21_std_multiset(stdmultiset_1, s21multiset_1);
  compare_s21_std_multiset(stdmultiset_2, s21multiset_2);
}

TEST(multiset, merge1) {
  s21::multiset<int> s21multiset_1 = {5, 3};
  s21::multiset<int> s21multiset_2 = {7, 8, 9};
  std::multiset<int> stdmultiset = {5, 3, 7, 8, 9};
  s21multiset_1.merge(s21multiset_2);
  compare_s21_std_multiset(s21multiset_1, stdmultiset);
}

TEST(multiset, merge2) {
  s21::multiset<int> s21multiset_1 = {5, 3};
  s21::multiset<int> s21multiset_2 = {7, 8, 9};
  std::multiset<int> stdmultiset = {5, 3, 7, 8, 9};
  s21multiset_1.merge(s21multiset_2);
  compare_s21_std_multiset(s21multiset_1, stdmultiset);
}

TEST(multiset, insert1) {
  s21::multiset<int> s21multiset_1 = {1};
  s21::multiset<int> s21multiset_2 = {};
  auto iter = s21multiset_2.insert(1);
  ASSERT_EQ(*(iter), 1);
  compare_s21_s21_multiset(s21multiset_1, s21multiset_2);
}

TEST(multiset, insert2) {
  s21::multiset<int> s21multiset_1 = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 7};
  s21::multiset<int> s21multiset_2 = {2, 4, 7};
  s21multiset_2.insert(3);
  s21multiset_2.insert(4);
  s21multiset_2.insert(3);
  s21multiset_2.insert(2);
  s21multiset_2.insert(5);
  s21multiset_2.insert(7);
  s21multiset_2.insert(6);
  auto iter = s21multiset_2.insert(1);
  ASSERT_EQ(*(iter), 1);
  iter = s21multiset_2.insert(1);
  ASSERT_EQ(*(iter), 1);
  compare_s21_s21_multiset(s21multiset_1, s21multiset_2);
}

TEST(multiset, insert3) {
  std::multiset<int> s21multiset_1 = {0,  -100, 100, -50, 50, -25, 25, -12,
                                      12, -6,   6,   -3,  3,  -1,  1};
  s21::multiset<int> s21multiset_2 = {};
  s21multiset_2.insert(0);
  s21multiset_2.insert(-100);
  s21multiset_2.insert(100);
  s21multiset_2.insert(-50);
  s21multiset_2.insert(50);
  s21multiset_2.insert(-25);
  s21multiset_2.insert(25);
  s21multiset_2.insert(-12);
  s21multiset_2.insert(12);
  s21multiset_2.insert(-6);
  s21multiset_2.insert(6);
  s21multiset_2.insert(-3);
  s21multiset_2.insert(3);
  s21multiset_2.insert(-1);
  s21multiset_2.insert(1);
  compare_s21_std_multiset(s21multiset_1, s21multiset_2);
}

TEST(multiset, insert4) {
  std::multiset<int> s21multiset_1 = {0, -100, 100, -50, 50, -75, 75};
  s21::multiset<int> s21multiset_2 = {};
  s21multiset_2.insert(0);
  s21multiset_2.insert(-100);
  s21multiset_2.insert(100);
  s21multiset_2.insert(-50);
  s21multiset_2.insert(50);
  s21multiset_2.insert(-75);
  s21multiset_2.insert(75);
  compare_s21_std_multiset(s21multiset_1, s21multiset_2);
}

TEST(multiset, erase1) {
  s21::multiset<int> s21multiset_1 = {};
  s21::multiset<int> s21multiset_2 = {1};
  s21multiset_2.erase(s21multiset_2.begin());
  compare_s21_s21_multiset(s21multiset_1, s21multiset_2);
}

TEST(multiset, erase2) {
  s21::multiset<int> s21multiset_1 = {};
  s21::multiset<int> s21multiset_2 = {};
  s21multiset_2.erase(s21multiset_2.begin());
  compare_s21_s21_multiset(s21multiset_1, s21multiset_2);
}

TEST(multiset, erase3) {
  std::multiset<int> stdmultiset = {1, 2, 4, 5, 6};
  s21::multiset<int> s21multiset = {1, 2, 3, 4, 5, 6};
  auto i = s21multiset.begin();
  i++;
  i++;
  s21multiset.erase(i);
  compare_s21_std_multiset(stdmultiset, s21multiset);
}

TEST(multiset, find1) {
  std::multiset<int> stdmultiset = {0,  -100, 100, -50, 50, -25, 25, -12,
                                    12, -6,   6,   -3,  3,  -1,  1};
  s21::multiset<int> s21multiset = {0,  -100, 100, -50, 50, -25, 25, -12,
                                    12, -6,   6,   -3,  3,  -1,  1};
  ASSERT_EQ(*(stdmultiset.find(-100)), *(s21multiset.find(-100)));
  ASSERT_EQ(*(stdmultiset.find(50)), *(s21multiset.find(50)));
  ASSERT_EQ(*(stdmultiset.find(-25)), *(s21multiset.find(-25)));
  ASSERT_EQ(*(stdmultiset.find(12)), *(s21multiset.find(12)));
  ASSERT_EQ(*(stdmultiset.find(-6)), *(s21multiset.find(-6)));
  ASSERT_EQ(*(stdmultiset.find(3)), *(s21multiset.find(3)));
  ASSERT_EQ(*(stdmultiset.find(-1)), *(s21multiset.find(-1)));
  ASSERT_EQ(*(stdmultiset.find(0)), *(s21multiset.find(0)));
}

TEST(multiset, find2) {
  std::multiset<int> stdmultiset = {0, -100, 100, -50, 50, -75, 75};
  s21::multiset<int> s21multiset = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(*(stdmultiset.find(-100)), *(s21multiset.find(-100)));
  ASSERT_EQ(*(stdmultiset.find(50)), *(s21multiset.find(50)));
  ASSERT_EQ(*(stdmultiset.find(-75)), *(s21multiset.find(-75)));
  ASSERT_EQ(*(stdmultiset.find(0)), *(s21multiset.find(0)));
}

TEST(multiset, find3) {
  s21::multiset<int> s21multiset = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(s21multiset.find(25) == s21multiset.end(), true);
  ASSERT_EQ(s21multiset.find(-25) == s21multiset.end(), true);
  ASSERT_EQ(s21multiset.find(10) == s21multiset.end(), true);
}

TEST(multiset, contains1) {
  s21::multiset<int> s21multiset = {0,  -100, 100, -50, 50, -25, 25, -12,
                                    12, -6,   6,   -3,  3,  -1,  1};
  ASSERT_EQ(s21multiset.contains(-100), true);
  ASSERT_EQ(s21multiset.contains(100), true);
  ASSERT_EQ(s21multiset.contains(-50), true);
  ASSERT_EQ(s21multiset.contains(50), true);
  ASSERT_EQ(s21multiset.contains(-25), true);
  ASSERT_EQ(s21multiset.contains(25), true);
  ASSERT_EQ(s21multiset.contains(-12), true);
  ASSERT_EQ(s21multiset.contains(12), true);
  ASSERT_EQ(s21multiset.contains(-6), true);
  ASSERT_EQ(s21multiset.contains(6), true);
  ASSERT_EQ(s21multiset.contains(-3), true);
  ASSERT_EQ(s21multiset.contains(3), true);
  ASSERT_EQ(s21multiset.contains(-1), true);
  ASSERT_EQ(s21multiset.contains(1), true);
  ASSERT_EQ(s21multiset.contains(0), true);
}

TEST(multiset, contains2) {
  s21::multiset<int> s21multiset = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(s21multiset.contains(-100), true);
  ASSERT_EQ(s21multiset.contains(100), true);
  ASSERT_EQ(s21multiset.contains(-50), true);
  ASSERT_EQ(s21multiset.contains(50), true);
  ASSERT_EQ(s21multiset.contains(-75), true);
  ASSERT_EQ(s21multiset.contains(75), true);
  ASSERT_EQ(s21multiset.contains(0), true);
}

TEST(multiset, contains3) {
  s21::multiset<int> s21multiset = {0, -100, 100, -50, 50, -75, 75};
  ASSERT_EQ(s21multiset.contains(0), true);
  ASSERT_EQ(s21multiset.contains(100), true);
  ASSERT_EQ(s21multiset.contains(-100), true);
  ASSERT_EQ(s21multiset.contains(11), false);
  ASSERT_EQ(s21multiset.contains(-1000), false);
  ASSERT_EQ(s21multiset.contains(1000), false);
}

TEST(multiset, lower_bound1) {
  s21::multiset<int> s21multiset = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter < key); ++iter)
    ;
  auto temp = s21multiset.lower_bound(key);
  ASSERT_FALSE(++iter == temp);
  ASSERT_TRUE(--iter == temp);
}

TEST(multiset, lower_bound2) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter < key); ++iter)
    ;
  ASSERT_TRUE(iter == s21multiset.lower_bound(key));
}

TEST(multiset, lower_bound3) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 9;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter < key); ++iter)
    ;
  ASSERT_TRUE(iter == s21multiset.lower_bound(key));
}

TEST(multiset, lower_bound4) {
  s21::multiset<int> s21multiset = {};
  int key = 2;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter < key); ++iter)
    ;
  ASSERT_TRUE(iter == s21multiset.lower_bound(key));
}

TEST(multiset, upper_bound1) {
  s21::multiset<int> s21multiset = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter <= key); ++iter)
    ;
  auto temp = s21multiset.upper_bound(key);
  ASSERT_FALSE(++iter == temp);
  ASSERT_TRUE(--iter == temp);
}

TEST(multiset, upper_bound2) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter <= key); ++iter)
    ;
  ASSERT_TRUE(iter == s21multiset.upper_bound(key));
}

TEST(multiset, upper_bound3) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 9;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter <= key); ++iter)
    ;
  ASSERT_TRUE(iter == s21multiset.upper_bound(key));
}

TEST(multiset, upper_bound4) {
  s21::multiset<int> s21multiset = {};
  int key = 2;
  auto iter = s21multiset.begin();
  for (; iter != s21multiset.end() && (*iter <= key); ++iter)
    ;
  ASSERT_TRUE(iter == s21multiset.upper_bound(key));
}

TEST(multiset, equal_range1) {
  s21::multiset<int> s21multiset = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  ASSERT_TRUE(
      s21multiset.equal_range(key).first == s21multiset.lower_bound(key) &&
      s21multiset.equal_range(key).second == s21multiset.upper_bound(key));
}

TEST(multiset, equal_range2) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  ASSERT_TRUE(
      s21multiset.equal_range(key).first == s21multiset.lower_bound(key) &&
      s21multiset.equal_range(key).second == s21multiset.upper_bound(key));
}

TEST(multiset, equal_range3) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 9;
  ASSERT_TRUE(
      s21multiset.equal_range(key).first == s21multiset.lower_bound(key) &&
      s21multiset.equal_range(key).second == s21multiset.upper_bound(key));
}

TEST(multiset, equal_range4) {
  s21::multiset<int> s21multiset = {};
  int key = 2;
  ASSERT_TRUE(
      s21multiset.equal_range(key).first == s21multiset.lower_bound(key) &&
      s21multiset.equal_range(key).second == s21multiset.upper_bound(key));
}

TEST(multiset, count1) {
  s21::multiset<int> s21multiset = {1, 1, 2, 2, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  ASSERT_TRUE(s21multiset.count(key) == 2);
}

TEST(multiset, count2) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 2;
  ASSERT_TRUE(s21multiset.count(key) == 0);
}

TEST(multiset, count3) {
  s21::multiset<int> s21multiset = {1, 1, 3, 3, 4, 4, 5, 6, 7, 7};
  int key = 9;
  ASSERT_TRUE(s21multiset.count(key) == 0);
}

TEST(multiset, count4) {
  s21::multiset<int> s21multiset = {};
  int key = 2;
  ASSERT_TRUE(s21multiset.count(key) == 0);
}

TEST(multiset, insert_many1) {
  s21::multiset<int> s21multiset_1 = {1};
  s21::multiset<int> s21multiset_2 = {};
  auto res = s21multiset_2.insert_many(1);
  compare_s21_s21_multiset(s21multiset_1, s21multiset_2);
  ASSERT_TRUE(*(res[0].first) == 1);
}

TEST(multiset, insert_many2) {
  std::multiset<int> s21multiset_1 = {0, -100, 100, -50, 50, -75, 75};
  s21::multiset<int> s21multiset_2 = {};
  auto res = s21multiset_2.insert_many(0, -100, 100, -50, 50, -75, 75);
  compare_s21_std_multiset(s21multiset_1, s21multiset_2);
  std::vector<int> req = {0, -100, 100, -50, 50, -75, 75};
  for (size_t i = 0; i < req.size(); ++i)
    ASSERT_TRUE(*(res[i].first) == req[i]);
}
