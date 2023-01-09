// Copyright [year] <Copyright Owner>
#include "../includes/test_list.h"

#include <gtest/gtest.h>

#include <list>

#include "../../includes/list.h"
// #include <list>
// #include <sstream>
// #include <string>

template <typename T>
void print_list(T const &lst) {
  std::cout << "\n" << std::endl;
  for (auto const &value : lst) std::cout << value << std::endl;
}

TEST_F(TestList, Foo1) { ASSERT_EQ(1, 1); }

// -------------------------------------------------------

TEST_F(TestList, Erase) {
  s21::List<int> lst{1, 2, 3};

  s21::List<int>::iterator lst_iter = lst.begin();

  ASSERT_EQ(*lst_iter, 1);
  ++lst_iter;
  ASSERT_EQ(*lst_iter, 2);

  lst_iter = lst.erase(lst_iter);
  ASSERT_EQ(*lst_iter, 3);

  lst_iter = lst.begin();
  ASSERT_EQ(*lst_iter, 1);

  ++lst_iter;

  ASSERT_EQ(*lst_iter, 3);
  ASSERT_EQ(lst.size(), 2);

  lst_iter = lst.begin();

  lst_iter = lst.erase(lst_iter);
  ASSERT_EQ(*lst_iter, 3);
  ASSERT_EQ(lst.font(), 3);

  lst_iter = lst.begin();

  lst_iter = lst.erase(lst_iter);

  ASSERT_EQ(lst_iter, lst.end());
  ASSERT_EQ(lst_iter, lst.begin());
  ASSERT_EQ(lst.begin(), lst.end());

  lst_iter = lst.begin();

  lst.erase(lst_iter);  // Orignal erase last point (head, end) !!!

  ASSERT_EQ(lst.begin(), lst.end());
}

TEST_F(TestList, Clear) {
  s21::List<int> lst{1, 2, 3};

  ASSERT_EQ(lst.size(), 3);

  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  ASSERT_EQ(lst.begin(), lst.end());
  ASSERT_EQ(lst.size(), 0);

  /* *****  ***** */

  lst.push_back(8);

  ASSERT_NE(lst.size(), 0);
  ASSERT_EQ(lst.font(), 8);
  ASSERT_EQ(lst.size(), 1);

  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  ASSERT_EQ(lst.begin(), lst.end());
  ASSERT_EQ(lst.size(), 0);

  /* *****  ***** */

  lst.push_back(3);
  lst.push_back(7);
  lst.push_back(6);

  ASSERT_NE(lst.size(), 0);
  ASSERT_EQ(lst.font(), 3);
  ASSERT_EQ(lst.size(), 3);

  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  ASSERT_EQ(lst.begin(), lst.end());
  ASSERT_EQ(lst.size(), 0);
}

// -------------------------------------------------------

TEST_F(TestList, IsEmpty) {
  s21::List<int> lst;
  s21::List<int> lst2;
  // std::list<int> orig{1, 2, 3};

  ASSERT_NE(lst.empty(), 0);
  ASSERT_EQ(lst.empty(), 1);

  lst.push_back(1);
  ASSERT_EQ(lst.empty(), 0);

  lst.push_back(2);
  ASSERT_EQ(lst.empty(), 0);

  /* *****  ***** */

  ASSERT_EQ(lst2.empty(), 1);

  lst2.push_front(8);
  ASSERT_EQ(lst2.empty(), 0);

  lst2.push_front(7);
  ASSERT_EQ(lst2.empty(), 0);
}

// -------------------------------------------------------

TEST_F(TestList, FontAndBack) {
  s21::List<int> lst{1};

  ASSERT_EQ(lst.font(), 1);
  ASSERT_EQ(lst.size(), 1);

  lst.push_back(8);
  lst.push_back(9);
  ASSERT_EQ(lst.size(), 3);
  ASSERT_EQ(lst.font(), 1);
}

