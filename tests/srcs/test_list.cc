// Copyright [year] <Copyright Owner>
#include "../includes/test_list.h"

#include <gtest/gtest.h>

#include <iterator>
#include <list>

#include "../../includes/list.h"
// #include <list>
// #include <sstream>
// #include <string>

template <typename T>
void print_list(T const &lst, std::string const &msg) {
  std::cout << "\nmessage: " << msg << std::endl;
  for (auto const &value : lst) std::cout << value << std::endl;
}

TEST_F(TestList, Foo1) { ASSERT_EQ(1, 1); }

// -------------------------------------------------------

TEST_F(TestList, Splice) {
  std::list<int> orig{1, 2, 3};
  std::list<int> pick{8, 9, 7, 6};

  s21::List<int> lst{1, 2, 3};
  s21::List<int> lst_pick{8, 9, 7, 6};

  auto iter_orig = orig.begin();
  auto lst_iter = lst.begin();

  orig.splice(iter_orig, pick);
  lst.splice(lst_iter, lst_pick);

  ASSERT_EQ(*iter_orig, *lst_iter);

  ASSERT_EQ(lst_pick.size(), 0);

  ++iter_orig;
  ++lst_iter;
  ASSERT_EQ(*iter_orig, *lst_iter);

  ++iter_orig;
  ++lst_iter;
  ASSERT_EQ(*iter_orig, *lst_iter);

  ++iter_orig;  // trash
  ++lst_iter;   // trash

  ++iter_orig;
  ++lst_iter;
  ASSERT_EQ(*iter_orig, *lst_iter);

  ++iter_orig;
  ++lst_iter;
  ASSERT_EQ(*iter_orig, *lst_iter);

  ++iter_orig;
  ++lst_iter;
  ASSERT_EQ(*iter_orig, *lst_iter);

  ++iter_orig;
  ++lst_iter;
  ASSERT_EQ(*iter_orig, *lst_iter);

  ASSERT_EQ(lst.size(), orig.size());

  /* *****  ***** */

  // TODO(probiuss): Release next test for splice
  // lst.assign({1});

  // ASSERT_EQ(lst.size(), 1);
  // print_list(lst, "list");
}

// -------------------------------------------------------

TEST_F(TestList, AssignInitializer) {
  s21::List<int> lst{1, 2, 3};

  lst.assign({3, 4, 5});
  ASSERT_EQ(lst.size(), 3);

  auto iter = lst.begin();

  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 4);
  ++iter;
  ASSERT_EQ(*iter, 5);
  ++iter;  // trash
  ++iter;
  ASSERT_EQ(*iter, 3);
  ++iter;
  ASSERT_EQ(*iter, 4);

  /* *****  ***** */

  lst.assign({0});
  ASSERT_EQ(lst.size(), 1);

  iter = lst.begin();
  ASSERT_EQ(*iter, 0);
  ++iter;  // trash
  ++iter;
  ASSERT_EQ(*iter, 0);

  /* *****  ***** */

  lst.assign({1, 2});
  ASSERT_EQ(lst.size(), 2);

  iter = lst.begin();
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);
  ++iter;  // trash
  ++iter;
  ASSERT_EQ(*iter, 1);
  ++iter;
  ASSERT_EQ(*iter, 2);

  /* *****  ***** */

  lst.assign({});
  ASSERT_EQ(lst.size(), 0);
  iter = lst.begin();
  ASSERT_EQ(*iter, 0);  // trash
  ++iter;
  ASSERT_EQ(*iter, 0);  // trash
}

// -------------------------------------------------------

