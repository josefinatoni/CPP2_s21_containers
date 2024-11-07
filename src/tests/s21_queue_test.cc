#include "s21_test.h"

// Tests for the queue class

TEST(QueueTest, DefaultConstructor) {
  s21::queue<char> q1;
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1.size(), 0UL);

  s21::queue<int> q2;
  EXPECT_TRUE(q2.empty());
  EXPECT_EQ(q2.size(), 0UL);

  s21::queue<double> q3;
  EXPECT_TRUE(q3.empty());
  EXPECT_EQ(q3.size(), 0UL);
}

TEST(QueueTest, ConstructorWithInitializerList) {
  s21::queue<char> q1{'a', 'b', 'c'};
  EXPECT_FALSE(q1.empty());
  EXPECT_EQ(q1.size(), 3UL);
  EXPECT_EQ(q1.front(), 'a');
  EXPECT_EQ(q1.back(), 'c');

  s21::queue<int> q2{1, 2, 3};
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 1);
  EXPECT_EQ(q2.back(), 3);

  s21::queue<double> q3{1.1, 2.2, 3.3};
  EXPECT_FALSE(q3.empty());
  EXPECT_EQ(q3.size(), 3UL);
  EXPECT_DOUBLE_EQ(q3.front(), 1.1);
  EXPECT_DOUBLE_EQ(q3.back(), 3.3);
}

TEST(QueueTest, CopyConstructor) {
  s21::queue<char> q1{'a', 'b', 'c'};
  s21::queue<char> q2(q1);
  EXPECT_EQ(q1.size(), q2.size());
  EXPECT_EQ(q1.front(), q2.front());
  EXPECT_EQ(q1.back(), q2.back());

  s21::queue<int> q3{1, 2, 3};
  s21::queue<int> q4(q3);
  EXPECT_EQ(q3.size(), q4.size());
  EXPECT_EQ(q3.front(), q4.front());
  EXPECT_EQ(q3.back(), q4.back());

  s21::queue<double> q5{1.1, 2.2, 3.3};
  s21::queue<double> q6(q5);
  EXPECT_EQ(q5.size(), q6.size());
  EXPECT_DOUBLE_EQ(q5.front(), q6.front());
  EXPECT_DOUBLE_EQ(q5.back(), q6.back());
}

// Move constructor
TEST(QueueTest, MoveConstructor) {
  s21::queue<char> q1{'a', 'b', 'c'};
  s21::queue<char> q2(std::move(q1));
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1.size(), 0UL);
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 'a');
  EXPECT_EQ(q2.back(), 'c');

  s21::queue<int> q3{1, 2, 3};
  s21::queue<int> q4(std::move(q3));
  EXPECT_TRUE(q3.empty());
  EXPECT_EQ(q3.size(), 0UL);
  EXPECT_FALSE(q4.empty());
  EXPECT_EQ(q4.size(), 3UL);
  EXPECT_EQ(q4.front(), 1);
  EXPECT_EQ(q4.back(), 3);

  s21::queue<double> q5{1.1, 2.2, 3.3};
  s21::queue<double> q6(std::move(q5));
  EXPECT_TRUE(q5.empty());
  EXPECT_EQ(q5.size(), 0UL);
  EXPECT_FALSE(q6.empty());
  EXPECT_EQ(q6.size(), 3UL);
  EXPECT_DOUBLE_EQ(q6.front(), 1.1);
  EXPECT_DOUBLE_EQ(q6.back(), 3.3);
}

TEST(QueueTest, Destructor) {
  s21::queue<char> q{'a', 'b', 'c'};

  EXPECT_EQ(q.size(), 3UL);
}

