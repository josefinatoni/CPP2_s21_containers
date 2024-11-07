#include "../s21_containers/list/s21_list.h"

#include <gtest/gtest.h>

#include <list>

#include "s21_test.h"

TEST(list, Create) {
  s21::list<int> my_list;
  std::list<int> std_list;

  ASSERT_EQ(my_list.empty(), std_list.empty());
  ASSERT_EQ(my_list.size(), std_list.size());
}

TEST(list, CopyConstructor) {
  s21::list<int> s21_original = {1, 2, 3, 4, 5};
  std::list<int> std_original = {1, 2, 3, 4, 5};

  s21::list<int> s21_copied(s21_original);
  std::list<int> std_copied(std_original);

  ASSERT_EQ(s21_copied.size(), std_copied.size());

  auto it_s21 = s21_copied.begin();
  auto it_std = std_copied.begin();

  while (it_s21 != s21_copied.end() && it_std != std_copied.end()) {
    ASSERT_EQ(*it_s21, *it_std);
    ++it_s21;
    ++it_std;
  }
}

TEST(list, MoveConstructor) {
  s21::list<int> s21_original = {1, 2, 3, 4, 5};
  std::list<int> std_original = {1, 2, 3, 4, 5};

  s21::list<int> s21_moved(std::move(s21_original));
  std::list<int> std_moved(std::move(std_original));

  ASSERT_TRUE(s21_original.empty());
  ASSERT_TRUE(std_original.empty());

  ASSERT_EQ(s21_moved.size(), std_moved.size());

  auto it_s21 = s21_moved.begin();
  auto it_std = std_moved.begin();

  while (it_s21 != s21_moved.end() && it_std != std_moved.end()) {
    ASSERT_EQ(*it_s21, *it_std);
    ++it_s21;
    ++it_std;
  }
}

TEST(list, InsertAtBeginning) {
  s21::list<int> my_list;
  std::list<int> std_list;

  auto my_it = my_list.insert(my_list.begin(), 10);
  auto std_it = std_list.insert(std_list.begin(), 10);

  ASSERT_EQ(my_list.size(), std_list.size());
  ASSERT_EQ(*my_it, *std_it);
}

TEST(list, InsertAtEnd) {
  s21::list<int> my_list = {1, 2, 3};
  auto it = my_list.end();
  my_list.insert(it, 4);

  std::list<int> std_list = {1, 2, 3};
  auto std_it = std_list.end();
  std_list.insert(std_it, 4);

  ASSERT_EQ(my_list.size(), std_list.size());
  auto my_it = my_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++my_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, InsertInMiddle) {
  s21::list<int> my_list = {1, 3, 4};
  auto it = my_list.begin();
  std::advance(it, 1);
  my_list.insert(it, 2);

  std::list<int> std_list = {1, 3, 4};
  auto std_it = std_list.begin();
  std::advance(std_it, 1);
  std_list.insert(std_it, 2);

  ASSERT_EQ(my_list.size(), std_list.size());
  auto my_it = my_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++my_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, InsertManyAtBeginning) {
  s21::list<int> my_list = {2, 3, 4};
  std::list<int> std_list = {2, 3, 4};

  my_list.insert_many(my_list.cbegin(), 0, 1);
  std_list.insert(std_list.begin(), {0, 1});

  ASSERT_EQ(my_list.size(), std_list.size());
  auto it_my = my_list.cbegin();
  auto it_std = std_list.begin();
  for (; it_my != my_list.cend(); ++it_my, ++it_std) {
    ASSERT_EQ(*it_my, *it_std);
  }
}

TEST(list, InsertManyAtMiddle) {
  s21::list<int> my_list = {1, 2, 5, 6};
  std::list<int> std_list = {1, 2, 5, 6};

  auto it_my_list = my_list.cbegin();
  std::advance(it_my_list, 2);
  auto it_std_list = std_list.begin();
  std::advance(it_std_list, 2);

  my_list.insert_many(it_my_list, 3, 4);
  std_list.insert(it_std_list, {3, 4});

  ASSERT_EQ(my_list.size(), std_list.size());
  auto it_my = my_list.cbegin();
  auto it_std = std_list.begin();
  for (; it_my != my_list.cend(); ++it_my, ++it_std) {
    ASSERT_EQ(*it_my, *it_std);
  }
}

