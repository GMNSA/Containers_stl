// Copyright 2022
#ifndef TESTS_INCLUDES_TEST_LIST_H_
#define TESTS_INCLUDES_TEST_LIST_H_

#include <gtest/gtest.h>

class TestList : public ::testing::Test {
 public:
  TestList() {
    // initialization code here
  }

  void SetUp() {
    // code here will execute just before the test ensues
  }

  void TearDown() {
    // code here will be called just after the test completes
    // ok to through exceptions from here if need be
  }

  ~TestList() {
    // cleanup any pending stuff, but no exceptions allowed
  }

 private:
  // put in any custom data members that you need
};

#endif  // TESTS_INCLUDES_TEST_LIST_H_