TEST(QueueTest, MoveAssignmentOperator) {
  s21::queue<char> q1{'a', 'b', 'c'};
  s21::queue<char> q2;
  q2 = std::move(q1);
  EXPECT_TRUE(q1.empty());
  EXPECT_EQ(q1.size(), 0UL);
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 'a');
  EXPECT_EQ(q2.back(), 'c');

  s21::queue<int> q3{1, 2, 3};
  s21::queue<int> q4;
  q4 = std::move(q3);
  EXPECT_TRUE(q3.empty());
  EXPECT_EQ(q3.size(), 0UL);
  EXPECT_FALSE(q4.empty());
  EXPECT_EQ(q4.size(), 3UL);
  EXPECT_EQ(q4.front(), 1);
  EXPECT_EQ(q4.back(), 3);

  s21::queue<double> q5{1.1, 2.2, 3.3};
  s21::queue<double> q6;
  q6 = std::move(q5);
  EXPECT_TRUE(q5.empty());
  EXPECT_EQ(q5.size(), 0UL);
  EXPECT_FALSE(q6.empty());
  EXPECT_EQ(q6.size(), 3UL);
  EXPECT_DOUBLE_EQ(q6.front(), 1.1);
  EXPECT_DOUBLE_EQ(q6.back(), 3.3);
}

TEST(QueueTest, Front) {
  s21::queue<char> q1{'a', 'b', 'c'};
  EXPECT_EQ(q1.front(), 'a');

  s21::queue<int> q2{1, 2, 3};
  EXPECT_EQ(q2.front(), 1);

  s21::queue<double> q3{1.1, 2.2, 3.3};
  EXPECT_DOUBLE_EQ(q3.front(), 1.1);
}

TEST(QueueTest, Back) {
  s21::queue<char> q1{'a', 'b', 'c'};
  EXPECT_EQ(q1.back(), 'c');

  s21::queue<int> q2{1, 2, 3};
  EXPECT_EQ(q2.back(), 3);

  s21::queue<double> q3{1.1, 2.2, 3.3};
  EXPECT_DOUBLE_EQ(q3.back(), 3.3);
}

TEST(QueueTest, Empty) {
  s21::queue<char> q1;
  EXPECT_TRUE(q1.empty());
  q1.push('a');
  EXPECT_FALSE(q1.empty());

  s21::queue<int> q2;
  EXPECT_TRUE(q2.empty());
  q2.push(42);
  EXPECT_FALSE(q2.empty());

  s21::queue<double> q3;
  EXPECT_TRUE(q3.empty());
  q3.push(3.14);
  EXPECT_FALSE(q3.empty());
}

TEST(QueueTest, Size) {
  s21::queue<char> q1{'a', 'b', 'c'};
  EXPECT_EQ(q1.size(), 3UL);
  q1.pop();
  EXPECT_EQ(q1.size(), 2UL);

  s21::queue<int> q2{1, 2, 3};
  EXPECT_EQ(q2.size(), 3UL);
  q2.pop();
  EXPECT_EQ(q2.size(), 2UL);

  s21::queue<double> q3{1.1, 2.2, 3.3};
  EXPECT_EQ(q3.size(), 3UL);
  q3.pop();
  EXPECT_EQ(q3.size(), 2UL);
}

TEST(QueueTest, Push) {
  s21::queue<char> q1;
  q1.push('a');
  EXPECT_FALSE(q1.empty());
  EXPECT_EQ(q1.size(), 1UL);
  EXPECT_EQ(q1.front(), 'a');
  EXPECT_EQ(q1.back(), 'a');
  q1.push('b');
  EXPECT_EQ(q1.size(), 2UL);
  EXPECT_EQ(q1.front(), 'a');
  EXPECT_EQ(q1.back(), 'b');

  s21::queue<int> q2;
  q2.push(42);
  EXPECT_FALSE(q2.empty());
  EXPECT_EQ(q2.size(), 1UL);
  EXPECT_EQ(q2.front(), 42);
  EXPECT_EQ(q2.back(), 42);
  q2.push(13);
  EXPECT_EQ(q2.size(), 2UL);
  EXPECT_EQ(q2.front(), 42);
  EXPECT_EQ(q2.back(), 13);

  s21::queue<double> q3;
  q3.push(3.14);
  EXPECT_FALSE(q3.empty());
  EXPECT_EQ(q3.size(), 1UL);
  EXPECT_DOUBLE_EQ(q3.front(), 3.14);
  EXPECT_DOUBLE_EQ(q3.back(), 3.14);
  q3.push(2.71);
  EXPECT_EQ(q3.size(), 2UL);
  EXPECT_DOUBLE_EQ(q3.front(), 3.14);
  EXPECT_DOUBLE_EQ(q3.back(), 2.71);
}