TEST(list, InsertManyAtEnd) {
  s21::list<int> my_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  my_list.insert_many(my_list.cend(), 4, 5);
  std_list.insert(std_list.end(), {4, 5});

  ASSERT_EQ(my_list.size(), std_list.size());
  auto it_my = my_list.begin();
  auto it_std = std_list.begin();

  for (; it_my != my_list.end(); ++it_my, ++it_std) {
    ASSERT_EQ(*it_my, *it_std);
  }
}

TEST(list, InsertManyBackInEmptyList) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.insert_many(my_list.cbegin(), 1, 2, 3);
  std_list.insert(std_list.begin(), {1, 2, 3});

  ASSERT_EQ(my_list.size(), std_list.size());
  auto it_my = my_list.cbegin();
  auto it_std = std_list.begin();
  for (; it_my != my_list.cend(); ++it_my, ++it_std) {
    ASSERT_EQ(*it_my, *it_std);
  }
}

TEST(list, InsertManyBackEmptyList) {
  s21::list<int> my_list;
  my_list.insert_many_back(1, 2, 3, 4, 5);

  std::list<int> std_list({1, 2, 3, 4, 5});
  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  for (const auto& item : std_list) {
    ASSERT_EQ(*my_it, item);
    ++my_it;
  }
}

TEST(list, InsertManyBackNonEmptyList) {
  s21::list<int> my_list({0});
  my_list.insert_many_back(1, 2, 3);

  std::list<int> std_list({0, 1, 2, 3});
  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  for (const auto& item : std_list) {
    ASSERT_EQ(*my_it, item);
    ++my_it;
  }
}

TEST(list, InsertBackSingleElement) {
  s21::list<int> my_list;
  my_list.insert_many_back(42);

  ASSERT_EQ(my_list.size(), 1u);
  ASSERT_EQ(my_list.front(), 42);
  ASSERT_EQ(my_list.back(), 42);
}

TEST(list, InsertBackNoElements) {
  s21::list<int> my_list;
  my_list.insert_many_back();

  ASSERT_TRUE(my_list.empty());
}

TEST(list, InsertManyFrontEmptyList) {
  s21::list<int> my_list;
  my_list.insert_many_front(5, 4, 3, 2, 1);

  std::list<int> std_list({5, 4, 3, 2, 1});
  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  for (const auto& item : std_list) {
    ASSERT_EQ(*my_it, item);
    ++my_it;
  }
}

TEST(list, InsertManyNonEmptyList) {
  s21::list<int> my_list({6});
  my_list.insert_many_front(3, 2, 1);

  std::list<int> std_list({3, 2, 1, 6});
  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  for (const auto& item : std_list) {
    ASSERT_EQ(*my_it, item);
    ++my_it;
  }
}

TEST(list, InsertSingleElement) {
  s21::list<int> my_list;
  my_list.insert_many_front(42);

  ASSERT_EQ(my_list.size(), 1u);
  ASSERT_EQ(my_list.front(), 42);
  ASSERT_EQ(my_list.back(), 42);
}

TEST(list, InsertNoElements) {
  s21::list<int> my_list;
  my_list.insert_many_front();

  ASSERT_TRUE(my_list.empty());
}

TEST(list, EraseFromBeginning) {
  s21::list<int> my_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  my_list.erase(my_list.begin());
  std_list.erase(std_list.begin());

  ASSERT_EQ(my_list.size(), std_list.size());
  auto my_it = my_list.begin();
  auto std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, EraseFromMiddle) {
  s21::list<int> my_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  auto my_it = my_list.begin();
  std::advance(my_it, 2);
  my_list.erase(my_it);

  auto std_it = std_list.begin();
  std::advance(std_it, 2);
  std_list.erase(std_it);

  ASSERT_EQ(my_list.size(), std_list.size());
  my_it = my_list.begin();
  std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, EraseFromEnd) {
  s21::list<int> my_list = {1, 2, 3, 4};
  std::list<int> std_list = {1, 2, 3, 4};

  ASSERT_FALSE(my_list.empty());
  ASSERT_FALSE(std_list.empty());

  auto my_it = my_list.begin();
  auto prev_it = my_it;
  while (my_it != my_list.end()) {
    prev_it = my_it;
    ++my_it;
  }
  my_list.erase(prev_it);

  auto std_it = std_list.end();
  --std_it;
  std_list.erase(std_it);

  ASSERT_EQ(my_list.size(), std_list.size());

  my_it = my_list.begin();
  std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, SwapLists) {
  s21::list<int> my_list1 = {1, 2, 3};
  s21::list<int> my_list2 = {4, 5, 6, 7};

  std::list<int> std_list1 = {1, 2, 3};
  std::list<int> std_list2 = {4, 5, 6, 7};

  my_list1.swap(my_list2);
  std_list1.swap(std_list2);

  ASSERT_EQ(my_list1.size(), std_list1.size());
  ASSERT_EQ(my_list2.size(), std_list2.size());

  auto my_it1 = my_list1.begin();
  auto std_it1 = std_list1.begin();
  for (; my_it1 != my_list1.end() && std_it1 != std_list1.end();
       ++my_it1, ++std_it1) {
    ASSERT_EQ(*my_it1, *std_it1);
  }

  auto my_it2 = my_list2.begin();
  auto std_it2 = std_list2.begin();
  for (; my_it2 != my_list2.end() && std_it2 != std_list2.end();
       ++my_it2, ++std_it2) {
    ASSERT_EQ(*my_it2, *std_it2);
  }
}

