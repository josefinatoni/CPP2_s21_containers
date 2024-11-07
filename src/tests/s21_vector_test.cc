#include "../s21_containers/vector/s21_vector.h"

#include <gtest/gtest.h>

#include "s21_test.h"

TEST(VECTOR, DefaultConstructor_SizeCapacityAndEmpty) {
  s21::vector<int> vec;

  ASSERT_EQ(vec.size(), 0UL);
  ASSERT_TRUE(vec.empty());
}

TEST(VECTOR, ConstructorWithSize_EmptyVector) {
  s21::vector<int> vec(0);

  ASSERT_EQ(vec.size(), 0UL);
  ASSERT_TRUE(vec.empty());
}

TEST(VECTOR, ConstructorWithSize_NonEmptyVector) {
  s21::vector<int> vec(3);

  ASSERT_EQ(vec.size(), 3UL);
  ASSERT_EQ(vec[0], 0);
  ASSERT_EQ(vec[1], 0);
  ASSERT_EQ(vec[2], 0);
}

TEST(VECTOR, ConstructorInitializerList_Empty) {
  s21::vector<int> vec = {};

  ASSERT_EQ(vec.size(), 0UL);
  ASSERT_TRUE(vec.empty());
}

TEST(VECTOR, ConstructorInitializerList_NonEmpty) {
  s21::vector<int> vec = {1, 2, 3};

  ASSERT_EQ(vec.size(), 3UL);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}

TEST(VECTOR, CopyConstructor_EmptyVector) {
  s21::vector<int> original;
  s21::vector<int> copy(original);

  ASSERT_EQ(copy.size(), 0UL);
  ASSERT_TRUE(copy.empty());
}

TEST(VECTOR, CopyConstructor_NonEmptyVector) {
  s21::vector<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  s21::vector<int> copy(original);

  ASSERT_EQ(copy.size(), 3UL);
  ASSERT_EQ(copy[0], 1);
  ASSERT_EQ(copy[1], 2);
  ASSERT_EQ(copy[2], 3);
}

TEST(VECTOR, MoveConstructor_EmptyVector) {
  s21::vector<int> original;
  s21::vector<int> moved(std::move(original));

  ASSERT_EQ(moved.size(), 0UL);
  ASSERT_TRUE(moved.empty());
  ASSERT_EQ(original.size(), 0UL);
}

TEST(VECTOR, MoveConstructor_NonEmptyVector) {
  s21::vector<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  s21::vector<int> moved(std::move(original));

  ASSERT_EQ(moved.size(), 3UL);
  ASSERT_EQ(moved[0], 1);
  ASSERT_EQ(moved[1], 2);
  ASSERT_EQ(moved[2], 3);
  ASSERT_EQ(original.size(), 0UL);
}

TEST(VECTOR, CopyAssignmentOperator_SameSize) {
  s21::vector<int> source = {1, 2, 3};
  s21::vector<int> dest = {4, 5, 6};

  dest = source;

  ASSERT_EQ(dest.size(), 3UL);
  ASSERT_EQ(dest[0], 1);
  ASSERT_EQ(dest[1], 2);
  ASSERT_EQ(dest[2], 3);
}

TEST(VECTOR, CopyAssignmentOperator_DifferentSize) {
  s21::vector<int> source = {1, 2, 3};
  s21::vector<int> dest = {4, 5, 6, 7};

  dest = source;

  ASSERT_EQ(dest.size(), 3UL);
  ASSERT_EQ(dest[0], 1);
  ASSERT_EQ(dest[1], 2);
  ASSERT_EQ(dest[2], 3);
}

TEST(VECTOR, MoveAssignmentOperator_EmptyToEmpty) {
  s21::vector<int> original;
  s21::vector<int> moved;
  moved = std::move(original);

  ASSERT_EQ(moved.size(), 0UL);
  ASSERT_TRUE(moved.empty());
  ASSERT_EQ(original.size(), 0UL);
}

