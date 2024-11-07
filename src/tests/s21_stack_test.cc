#include "s21_test.h"

TEST(StackTest, DefaultConstructor) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());
  EXPECT_EQ(stack.size(), 0UL);
}

TEST(StackTest, InitializerListConstructor) {
  s21::stack<int> stack{1, 2, 3};
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.size(), 3Ul);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, PushAndTop) {
  s21::stack<int> stack;
  stack.push(1);
  EXPECT_FALSE(stack.empty());
  EXPECT_EQ(stack.size(), 1Ul);
  EXPECT_EQ(stack.top(), 1);

  stack.push(2);
  EXPECT_EQ(stack.size(), 2UL);
  EXPECT_EQ(stack.top(), 2);

  stack.push(3);
  EXPECT_EQ(stack.size(), 3UL);
  EXPECT_EQ(stack.top(), 3);
}

TEST(StackTest, Pop) {
  s21::stack<int> stack{1, 2, 3};
  EXPECT_EQ(stack.size(), 3Ul);

  stack.pop();
  EXPECT_EQ(stack.size(), 2UL);
  EXPECT_EQ(stack.top(), 2);

  stack.pop();
  EXPECT_EQ(stack.size(), 1UL);
  EXPECT_EQ(stack.top(), 1);

  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, Swap) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2{4, 5};

  stack1.swap(stack2);

  EXPECT_EQ(stack1.size(), 2UL);
  EXPECT_EQ(stack1.top(), 5);

  EXPECT_EQ(stack2.size(), 3UL);
  EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, Empty) {
  s21::stack<int> stack;
  EXPECT_TRUE(stack.empty());

  stack.push(1);
  EXPECT_FALSE(stack.empty());

  stack.pop();
  EXPECT_TRUE(stack.empty());
}

TEST(StackTest, Size) {
  s21::stack<int> stack;
  EXPECT_EQ(stack.size(), 0UL);

  stack.push(1);
  EXPECT_EQ(stack.size(), 1UL);

  stack.push(2);
  EXPECT_EQ(stack.size(), 2UL);

  stack.pop();
  EXPECT_EQ(stack.size(), 1UL);

  stack.pop();
  EXPECT_EQ(stack.size(), 0UL);
}

TEST(StackTest, Destructor) {
  s21::stack<int>* stack = new s21::stack<int>{1, 2, 3};
  delete stack;
}

TEST(StackTest, MoveConstructor) {
  s21::stack<int> stack1{1, 2, 3};
  s21::stack<int> stack2 = std::move(stack1);

  EXPECT_EQ(stack1.size(), 0UL);
  EXPECT_TRUE(stack1.empty());

  EXPECT_EQ(stack2.size(), 3UL);
  EXPECT_EQ(stack2.top(), 3);
}

TEST(StackTest, CharType) {
  s21::stack<char> stack;
  stack.push('a');
  stack.push('b');
  stack.push('c');

  EXPECT_EQ(stack.top(), 'c');
  stack.pop();
  EXPECT_EQ(stack.top(), 'b');
  stack.pop();
  EXPECT_EQ(stack.top(), 'a');
  stack.pop();
  EXPECT_TRUE(stack.empty());
}

#include <list>
#include <queue>
#include <stack>

TEST(stack, DefaultConstructor) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_EQ(my_stack.empty(), std_stack.empty());
  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(stack, InitializerListConstructor) {
  s21::stack<int> my_stack({1, 2, 3});
  std::stack<int> std_stack({1, 2, 3});

  ASSERT_EQ(my_stack.size(), std_stack.size());
  ASSERT_EQ(my_stack.top(), std_stack.top());
}

TEST(stack, CopyConstructor) {
  s21::stack<int> my_stack_orig;
  my_stack_orig.push(1);
  my_stack_orig.push(2);
  my_stack_orig.push(3);
  s21::stack<int> my_stack_copy(my_stack_orig);
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_stack_copy(std_stack);

  ASSERT_EQ(my_stack_copy.size(), std_stack_copy.size());
  ASSERT_EQ(my_stack_copy.top(), std_stack_copy.top());
}

TEST(stack, MoveConstructor) {
  s21::stack<int> my_stack_orig;
  my_stack_orig.push(1);
  my_stack_orig.push(2);
  my_stack_orig.push(3);
  s21::stack<int> my_stack_move(std::move(my_stack_orig));
  std::stack<int> std_stack;
  std_stack.push(1);
  std_stack.push(2);
  std_stack.push(3);
  std::stack<int> std_stack_move(std::move(std_stack));

  ASSERT_EQ(my_stack_move.size(), std_stack_move.size());
  ASSERT_EQ(my_stack_move.top(), std_stack_move.top());
}

TEST(stack, Destructor) {
  s21::stack<int>* my_stack = new s21::stack<int>({1, 2, 3});
  delete my_stack;
  ASSERT_TRUE(true);
}

