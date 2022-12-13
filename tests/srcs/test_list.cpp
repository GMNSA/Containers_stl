#include "test_list.hpp"
#include <gtest/gtest.h>
#include <string>


TEST_F(TestList, Foo1) {
    ASSERT_EQ(1 == 1, 1);
}

// -------------------------------------------------------


// -------------------------------------------------------

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