TEST(VECTOR, MoveAssignmentOperator_NonEmptyToEmpty) {
  s21::vector<int> original;
  original.push_back(1);
  original.push_back(2);
  original.push_back(3);

  s21::vector<int> moved;
  moved = std::move(original);

  ASSERT_EQ(moved.size(), 3UL);
  ASSERT_EQ(moved[0], 1);
  ASSERT_EQ(moved[1], 2);
  ASSERT_EQ(moved[2], 3);
  ASSERT_EQ(original.size(), 0UL);
}

TEST(VECTOR, At_ValidIndex) {
  s21::vector<int> vec;

  vec.push_back(42);

  ASSERT_EQ(vec.at(0), 42);
}

TEST(VECTOR, At_InvalidIndex) {
  s21::vector<int> vec;

  ASSERT_THROW(vec.at(0), std::out_of_range);
}

TEST(VECTOR, OperatorIndex_NonEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);

  vec[1] = 42;
  ASSERT_EQ(vec[1], 42);
}

TEST(VECTOR, FrontAndBack_SingleElement) {
  s21::vector<int> vec;

  vec.push_back(42);

  ASSERT_EQ(vec.front(), 42);
  ASSERT_EQ(vec.back(), 42);
}

TEST(VECTOR, FrontAndBack_EmptyVector) {
  s21::vector<int> vec;

  ASSERT_THROW(vec.front(), std::out_of_range);
  ASSERT_THROW(vec.back(), std::out_of_range);
}

TEST(VECTOR, Data_EmptyVector) {
  s21::vector<int> v;
  int* dataPtr = v.data();
  EXPECT_EQ(dataPtr, nullptr);
}

TEST(VECTOR, Data_NonEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);

  auto data_ptr = vec.data();

  ASSERT_NE(data_ptr, nullptr);
  ASSERT_EQ(*data_ptr, 1);

  *data_ptr = 99;

  ASSERT_EQ(vec.size(), 2UL);
  ASSERT_EQ(vec[0], 99);
}

TEST(VECTOR, Begin_EmptyVector) {
  s21::vector<int> vec;

  auto begin_iter = vec.begin();
  auto end_iter = vec.end();

  ASSERT_EQ(begin_iter, end_iter);
}

TEST(VECTOR, Begin_NonEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  auto begin_iter = vec.begin();
  auto end_iter = vec.end();

  ASSERT_NE(begin_iter, end_iter);

  ASSERT_EQ(*begin_iter, 1);
  ASSERT_EQ(*(begin_iter + 1), 2);
  ASSERT_EQ(*(begin_iter + 2), 3);
}

TEST(VECTOR, End_EmptyVector) {
  s21::vector<int> vec;

  auto end_iter = vec.end();

  ASSERT_EQ(vec.begin(), end_iter);
}

TEST(VECTOR, End_ModifyVector) {
  s21::vector<int> vec;
  vec.push_back(42);

  auto end_iter = vec.end();

  *--end_iter = 99;
  ASSERT_EQ(vec[0], 99);
}

TEST(VECTOR, Empty_EmptyVector) {
  s21::vector<int> vec;

  ASSERT_TRUE(vec.empty());
  ASSERT_EQ(vec.size(), 0UL);
}

TEST(VECTOR, Empty_NonEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(42);

  ASSERT_FALSE(vec.empty());
  ASSERT_EQ(vec.size(), 1UL);
}

TEST(VECTOR, Size_EmptyVector) {
  s21::vector<int> vec;

  ASSERT_EQ(vec.size(), 0UL);
}

TEST(VECTOR, Size_NonEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(1);
  vec.push_back(2);
  vec.push_back(3);

  ASSERT_EQ(vec.size(), 3UL);
}

TEST(VECTOR, MaxSize) {
  s21::vector<int> vec;

  ASSERT_EQ(vec.max_size(), std::numeric_limits<size_t>::max());
}