TEST_F(TestList, AssignElem) {
  std::list<std::string> orig{"1", "2"};
  s21::List<std::string> lst{"1", "2"};

  orig.assign(3, "88");
  lst.assign(3, "88");

  ASSERT_EQ(lst.size(), 3);

  auto iter = lst.begin();

  ASSERT_NE(*iter, "1");
  ASSERT_EQ(*iter, "88");
  ++iter;
  ASSERT_EQ(*iter, "88");
  ++iter;
  ASSERT_EQ(*iter, "88");

  ++iter;  // trash

  ++iter;
  ASSERT_EQ(*iter, "88");
  ++iter;
  ASSERT_EQ(*iter, "88");

  /* *****  ***** */

  lst.assign(2, "19");
  ASSERT_EQ(lst.size(), 2);
  iter = lst.begin();
  ASSERT_NE(*iter, "88");
  ASSERT_EQ(*iter, "19");
  ++iter;
  ASSERT_EQ(*iter, "19");

  ++iter;  // trash

  ++iter;
  ASSERT_EQ(*iter, "19");

  /* *****  ***** */

  lst.assign(0, "1");
  ASSERT_EQ(lst.size(), 0);
  iter = lst.begin();
  ASSERT_EQ(*iter, "");  // trash
  ++iter;
  ASSERT_EQ(*iter, "");  // trash
}

// -------------------------------------------------------

TEST_F(TestList, Max_size) {
  std::list<int> orig{1, 2, 3};
  s21::List<int> lst{1, 2, 3};

  ASSERT_EQ(orig.max_size(), lst.max_size());

  /* *****  ***** */

  std::list<std::string> orig1{"there", "is", "no", "spoon."};
  s21::List<std::string> lst1{"there", "is", "no", "spoon."};

  ASSERT_EQ(orig1.max_size(), lst1.max_size());

  /* *****  ***** */

  std::list<double> orig2{8.0012, 889.43};
  s21::List<double> lst2{8.0012, 889.43};

  ASSERT_EQ(orig2.max_size(), lst2.max_size());

  /* *****  ***** */

  std::list<float> orig3;
  s21::List<float> lst3;

  ASSERT_EQ(orig3.max_size(), lst3.max_size());
}

// -------------------------------------------------------

TEST_F(TestList, ReverseIteratorIncrement) {
  // TODO(probiuss): Release and tests reverse_iterator
  std::list<int> orig{1, 2, 3};
  s21::List<int> lst{1, 2, 3};

  std::list<int>::reverse_iterator orig_iter = orig.rbegin();
  s21::List<int>::reverse_iterator iter = lst.rbegin();

  ASSERT_EQ(*iter, *orig_iter);
  ++orig_iter;
  ++iter;

  ASSERT_EQ(*iter, *orig_iter);

  ++orig_iter;
  ++iter;
  ASSERT_EQ(*iter, *orig_iter);

  ++orig_iter;  // trash
  ++iter;       // trash

  ++orig_iter;
  ++iter;
  ASSERT_EQ(*iter, *orig_iter);
}

// -------------------------------------------------------

TEST_F(TestList, ReverseIteratorDecrement) {
  // TODO(probiuss): Release and tests reverse_iterator
  std::list<int> orig{1, 2, 3};
  s21::List<int> lst{1, 2, 3};

  std::list<int>::reverse_iterator orig_iter = orig.rend();
  s21::List<int>::reverse_iterator iter = lst.rend();

  --orig_iter;
  --iter;
  ASSERT_EQ(*iter, *orig_iter);

  --orig_iter;
  --iter;
  ASSERT_EQ(*iter, *orig_iter);

  --orig_iter;
  --iter;
  ASSERT_EQ(*iter, *orig_iter);

  --orig_iter;  // trash
  --iter;       // trash

  --orig_iter;
  --iter;
  ASSERT_EQ(*iter, *orig_iter);

  --orig_iter;
  --iter;
  ASSERT_EQ(*iter, *orig_iter);

  ++orig_iter;
  ++iter;
  ASSERT_EQ(*iter, *orig_iter);
}

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