// -------------------------------------------------------

TEST_F(TestList, Insert) {
  // std::list<std::string> orig{"1", "2"};
  // s21::List<std::string> lst;

  // lst.insert(lst.begin(), "1");
  // lst.insert(lst.begin(), "2");

  //   auto iter = lst.end();
  //   --iter;
  //
  //   std::cout << "iter: " << std::endl;

  // lst.insert(lst.begin(), "1");
  // lst.insert(lst.begin(), "2");
  // lst.insert(lst.begin(), "3");

  // std::cout << lst << std::endl;
}

// -------------------------------------------------------

TEST_F(TestList, Decrement) {
  s21::List<int> lst{1, 2, 3};

  ASSERT_EQ(lst.size(), 3);
  lst.push_back(4);
  lst.push_back(5);

  ASSERT_EQ(lst.size(), 5);

  s21::List<int>::iterator iter = lst.begin();

  ASSERT_EQ(*iter, 1);

  --iter;
  --iter;
  ASSERT_EQ(*iter, 5);

  --iter;
  ASSERT_EQ(*iter, 4);

  --iter;
  ASSERT_EQ(*iter, 3);

  --iter;
  ASSERT_EQ(*iter, 2);

  --iter;
  ASSERT_EQ(*iter, 1);

  --iter;
  --iter;
  ASSERT_EQ(*iter, 5);
}

// -------------------------------------------------------

TEST_F(TestList, Increment) {
  s21::List<int> lst{1, 2, 3};

  ASSERT_EQ(lst.size(), 3);
  lst.push_back(4);
  lst.push_back(5);

  ASSERT_EQ(lst.size(), 5);

  s21::List<int>::iterator iter = lst.begin();

  ASSERT_EQ(*iter, 1);

  ++iter;
  ASSERT_EQ(*iter, 2);

  ++iter;
  ASSERT_EQ(*iter, 3);

  ++iter;
  ASSERT_EQ(*iter, 4);

  ++iter;
  ASSERT_EQ(*iter, 5);

  ++iter;
  ++iter;
  ASSERT_EQ(*iter, 1);
  ASSERT_NE(*iter, 2);

  ++iter;
  ASSERT_EQ(*iter, 2);
}

// -------------------------------------------------------