TEST(VECTOR, Reserve_IncreaseCapacity) {
  s21::vector<int> vec;

  vec.reserve(10);

  ASSERT_EQ(vec.capacity(), 10UL);
}

TEST(VECTOR, Reserve_NoCapacityIncrease) {
  s21::vector<int> vec;

  vec.reserve(5);

  ASSERT_EQ(vec.capacity(), 5UL);
}

TEST(VECTOR, Capacity_EmptyVector) {
  s21::vector<int> vec;

  ASSERT_EQ(vec.capacity(), 0UL);
}

TEST(VECTOR, Capacity_NonEmptyVector) {
  s21::vector<int> vec;
  vec.push_back(1);

  ASSERT_GE(vec.capacity(), 1UL);
}

TEST(VECTOR, ShrinkToFit_NonEmptyVector) {
  s21::vector<int> vec;
  vec.reserve(10);
  vec.push_back(1);
  vec.push_back(2);

  vec.shrink_to_fit();

  ASSERT_EQ(vec.capacity(), vec.size());
}

TEST(VECTOR, ShrinkToFit_EmptyVector) {
  s21::vector<int> vec;
  vec.reserve(10);

  vec.shrink_to_fit();

  ASSERT_EQ(vec.capacity(), 0UL);
}

TEST(VECTOR, DefaultClear) {
  s21::vector<int> vec;

  vec.push_back(42);
  vec.push_back(99);

  ASSERT_EQ(vec.size(), 2UL);

  vec.clear();

  ASSERT_EQ(vec.size(), 0UL);
  ASSERT_TRUE(vec.empty());
}

TEST(VECTOR, Clear_EmptyVector) {
  s21::vector<int> vec;

  vec.clear();

  ASSERT_EQ(vec.size(), 0UL);
  ASSERT_TRUE(vec.empty());
}

TEST(VECTOR, Insert_Begin) {
  s21::vector<int> vec = {2, 3, 4};
  auto it = vec.begin();

  auto inserted_iter = vec.insert(it, 1);

  ASSERT_EQ(vec.size(), 4UL);
  ASSERT_EQ(*inserted_iter, 1);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
}

TEST(VECTOR, Insert_Middle) {
  s21::vector<int> vec = {1, 3, 4};
  auto it = vec.begin() + 1;

  auto inserted_iter = vec.insert(it, 2);

  ASSERT_EQ(vec.size(), 4UL);
  ASSERT_EQ(*inserted_iter, 2);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
}

TEST(VECTOR, Erase_Begin) {
  s21::vector<int> vec = {1, 2, 3, 4};
  auto it = vec.begin();

  vec.erase(it);

  ASSERT_EQ(vec.size(), 3UL);
  ASSERT_EQ(vec[0], 2);
  ASSERT_EQ(vec[1], 3);
  ASSERT_EQ(vec[2], 4);
}

TEST(VECTOR, Erase_Middle) {
  s21::vector<int> vec = {1, 2, 3, 4};
  auto it = vec.begin() + 2;

  vec.erase(it);

  ASSERT_EQ(vec.size(), 3UL);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 4);
}

TEST(VECTOR, PushBack_IncreaseSize) {
  s21::vector<int> vec;

  ASSERT_EQ(vec.size(), 0UL);

  vec.push_back(42);
  ASSERT_EQ(vec.size(), 1UL);
  ASSERT_EQ(vec[0], 42);
}

TEST(VECTOR, PushBack_MultipleElements) {
  s21::vector<int> vec;

  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  ASSERT_EQ(vec.size(), 3UL);
  ASSERT_EQ(vec[0], 10);
  ASSERT_EQ(vec[1], 20);
  ASSERT_EQ(vec[2], 30);
}

TEST(VECTOR, PopBack_DecreaseSize) {
  s21::vector<int> vec;

  vec.push_back(42);
  vec.pop_back();

  ASSERT_EQ(vec.size(), 0UL);
  ASSERT_TRUE(vec.empty());
}