TEST(list, SortTest) {
  s21::list<int> my_list = {4, 2, 5, 1, 3};
  std::list<int> std_list = {4, 2, 5, 1, 3};

  my_list.sort();
  std_list.sort();

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
  ASSERT_EQ(my_it, my_list.end());
}

TEST(list, MergeWithSortTest) {
  s21::list<int> my_list1 = {5, 1, 3};
  std::list<int> std_list1 = {5, 1, 3};
  s21::list<int> my_list2 = {6, 2, 4};
  std::list<int> std_list2 = {6, 2, 4};

  my_list1.sort();
  std_list1.sort();
  my_list2.sort();
  std_list2.sort();

  my_list1.merge(my_list2);
  std_list1.merge(std_list2);

  auto my_it = my_list1.begin();
  auto std_it = std_list1.begin();
  for (; my_it != my_list1.end() && std_it != std_list1.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
  ASSERT_EQ(my_it, my_list1.end());
  ASSERT_TRUE(my_list2.empty());
  ASSERT_TRUE(std_list2.empty());
}

TEST(list, SpliceToBeginning) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> other_list = {4, 5, 6};
  std::list<int> std_my_list = {1, 2, 3};
  std::list<int> std_other_list = {4, 5, 6};

  my_list.splice(my_list.begin(), other_list);
  std_my_list.splice(std_my_list.begin(), std_other_list);

  EXPECT_EQ(my_list.size(), std_my_list.size());
  auto my_it = my_list.begin();
  auto std_it = std_my_list.begin();
  for (; my_it != my_list.end(); ++my_it, ++std_it) {
    EXPECT_EQ(*my_it, *std_it);
  }
}

TEST(list, SpliceToEnd) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> other_list = {4, 5, 6};
  std::list<int> std_my_list = {1, 2, 3};
  std::list<int> std_other_list = {4, 5, 6};

  my_list.splice(my_list.end(), other_list);
  std_my_list.splice(std_my_list.end(), std_other_list);

  EXPECT_EQ(my_list.size(), std_my_list.size());
  auto my_it = my_list.begin();
  auto std_it = std_my_list.begin();
  for (; my_it != my_list.end(); ++my_it, ++std_it) {
    EXPECT_EQ(*my_it, *std_it);
  }
}

TEST(list, SpliceToMiddle) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> other_list = {4, 5, 6};
  std::list<int> std_my_list = {1, 2, 3};
  std::list<int> std_other_list = {4, 5, 6};

  auto my_mid = std::next(my_list.begin(), 2);
  auto std_mid = std::next(std_my_list.begin(), 2);

  my_list.splice(my_mid, other_list);
  std_my_list.splice(std_mid, std_other_list);

  EXPECT_EQ(my_list.size(), std_my_list.size());
  auto my_it = my_list.begin();
  auto std_it = std_my_list.begin();
  for (; my_it != my_list.end(); ++my_it, ++std_it) {
    EXPECT_EQ(*my_it, *std_it);
  }
}

TEST(list, SpliceEmptyList) {
  s21::list<int> my_list = {1, 2, 3};
  s21::list<int> other_list;
  std::list<int> std_my_list = {1, 2, 3};
  std::list<int> std_other_list;

  my_list.splice(my_list.begin(), other_list);
  std_my_list.splice(std_my_list.begin(), std_other_list);

  EXPECT_EQ(my_list.size(), std_my_list.size());
  auto my_it = my_list.begin();
  auto std_it = std_my_list.begin();
  for (; my_it != my_list.end(); ++my_it, ++std_it) {
    EXPECT_EQ(*my_it, *std_it);
  }
}

