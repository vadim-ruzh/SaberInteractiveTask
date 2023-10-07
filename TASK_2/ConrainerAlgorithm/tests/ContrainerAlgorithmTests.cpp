#include "gtest/gtest.h"
#include "RemoveDupsTests.hpp"
#include "UniqueImplTests.hpp"

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
