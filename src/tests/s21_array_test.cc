#include "s21_test.h"

// Member function

TEST(Array_Member_functions, Data_Zero_Size_And_Empty) {
  s21::array<int, 0> data_int;
  s21::array<double, 0> data_double;
  s21::array<std::string, 0> data_string;

  EXPECT_EQ(data_int.empty(), 1);
  EXPECT_EQ(data_double.empty(), 1);
  EXPECT_EQ(data_string.empty(), 1);
}

TEST(Array_Member_functions, Data_Not_Zero_Size_And_Empty) {
  s21::array<int, 7> data_int;
  s21::array<double, 7> data_double;
  s21::array<std::string, 7> data_string;

  EXPECT_EQ(data_int.empty(), 0);
  EXPECT_EQ(data_double.empty(), 0);
  EXPECT_EQ(data_string.empty(), 0);
}

TEST(Array_Member_functions, Data_Initializer_List) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 7};
  s21::array<double, 7> data_double{1.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ((int)data_int.size(), 7);
  EXPECT_EQ((int)data_double.size(), 7);
  EXPECT_EQ((int)data_string.size(), 3);
}

TEST(Array_Member_functions, Data_Copy) {
  s21::array<int, 5> data = {1, 2, 3, 4, 5};
  s21::array<int, 5> copy(data);

  EXPECT_EQ((int)copy.size(), 5);
}

TEST(Array_Member_functions, Data_Move) {
  s21::array<int, 5> data = {1, 2, 3, 4, 5};
  s21::array<int, 5> move(std::move(data));
  std::cout << data.empty() << std::endl;
  EXPECT_EQ(data.empty(), 1);
  EXPECT_EQ((int)move.size(), 5);
}

TEST(Array_Member_functions, Operator_Eq) {
  s21::array<int, 3> data = {1, 2, 3};
  s21::array<int, 3> move;
  move = std::move(data);

  EXPECT_EQ((int)move.size(), 3);
}

// Element access

TEST(Array_Element_Access, Element_At) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 7};
  s21::array<double, 7> data_double{1.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ(data_int.at(1), 2);
  EXPECT_EQ(data_double.at(1), 2.8);
  EXPECT_EQ(data_string.at(1), "for");
}

TEST(Array_Element_Access, Element_At_OutOfRange) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 7};
  s21::array<double, 7> data_double{1.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_THROW(data_int.at(15), std::out_of_range);
  EXPECT_THROW(data_double.at(15), std::out_of_range);
  EXPECT_THROW(data_string.at(15), std::out_of_range);
}

TEST(Array_Element_Access, Element_Operator_At) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 7};
  s21::array<double, 7> data_double{1.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ(data_int[6], 7);
  EXPECT_EQ(data_double[6], 7.3);
  EXPECT_EQ(data_string[2], "array");
}

TEST(Array_Element_Access, Element_Operator_At_OutOfRange) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 7};
  s21::array<double, 7> data_double{1.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_THROW(data_int[15], std::out_of_range);
  EXPECT_THROW(data_double[15], std::out_of_range);
  EXPECT_THROW(data_string[5], std::out_of_range);
}

TEST(Array_Element_Access, Element_Front) {
  s21::array<int, 7> data_int = {11, 2, 3, 4, 5, 6, 7};
  s21::array<double, 7> data_double{11.9, 2.8, 3.7, 4.6, 5.5, 6.4, 7.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ(data_int.front(), 11);
  EXPECT_EQ(data_double.front(), 11.9);
  EXPECT_EQ(data_string.front(), "Test");
}

TEST(Array_Element_Access, Element_Back) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 77};
  s21::array<double, 7> data_double{11.9, 2.8, 3.7, 4.6, 5.5, 6.4, 77.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ(data_int.back(), 77);
  EXPECT_EQ(data_double.back(), 77.3);
  EXPECT_EQ(data_string.back(), "array");
}

TEST(Array_Element_Access, Element_Data) {
  s21::array<int, 7> data = {1, 2, 3, 4, 5, 6, 7};
  int* value = data.data();

  EXPECT_EQ(value[0], 1);
}

// Iterators

TEST(Array_Iterators, Element_Begin) {
  s21::array<int, 7> data = {1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ(*(data.begin()), 1);
}

TEST(Array_Iterators, Element_End) {
  s21::array<int, 7> data = {1, 2, 3, 4, 5, 6, 7};

  EXPECT_EQ(data.end(), data.begin() + 7);
}

// Capacity

TEST(Array_Capacity, Capacity_Empty) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 77};
  s21::array<double, 7> data_double{11.9, 2.8, 3.7, 4.6, 5.5, 6.4, 77.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ(data_int.empty(), 0);
  EXPECT_EQ(data_double.empty(), 0);
  EXPECT_EQ(data_string.empty(), 0);
}

TEST(Array_Capacity, Capacity_Size) {
  s21::array<int, 7> data_int = {1, 2, 3, 4, 5, 6, 77};
  s21::array<double, 7> data_double{11.9, 2.8, 3.7, 4.6, 5.5, 6.4, 77.3};
  s21::array<std::string, 3> data_string = {"Test", "for", "array"};

  EXPECT_EQ((int)data_int.size(), 7);
  EXPECT_EQ((int)data_double.size(), 7);
  EXPECT_EQ((int)data_string.size(), 3);
}

TEST(Array_Capacity, Capacity_Max_Size) {
  s21::array<int, 9> data_int = {1, 2, 3, 4, 5, 6, 77};
  s21::array<double, 10> data_double{11.9, 2.8, 3.7, 4.6, 5.5, 6.4, 77.3};
  s21::array<std::string, 5> data_string = {"Test", "for", "array"};

  EXPECT_EQ((int)data_int.max_size(), 9);
  EXPECT_EQ((int)data_double.max_size(), 10);
  EXPECT_EQ((int)data_string.max_size(), 5);
}

// Modifiers

TEST(Array_Modifiers, Modifiers_Swap) {
  s21::array<int, 3> data = {12, 23, 34};
  s21::array<int, 3> data2 = {45, 56, 67};
  data.swap(data2);

  EXPECT_EQ(data.front(), 45);
  EXPECT_EQ(data.back(), 67);
  EXPECT_EQ(data2.front(), 12);
  EXPECT_EQ(data2.back(), 34);
}

TEST(Array_Modifiers, Modifiers_Fill) {
  s21::array<int, 3> data = {17, 26, 35};
  data.fill(52);

  EXPECT_EQ(data.front(), 52);
  EXPECT_EQ(data.back(), 52);
}