TEST(VECTOR, PopBack_MultipleElements) {
  s21::vector<int> vec;

  vec.push_back(10);
  vec.push_back(20);
  vec.push_back(30);

  vec.pop_back();

  ASSERT_EQ(vec.size(), 2UL);
  ASSERT_EQ(vec[0], 10);
  ASSERT_EQ(vec[1], 20);
}

TEST(VECTOR, Swap_EmptyVectors) {
  s21::vector<int> vec1;
  s21::vector<int> vec2;

  vec1.swap(vec2);

  ASSERT_EQ(vec1.size(), 0UL);
  ASSERT_EQ(vec2.size(), 0UL);
}

TEST(VECTOR, Swap_SingleElement) {
  s21::vector<int> vec1;
  s21::vector<int> vec2;

  vec1.push_back(42);

  vec1.swap(vec2);

  ASSERT_EQ(vec1.size(), 0UL);
  ASSERT_EQ(vec2.size(), 1UL);
  ASSERT_EQ(vec2[0], 42);
}

TEST(VECTOR, InsertMany_Begin) {
  s21::vector<int> vec = {4, 5, 6};
  auto it = vec.begin();

  vec.insert_many(it, 1, 2, 3);

  ASSERT_EQ(vec.size(), 6UL);

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 6);
}

TEST(VECTOR, InsertMany_End) {
  s21::vector<int> vec = {1, 2, 3};
  auto it = vec.end();

  vec.insert_many(it, 4, 5, 6);

  ASSERT_EQ(vec.size(), 6UL);

  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 6);
}

TEST(VECTOR, InsertManyBack_EmptyVector) {
  s21::vector<int> vec;

  vec.insert_many_back(1, 2, 3);

  ASSERT_EQ(vec.size(), 3UL);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
}

TEST(VECTOR, InsertManyBack_MixedTypes) {
  s21::vector<std::string> vec = {"apple", "banana"};

  vec.insert_many_back("cherry", "date");

  ASSERT_EQ(vec.size(), 4UL);
  ASSERT_EQ(vec[0], "apple");
  ASSERT_EQ(vec[1], "banana");
  ASSERT_EQ(vec[2], "cherry");
  ASSERT_EQ(vec[3], "date");
}

TEST(vector, Constructor) {
  s21::vector<std::string> s21vector;
  ASSERT_EQ(s21vector.capacity(), 0UL);
  ASSERT_EQ(s21vector.size(), 0UL);
  ASSERT_TRUE(s21vector.empty());
}

TEST(vector, ConstructorWithSize) {
  s21::vector<std::string> s21vector(5);
  ASSERT_EQ(s21vector.capacity(), 5UL);
  ASSERT_EQ(s21vector.size(), 5UL);
  ASSERT_FALSE(s21vector.empty());
}

TEST(vector, ConstructorWithInitializerList) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  ASSERT_EQ(s21vector.capacity(), 5UL);
  ASSERT_EQ(s21vector.size(), 5UL);
  ASSERT_FALSE(s21vector.empty());
  for (size_t i = 0; i < s21vector.size(); ++i) {
    ASSERT_EQ(static_cast<unsigned long>(s21vector[i]), i + 1);
  }
}

TEST(vector, CopyConstructor) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2(s21vector);
  ASSERT_EQ(s21vector2.capacity(), s21vector.capacity());
  ASSERT_EQ(s21vector2.size(), s21vector.size());
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(s21vector2[i], s21vector[i]);
  }
}

TEST(vector, MoveConstructor) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2(std::move(s21vector));
  ASSERT_EQ(s21vector.capacity(), 0UL);
  ASSERT_EQ(s21vector.size(), 0UL);
  ASSERT_TRUE(s21vector.empty());
  ASSERT_EQ(s21vector2.capacity(), 5UL);
  ASSERT_EQ(s21vector2.size(), 5UL);
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(static_cast<unsigned long>(s21vector2[i]), i + 1);
  }
}