// -------------------------------------------------------

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
  std::list<int> orig{1, 2, 3};
  s21::List<int> lst{1, 2, 3};

  orig.insert(orig.begin(), {8, 9, 2});
  s21::List<int>::iterator res = lst.insert(lst.begin(), {8, 9, 2});

  ASSERT_EQ(*res, 8);
  ASSERT_EQ(lst.font(), 8);
  ASSERT_EQ(lst.back(), 3);
  ASSERT_EQ(lst.size(), 6);

  res = lst.insert(lst.begin(), 99);
  ASSERT_EQ(*res, 99);
  ASSERT_EQ(lst.size(), 7);

  /* *****  ***** */

  res = lst.insert(lst.end(), 98);
  ASSERT_EQ(*res, 98);
  ASSERT_EQ(lst.size(), 8);
  ASSERT_EQ(lst.font(), 99);
  ASSERT_EQ(lst.back(), 98);

  /* *****  ***** */

  s21::List<int>::iterator iter = lst.begin();

  ++iter;

  res = lst.insert(iter, 87);
  ASSERT_EQ(lst.size(), 9);
  ASSERT_NE(*res, 88);
  ASSERT_EQ(*res, 87);
  ASSERT_EQ(lst.font(), 99);
  ASSERT_EQ(lst.back(), 98);

  /* *****  ***** */

  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  res = lst.insert(lst.begin(), 1);
  ASSERT_EQ(lst.size(), 1);
  ASSERT_EQ(*res, 1);
  ASSERT_EQ(lst.font(), 1);
  ASSERT_EQ(lst.back(), 1);

  /* *****  ***** */

  lst.clear();
  ASSERT_EQ(lst.size(), 0);
  res = lst.insert(lst.end(), 9);
  ASSERT_EQ(lst.size(), 1);
  ASSERT_EQ(*res, 9);
  ASSERT_EQ(lst.font(), 9);
  ASSERT_EQ(lst.back(), 9);

  /* *****  ***** */

  lst.clear();
  lst.insert(lst.begin(), 2, 7);
}

// -------------------------------------------------------

TEST_F(TestList, InsertCountValue) {
  s21::List<int> lst{1, 2, 3};
  std::list<int> orig{1, 2, 3};

  lst.insert(lst.begin(), 2, 7);
  orig.insert(orig.begin(), 2, 7);

  s21::List<int>::iterator iter = lst.begin();
  auto orig_iter = orig.begin();
  orig_iter++;
  orig_iter++;
  ++iter;
  ++iter;

  std::advance(iter, 0);  // need difference_type
  std::advance(orig_iter, 0);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, 2);
  std::advance(iter, 2);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, 1);  // trash
  std::advance(iter, 1);       // trash

  std::advance(orig_iter, 4);
  std::advance(iter, 4);
  ASSERT_EQ(*iter, *orig_iter);

  lst.insert(lst.begin(), 8, 3);
  orig.insert(orig.begin(), 8, 3);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, 6);
  std::advance(iter, 6);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, 2);
  std::advance(iter, 2);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, 1);
  std::advance(iter, 1);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, -9);
  std::advance(iter, -9);
  ASSERT_EQ(*iter, *orig_iter);

  /* *****  ***** */

  lst.insert(lst.begin(), {11, 12, 13});
  orig.insert(orig.begin(), {11, 12, 13});

  std::advance(orig_iter, 1);
  std::advance(iter, 1);
  ASSERT_EQ(*iter, *orig_iter);

  std::advance(orig_iter, 3);
  std::advance(iter, 3);
  ASSERT_EQ(*iter, *orig_iter);
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

TEST_F(TestList, Constructs) {
  // TODO(probiuss): release tests for constructs of list
  // s21::List<std::string> lst{"33"};

  // s21::List<std::string>::iterator iter = lst.begin();

  // for (int i = 0; i < 10; i++) {
  //   std::cout << *iter << std::endl;
  //   ++iter;
  // }
}

// -------------------------------------------------------

TEST_F(TestList, PushFrontBack) {
  s21::List<int> lst;

  ASSERT_EQ(lst.empty(), 1);

  /* *****  ***** */

  lst.push_front(3);
  lst.push_front(4);
  lst.push_front(5);

  ASSERT_EQ(lst.size() == 3, 1);

  // /* *****  ***** */

  lst.push_back(9);
  lst.push_back(8);
  lst.push_back(7);

  std::stringstream ss;
  for (auto const &i : lst) {
    ss << i;
  }

  ASSERT_EQ(ss.str() == "543987", 1);
}