// TEST_F(TestList, Constructs) {
//     s21::List<std::string> lst{"33"};
//
//     s21::List<std::string>::iterator iter = lst.begin();
//
//     for (int i = 0; i < 10; i++) {
//         std::cout << *iter << std::endl;
//         ++iter;
//     }
// }
//
// // -------------------------------------------------------
//
// TEST_F(TestList, PushFrontBack) {
//   s21::List<int> lst;
//
//   ASSERT_EQ(lst.empty(), 1);
//
//   /* *****  ***** */
//
//   lst.push_front(3);
//   lst.push_front(4);
//   lst.push_front(5);
//
//   ASSERT_EQ(lst.size() == 3, 1);
//
//   // /* *****  ***** */
//
//   lst.push_back(9);
//   lst.push_back(8);
//   lst.push_back(7);
//
//   std::stringstream ss;
//   for (auto &i : lst) {
//     ss << i;
//   }
//
//   ASSERT_EQ(ss.str() == "543987", 1);
// }
//
// // -------------------------------------------------------
//
// TEST_F(TestList, IterIncrement) {
//   s21::List<int> lst;
//   ASSERT_EQ(lst.empty(), 1);
//
//   /* *****  ***** */
//
//   lst.push_front(1);
//   lst.push_front(2);
//   lst.push_front(3);
//   lst.push_front(4);
//   lst.push_front(5);
//   lst.push_front(6);
//
//   s21::List<int>::iterator iter = lst.begin();
//
//   ASSERT_EQ(*iter, 6);
//   iter++;
//
//   ASSERT_EQ(*iter, 5);
//   iter++;
//   ASSERT_EQ(*iter, 4);
//
//   iter++;
//   ASSERT_EQ(*iter, 3);
//
//   iter++;
//   ASSERT_EQ(*iter, 2);
//
//   iter++;
//   ASSERT_EQ(*iter, 1);
// }
//
// // -------------------------------------------------------
//
// TEST_F(TestList, IterDecrement) {
//   // s21::List<int> lst{3, 4, 5};
//   // ASSERT_EQ(lst.empty(), 0);
//
//   // /* *****  ***** */
//
//   // lst.push_back(6);
//   // lst.push_back(7);
//   // lst.push_front(2);
//   // lst.push_front(1);
//
//   // std::stringstream ss;
//   // for (auto &i : lst) {
//   //     ss << i;
//   // }
//
//   // ASSERT_EQ(ss.str() == "1234567", 1);
//   // ASSERT_EQ(lst.size(), 7);
//
//   // s21::List<int>::Iterator iter = lst.begin();
//
//   s21::List<std::string> lst{"3", "4", "5"};
//   std::list<std::string> orig{"3", "4", "5"};
//
//
//   lst.push_back("9");
//   lst.push_back("8");
//   lst.push_back("7");
//
//   lst.push_front("11");
//   lst.push_front("22");
//   lst.push_front("33");
//
//   orig.push_back("9");
//   orig.push_back("8");
//   orig.push_back("7");
//
//   orig.push_front("1");
//   orig.push_front("2");
//   orig.push_front("3");
//
//   std::cout << "lst: " << lst << "\n\n" << std::endl;
//   auto end_iter = lst.end();
//   (void)end_iter;
//
//   // auto orig_iter = orig.begin();
//   s21::List<std::string>::iterator iter = lst.begin();
//   // std::cout << "orig_iter: " << *orig_iter << std::endl;
//   // std::cout << "iter: " << *iter << std::endl;
//
//   // for (int i = 0; i < 20; ++i) {
//   //   std::cout << "orig_iter: " << *orig_iter << std::endl;
//   //   std::cout << "&orig_iter: " << &*orig_iter << std::endl;
//   //   ++orig_iter;
//   // }
//
//   for (int i = 0; i < 20; ++i) {
//     std::cout << "iter: " << *iter << std::endl;
//     std::cout << "&iter: " << &*iter << std::endl;
//     ++iter;
//   }
//
//   // std::cout << "\n\n" << std::endl;
//   // for (int i = 0; i < 20; ++i) {
//   //   std::cout << "orig_iter: " << *orig_iter << std::endl;
//   //   std::cout << "&orig_iter: " << &*orig_iter << std::endl;
//   //   ++orig_iter;
//   // }
// }
//
// // -------------------------------------------------------
//
// TEST_F(TestList, IteratorInitizlizer) {
//   s21::List<std::string> lst{"1", "2", "3"};
//   std::stringstream ss;
//   ASSERT_EQ(lst.empty(), 0);
//
//   lst.push_back("9");
//   lst.push_back("8");
//   lst.push_back("7");
//
//   ASSERT_EQ(lst.size(), 6);
//   for (auto &i : lst) {
//     ss << i;
//   }
//
//   ASSERT_EQ(ss.str() == "123987", 1);
//
//   lst.push_front("6");
//   lst.push_front("5");
//   lst.push_front("4");
//
//   ss << "456";
//   ASSERT_EQ(ss.str() == "123987456", 1);
//   ASSERT_EQ(lst.size(), 9);
// }
//
// // -------------------------------------------------------
//
// TEST_F(TestList, IteratorConst) {
//   const s21::List<std::string> lst{"1", "2", "3"};
//
//   s21::List<std::string>::iterator iter = lst.begin();
//
//   std::cout << "before: " << *iter << std::endl;
//   *iter = "There is no spoon.!!";
//   std::cout << "after: " << *iter << std::endl;
// }

// -------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