TEST(vector, AssignmentOperatorCopy) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2;
  s21vector2 = s21vector;
  ASSERT_EQ(s21vector2.capacity(), s21vector.capacity());
  ASSERT_EQ(s21vector2.size(), s21vector.size());
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(s21vector2[i], s21vector[i]);
  }
}

TEST(vector, AssignmentOperatorMove) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21::vector<int> s21vector2;
  s21vector2 = std::move(s21vector);
  ASSERT_EQ(s21vector.capacity(), 0UL);
  ASSERT_EQ(s21vector.size(), 0UL);
  ASSERT_TRUE(s21vector.empty());
  ASSERT_EQ(s21vector2.capacity(), 5UL);
  ASSERT_EQ(s21vector2.size(), 5UL);
  ASSERT_FALSE(s21vector2.empty());
  for (size_t i = 0; i < s21vector2.size(); ++i) {
    ASSERT_EQ(static_cast<unsigned long>(s21vector2[i]), i + 1);
  }
}

TEST(vector, FrontAndBack) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  ASSERT_EQ(s21vector.front(), 1);
  ASSERT_EQ(s21vector.back(), 5);
}

TEST(vector, Data) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  int* data = s21vector.data();
  for (size_t i = 0; i < s21vector.size(); ++i) {
    ASSERT_EQ(data[i], s21vector[i]);
  }
}

TEST(vector, BeginAndEnd) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  auto begin = s21vector.begin();
  auto end = s21vector.end();
  size_t count = 0;
  for (auto it = begin; it != end; ++it) {
    ASSERT_EQ(*it, s21vector[count]);
    ++count;
  }
}

TEST(vector, Reserve) {
  s21::vector<int> s21vector;
  s21vector.reserve(100);
  ASSERT_GE(s21vector.capacity(), 100UL);
}

TEST(vector, ShrinkToFit) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.reserve(100);
  s21vector.shrink_to_fit();
  ASSERT_EQ(s21vector.capacity(), 5UL);
}

TEST(vector, Clear) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.clear();
  ASSERT_TRUE(s21vector.empty());
}

TEST(vector, Insert) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  auto it = s21vector.begin() + 2;
  s21vector.insert(it, 10);
  ASSERT_EQ(s21vector[2], 10);
}

TEST(vector, Erase) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  auto it = s21vector.begin() + 2;
  s21vector.erase(it);
  ASSERT_EQ(s21vector[2], 4);
}

TEST(vector, PushBack) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.push_back(6);
  ASSERT_EQ(s21vector.back(), 6);
}

TEST(vector, PopBack) {
  s21::vector<int> s21vector{1, 2, 3, 4, 5};
  s21vector.pop_back();
  ASSERT_EQ(s21vector.back(), 4);
}

TEST(vector, InsertMany) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert_many(vec.begin() + 1, 10, 20,
                  30);  // вставляем 10, 20, 30 на позицию после 1
  ASSERT_EQ(vec.size(), 6UL);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 10);
  ASSERT_EQ(vec[2], 20);
  ASSERT_EQ(vec[3], 30);
  ASSERT_EQ(vec[4], 2);
  ASSERT_EQ(vec[5], 3);
}

TEST(vector, InsertManyBack) {
  s21::vector<int> vec{1, 2, 3};
  vec.insert_many_back(4, 5, 6);  // добавляем 4, 5, 6 в конец
  ASSERT_EQ(vec.size(), 6UL);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
  ASSERT_EQ(vec[5], 6);
}

TEST(vector, InsertManyEdgeCases) {
  s21::vector<int> vec;
  vec.insert_many_back(1, 2, 3, 4, 5);  // добавляем в пустой вектор
  ASSERT_EQ(vec.size(), 5UL);
  ASSERT_EQ(vec[0], 1);
  ASSERT_EQ(vec[1], 2);
  ASSERT_EQ(vec[2], 3);
  ASSERT_EQ(vec[3], 4);
  ASSERT_EQ(vec[4], 5);
}
