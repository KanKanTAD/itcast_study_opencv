#include <gtest/gtest.h>
#include <iostream>

TEST(test_demo_1, demo1) { EXPECT_EQ(1, 1); }

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
