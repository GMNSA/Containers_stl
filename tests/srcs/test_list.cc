#include "test_list.h"
#include <gtest/gtest.h>
#include <string>
#include <list>


#include "list.h"

TEST_F(TestList, Foo1) {
    ASSERT_EQ(1 == 1, 1);
}

// -------------------------------------------------------

TEST_F(TestList, TestList) {
    s21::List<int> lst;
    std::list<int> orig_lst;

    ASSERT_EQ(lst.empty(), 1);
    ASSERT_EQ(orig_lst.empty(), 1);

    /* *****  ***** */

    lst.push_front(3);
    lst.push_front(4);
    lst.push_front(5);

    // ASSERT_EQ(lst.size() == 3, 1);

    // /* *****  ***** */

    // std::cout << lst << std::endl;

    // lst.push_back(9);
    // lst.push_back(8);
    // lst.push_back(7);

    for (auto &i : lst) {
        std::cout << "i: " << i << std::endl;
    }

    for (auto &i : orig_lst) {
        std::cout << "i: " << i << std::endl;
    }

    // const s21::List<int>lst_cns = {1, 1, 2, 3};

}

// -------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