TEST(list, SpliceIntoEmptyList) {
  s21::list<int> my_list;
  s21::list<int> other_list = {1, 2, 3};
  std::list<int> std_my_list;
  std::list<int> std_other_list = {1, 2, 3};

  my_list.splice(my_list.begin(), other_list);
  std_my_list.splice(std_my_list.begin(), std_other_list);

  EXPECT_EQ(my_list.size(), std_my_list.size());
  auto my_it = my_list.begin();
  auto std_it = std_my_list.begin();
  for (; my_it != my_list.end(); ++my_it, ++std_it) {
    EXPECT_EQ(*my_it, *std_it);
  }
}

TEST(list, ReverseEmptyList) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.reverse();
  std_list.reverse();

  ASSERT_TRUE(my_list.empty());
  ASSERT_TRUE(std_list.empty());
}

TEST(list, ReverseSingleElement) {
  s21::list<int> my_list = {1};
  std::list<int> std_list = {1};

  my_list.reverse();
  std_list.reverse();

  ASSERT_EQ(my_list.front(), std_list.front());
  ASSERT_EQ(my_list.back(), std_list.back());
}

TEST(list, ReverseMultipleElements) {
  s21::list<int> my_list = {1, 2, 3, 4, 5};
  std::list<int> std_list = {1, 2, 3, 4, 5};

  my_list.reverse();
  std_list.reverse();

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, UniqueOnEmptyList) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.unique();
  std_list.unique();

  ASSERT_EQ(my_list.size(), std_list.size());
}

TEST(list, UniqueOnNonDuplicateList) {
  s21::list<int> my_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  my_list.unique();
  std_list.unique();

  ASSERT_EQ(my_list.size(), std_list.size());
}

TEST(list, UniqueOnDuplicateList) {
  s21::list<int> my_list = {1, 1, 2, 3, 3, 2, 3};
  std::list<int> std_list = {1, 1, 2, 3, 3, 2, 3};

  my_list.unique();
  std_list.unique();

  auto it1 = my_list.begin();
  auto it2 = std_list.begin();
  while (it1 != my_list.end() && it2 != std_list.end()) {
    ASSERT_EQ(*it1, *it2);
    ++it1;
    ++it2;
  }
  ASSERT_EQ(it1, my_list.end());
  ASSERT_EQ(it2, std_list.end());
}

TEST(list, CopyAssignment) {
  s21::list<int> my_list;
  std::list<int> std_list;

  for (int i = 0; i < 5; ++i) {
    my_list.push_back(i);
    std_list.push_back(i);
  }

  s21::list<int> my_list_copy;
  std::list<int> std_list_copy;
  my_list_copy = my_list;
  std_list_copy = std_list;

  ASSERT_EQ(my_list_copy.size(), std_list_copy.size());

  auto my_it = my_list_copy.begin();
  auto std_it = std_list_copy.begin();
  for (; my_it != my_list_copy.end() && std_it != std_list_copy.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, MoveAssignment) {
  s21::list<int> my_list;
  std::list<int> std_list;

  for (int i = 0; i < 5; ++i) {
    my_list.push_back(i);
    std_list.push_back(i);
  }

  s21::list<int> my_list_moved;
  std::list<int> std_list_moved;
  my_list_moved = std::move(my_list);
  std_list_moved = std::move(std_list);

  ASSERT_EQ(my_list_moved.size(), std_list_moved.size());
  ASSERT_TRUE(my_list.empty());
  ASSERT_TRUE(std_list.empty());

  auto my_it = my_list_moved.begin();
  auto std_it = std_list_moved.begin();
  for (; my_it != my_list_moved.end() && std_it != std_list_moved.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, PushBackAndFront) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.push_back(10);
  std_list.push_back(10);
  my_list.push_back(20);
  std_list.push_back(20);
  my_list.push_front(5);
  std_list.push_front(5);

  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }
}

TEST(list, Clear) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.push_back(10);
  std_list.push_back(10);
  my_list.push_back(20);
  std_list.push_back(20);
  my_list.clear();
  std_list.clear();

  ASSERT_EQ(my_list.empty(), std_list.empty());
}