TEST(QueueTest, Pop) {
  s21::queue<char> q1{'a', 'b', 'c'};
  q1.pop();
  EXPECT_EQ(q1.size(), 2UL);
  EXPECT_EQ(q1.front(), 'b');
  q1.pop();
  EXPECT_EQ(q1.size(), 1UL);
  EXPECT_EQ(q1.front(), 'c');
  q1.pop();
  EXPECT_TRUE(q1.empty());

  s21::queue<int> q2{1, 2, 3};
  q2.pop();
  EXPECT_EQ(q2.size(), 2UL);
  EXPECT_EQ(q2.front(), 2);
  q2.pop();
  EXPECT_EQ(q2.size(), 1UL);
  EXPECT_EQ(q2.front(), 3);
  q2.pop();
  EXPECT_TRUE(q2.empty());

  s21::queue<double> q3{1.1, 2.2, 3.3};
  q3.pop();
  EXPECT_EQ(q3.size(), 2UL);
  EXPECT_DOUBLE_EQ(q3.front(), 2.2);
  q3.pop();
  EXPECT_EQ(q3.size(), 1UL);
  EXPECT_DOUBLE_EQ(q3.front(), 3.3);
  q3.pop();
  EXPECT_TRUE(q3.empty());
}

TEST(QueueTest, Swap) {
  s21::queue<char> q1{'a', 'b', 'c'};
  s21::queue<char> q2{'x', 'y', 'z'};
  q1.swap(q2);
  EXPECT_EQ(q1.size(), 3UL);
  EXPECT_EQ(q1.front(), 'x');
  EXPECT_EQ(q1.back(), 'z');
  EXPECT_EQ(q2.size(), 3UL);
  EXPECT_EQ(q2.front(), 'a');
  EXPECT_EQ(q2.back(), 'c');

  s21::queue<int> q3{1, 2, 3};
  s21::queue<int> q4{4, 5, 6};
  q3.swap(q4);
  EXPECT_EQ(q3.size(), 3UL);
  EXPECT_EQ(q3.front(), 4);
  EXPECT_EQ(q3.back(), 6);
  EXPECT_EQ(q4.size(), 3UL);
  EXPECT_EQ(q4.front(), 1);
  EXPECT_EQ(q4.back(), 3);

  s21::queue<double> q5{1.1, 2.2, 3.3};
  s21::queue<double> q6{4.4, 5.5, 6.6};
  q5.swap(q6);
  EXPECT_EQ(q5.size(), 3UL);
  EXPECT_DOUBLE_EQ(q5.front(), 4.4);
  EXPECT_DOUBLE_EQ(q5.back(), 6.6);
  EXPECT_EQ(q6.size(), 3UL);
  EXPECT_DOUBLE_EQ(q6.front(), 1.1);
  EXPECT_DOUBLE_EQ(q6.back(), 3.3);
}

TEST(QueueTest, InsertManyBack) {
  s21::queue<int> my_queue;

  my_queue.insert_many_back(1, 2, 3);

  ASSERT_EQ(my_queue.size(), 3UL);
  EXPECT_EQ(my_queue.front(), 1);

  my_queue.push(4);

  my_queue.insert_many_back(5, 6);

  ASSERT_EQ(my_queue.size(), 6UL);
  EXPECT_EQ(my_queue.front(), 1);
  EXPECT_EQ(my_queue.back(), 6);
}
TEST(QueueTest, SomeFunctions) {
  s21::queue<int> my_queue;
  s21::queue<int> my_queue2;

  my_queue.insert_many_back(1, 2, 3);
  my_queue2 = my_queue;

  ASSERT_EQ(my_queue.size(), my_queue2.size());
  EXPECT_EQ(my_queue.front(), my_queue2.front());
  my_queue.push(4);
  my_queue.insert_many_back(5, 6);
  my_queue2 = my_queue;
  ASSERT_EQ(my_queue.size(), my_queue2.size());
  EXPECT_EQ(my_queue.front(), my_queue2.front());
  EXPECT_EQ(my_queue.back(), my_queue2.back());
}
