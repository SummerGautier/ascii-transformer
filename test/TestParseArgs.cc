#include <gtest/gtest.h>
#include <cstdint>

TEST(TestParseArgs, BasicAssertions) {
  EXPECT_EQ(main (5, "--src file.txt --out file-out.hex --hex"), std::EXIT_SUCCESS);
}