TEST(list, Iterator) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.push_back(10);
  std_list.push_back(10);
  my_list.push_back(20);
  std_list.push_back(20);

  auto my_last = my_list.begin();
  auto std_last = std_list.begin();

  for (auto it = my_list.begin(); it != my_list.end(); ++it) {
    if (++it == my_list.end()) {
      --it;
      my_last = it;
      break;
    }
  }

  for (auto it = std_list.begin(); it != std_list.end(); ++it) {
    if (++it == std_list.end()) {
      --it;
      std_last = it;
      break;
    }
  }

  ASSERT_EQ(*my_last, *std_last);
}

TEST(list, PopFront) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.push_back(10);
  std_list.push_back(10);
  my_list.push_back(20);
  std_list.push_back(20);
  my_list.push_front(5);
  std_list.push_front(5);

  my_list.pop_front();
  std_list.pop_front();
  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }

  my_list.pop_front();
  std_list.pop_front();
  ASSERT_EQ(my_list.size(), std_list.size());

  my_list.pop_front();
  std_list.pop_front();
  ASSERT_EQ(my_list.empty(), std_list.empty());
}

TEST(list, PopBack) {
  s21::list<int> my_list;
  std::list<int> std_list;

  my_list.push_back(10);
  std_list.push_back(10);
  my_list.push_back(20);
  std_list.push_back(20);
  my_list.push_back(30);
  std_list.push_back(30);

  my_list.pop_back();
  std_list.pop_back();
  ASSERT_EQ(my_list.size(), std_list.size());

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();
  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }

  my_list.pop_back();
  std_list.pop_back();
  ASSERT_EQ(my_list.size(), std_list.size());

  my_list.pop_back();
  std_list.pop_back();
  ASSERT_EQ(my_list.empty(), std_list.empty());
}

TEST(list, DefaultConstructor) {
  s21::list<int> lst_s21;
  std::list<int> lst_std;

  EXPECT_EQ(lst_s21.size(), lst_std.size());
  EXPECT_TRUE(lst_s21.empty() == lst_std.empty());

  // Попытка доступа к несуществующему элементу
  EXPECT_THROW(lst_s21.front(), std::out_of_range);
  EXPECT_THROW(lst_s21.back(), std::out_of_range);
}

TEST(list, ParameterizedConstructor) {
  size_t n = 5;
  s21::list<int> lst_s21(n);
  std::list<int> lst_std(n);

  EXPECT_EQ(lst_s21.size(), lst_std.size());
  EXPECT_FALSE(lst_s21.empty() != lst_std.empty());

  auto it_s21 = lst_s21.begin();
  auto it_std = lst_std.begin();
  for (; it_s21 != lst_s21.end() && it_std != lst_std.end();
       ++it_s21, ++it_std) {
    EXPECT_EQ(*it_s21, *it_std);
  }
}

TEST(list, IteratorBasic) {
  s21::list<int> my_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();

  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }

  ASSERT_EQ(my_it, my_list.end());
}

TEST(list, IteratorIncrementDecrement) {
  s21::list<int> my_list = {1, 2, 3};
  std::list<int> std_list = {1, 2, 3};

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();

  ++my_it;
  ++std_it;
  ASSERT_EQ(*my_it, *std_it);

  ++my_it;
  ++std_it;
  ASSERT_EQ(*my_it, *std_it);

  --my_it;
  --std_it;
  ASSERT_EQ(*my_it, *std_it);
}

TEST(list, ConstIteratorBasic) {
  const s21::list<int> my_list = {1, 2, 3};
  const std::list<int> std_list = {1, 2, 3};

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();

  for (; my_it != my_list.end() && std_it != std_list.end();
       ++my_it, ++std_it) {
    ASSERT_EQ(*my_it, *std_it);
  }

  ASSERT_EQ(my_it, my_list.end());
}

TEST(list, ConstIteratorIncrementDecrement) {
  const s21::list<int> my_list = {1, 2, 3};
  const std::list<int> std_list = {1, 2, 3};

  auto my_it = my_list.begin();
  auto std_it = std_list.begin();

  ++my_it;
  ++std_it;
  ASSERT_EQ(*my_it, *std_it);

  ++my_it;
  ++std_it;
  ASSERT_EQ(*my_it, *std_it);

  --my_it;
  --std_it;
  ASSERT_EQ(*my_it, *std_it);
}