TEST(stack, CopyAssignmentOperator) {
  s21::stack<int> my_stack_orig;
  my_stack_orig.push(1);
  my_stack_orig.push(2);
  my_stack_orig.push(3);
  s21::stack<int> my_stack_assign;
  my_stack_assign = my_stack_orig;

  std::stack<int> std_stack_orig;
  std_stack_orig.push(1);
  std_stack_orig.push(2);
  std_stack_orig.push(3);
  std::stack<int> std_stack_assign;
  std_stack_assign = std_stack_orig;

  ASSERT_EQ(my_stack_assign.size(), std_stack_assign.size());
  ASSERT_EQ(my_stack_assign.top(), std_stack_assign.top());
}

TEST(stack, MoveAssignmentOperator) {
  s21::stack<int> my_stack_orig;
  my_stack_orig.push(1);
  my_stack_orig.push(2);
  my_stack_orig.push(3);
  s21::stack<int> my_stack_assign;
  my_stack_assign = std::move(my_stack_orig);

  std::stack<int> std_stack_orig;
  std_stack_orig.push(1);
  std_stack_orig.push(2);
  std_stack_orig.push(3);
  std::stack<int> std_stack_assign;
  std_stack_assign = std::move(std_stack_orig);

  ASSERT_EQ(my_stack_assign.size(), std_stack_assign.size());
  ASSERT_EQ(my_stack_assign.top(), std_stack_assign.top());
}

TEST(stack, TopMethod) {
  s21::stack<int> my_stack;
  my_stack.push(10);
  my_stack.push(20);

  std::stack<int> std_stack;
  std_stack.push(10);
  std_stack.push(20);

  ASSERT_EQ(my_stack.top(), std_stack.top());
}

TEST(stack, EmptyMethod) {
  s21::stack<int> my_stack;
  std::stack<int> std_stack;

  ASSERT_EQ(my_stack.empty(), std_stack.empty());

  my_stack.push(10);
  std_stack.push(10);
  ASSERT_EQ(my_stack.empty(), std_stack.empty());
}

TEST(stack, SizeMethod) {
  s21::stack<int> my_stack;
  my_stack.push(10);
  my_stack.push(20);

  std::stack<int> std_stack;
  std_stack.push(10);
  std_stack.push(20);

  ASSERT_EQ(my_stack.size(), std_stack.size());
}

TEST(stack, PushMethod) {
  s21::stack<int> my_stack;
  my_stack.push(10);
  my_stack.push(20);

  std::stack<int> std_stack;
  std_stack.push(10);
  std_stack.push(20);

  ASSERT_EQ(my_stack.size(), std_stack.size());
  ASSERT_EQ(my_stack.top(), std_stack.top());
}

TEST(stack, PopMethod) {
  s21::stack<int> my_stack;
  my_stack.push(10);
  my_stack.push(20);
  my_stack.pop();

  std::stack<int> std_stack;
  std_stack.push(10);
  std_stack.push(20);
  std_stack.pop();

  ASSERT_EQ(my_stack.size(), std_stack.size());
  if (!my_stack.empty() && !std_stack.empty()) {
    ASSERT_EQ(my_stack.top(), std_stack.top());
  }
}

TEST(stack, SwapMethod) {
  s21::stack<int> my_stack1;
  my_stack1.push(1);
  my_stack1.push(2);
  my_stack1.push(3);
  s21::stack<int> my_stack2;
  my_stack2.push(4);
  my_stack2.push(5);
  my_stack2.push(6);
  my_stack1.swap(my_stack2);

  std::stack<int> std_stack1;
  std_stack1.push(1);
  std_stack1.push(2);
  std_stack1.push(3);
  std::stack<int> std_stack2;
  std_stack2.push(4);
  std_stack2.push(5);
  std_stack2.push(6);
  std_stack1.swap(std_stack2);

  ASSERT_EQ(my_stack1.size(), std_stack1.size());
  ASSERT_EQ(my_stack2.size(), std_stack2.size());
  ASSERT_EQ(my_stack1.top(), std_stack1.top());
  ASSERT_EQ(my_stack2.top(), std_stack2.top());
}

TEST(stack, InsertManyIntoEmptyStack) {
  s21::stack<int> my_stack;
  my_stack.insert_many_back(1, 2, 3);

  ASSERT_EQ(my_stack.size(), 3UL);
  ASSERT_EQ(my_stack.top(), 3);
}

TEST(stack, InsertManyIntoNonEmptyStack) {
  s21::stack<int> my_stack;
  my_stack.push(4);
  my_stack.insert_many_back(1, 2, 3);

  ASSERT_EQ(my_stack.size(), 4UL);
  ASSERT_EQ(my_stack.top(), 3);
}

TEST(stack, InsertSingleElement) {
  s21::stack<int> my_stack;
  my_stack.insert_many_back(42);

  ASSERT_EQ(my_stack.size(), 1UL);
  ASSERT_EQ(my_stack.top(), 42);
}

TEST(stack, InsertNoElements) {
  s21::stack<int> my_stack;
  my_stack.insert_many_back();

  ASSERT_TRUE(my_stack.empty());
}