// -------------------------------------------------------

TEST_F(TestList, IterIncrement) {
  s21::List<int> lst;
  ASSERT_EQ(lst.empty(), 1);

  /* *****  ***** */

  lst.push_front(1);
  lst.push_front(2);
  lst.push_front(3);
  lst.push_front(4);
  lst.push_front(5);
  lst.push_front(6);

  s21::List<int>::iterator iter = lst.begin();

  ASSERT_EQ(*iter, 6);
  iter++;

  ASSERT_EQ(*iter, 5);
  iter++;
  ASSERT_EQ(*iter, 4);

  iter++;
  ASSERT_EQ(*iter, 3);

  iter++;
  ASSERT_EQ(*iter, 2);

  iter++;
  ASSERT_EQ(*iter, 1);
}

// -------------------------------------------------------

TEST_F(TestList, IterDecrement) {
  // TODO(probiuss): Release iter decrement of list
  // s21::List<int> lst{3, 4, 5};
  // ASSERT_EQ(lst.empty(), 0);

  // /* *****  ***** */

  // lst.push_back(6);
  // lst.push_back(7);
  // lst.push_front(2);
  // lst.push_front(1);

  // std::stringstream ss;
  // for (auto &i : lst) {
  //     ss << i;
  // }

  // ASSERT_EQ(ss.str() == "1234567", 1);
  // ASSERT_EQ(lst.size(), 7);

  // s21::List<int>::Iterator iter = lst.begin();

  // s21::List<std::string> lst{"3", "4", "5"};
  // std::list<std::string> orig{"3", "4", "5"};

  // lst.push_back("9");
  // lst.push_back("8");
  // lst.push_back("7");

  // lst.push_front("11");
  // lst.push_front("22");
  // lst.push_front("33");

  // orig.push_back("9");
  // orig.push_back("8");
  // orig.push_back("7");

  // orig.push_front("1");
  // orig.push_front("2");
  // orig.push_front("3");

  // std::cout << "lst: " << lst << "\n\n" << std::endl;
  // auto end_iter = lst.end();
  // (void)end_iter;

  // auto orig_iter = orig.begin();
  // s21::List<std::string>::iterator iter = lst.begin();
  // std::cout << "orig_iter: " << *orig_iter << std::endl;
  // std::cout << "iter: " << *iter << std::endl;

  // for (int i = 0; i < 20; ++i) {
  //   std::cout << "orig_iter: " << *orig_iter << std::endl;
  //   std::cout << "&orig_iter: " << &*orig_iter << std::endl;
  //   ++orig_iter;
  // }

  // for (int i = 0; i < 20; ++i) {
  //   std::cout << "iter: " << *iter << std::endl;
  //   std::cout << "&iter: " << &*iter << std::endl;
  //   ++iter;
  // }

  // std::cout << "\n\n" << std::endl;
  // for (int i = 0; i < 20; ++i) {
  //   std::cout << "orig_iter: " << *orig_iter << std::endl;
  //   std::cout << "&orig_iter: " << &*orig_iter << std::endl;
  //   ++orig_iter;
  // }
}

// -------------------------------------------------------

TEST_F(TestList, IteratorInitizlizer) {
  s21::List<std::string> lst{"1", "2", "3"};
  std::stringstream ss;
  ASSERT_EQ(lst.empty(), 0);

  lst.push_back("9");
  lst.push_back("8");
  lst.push_back("7");

  ASSERT_EQ(lst.size(), 6);
  for (auto &i : lst) {
    ss << i;
  }

  ASSERT_EQ(ss.str() == "123987", 1);

  lst.push_front("6");
  lst.push_front("5");
  lst.push_front("4");

  ss << "456";
  ASSERT_EQ(ss.str() == "123987456", 1);
  ASSERT_EQ(lst.size(), 9);
}

// -------------------------------------------------------

TEST_F(TestList, IteratorConst) {
  // TODO(probiuss): Release testt for const iterator
}

// -------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
