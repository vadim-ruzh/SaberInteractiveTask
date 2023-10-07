#pragma once
#include "gtest/gtest.h"

#include <cstdint>
#include <climits>
#include <bitset>
#include <vector>
#include <string>
#include <algorithm>

#include "include/Unique.hpp"

namespace remove_dups_tests
{

namespace input_params_tests
{

TEST( RemoveDupsInputParamsTests, InvalidPtrTest )
{
  char* stringPtr = nullptr;

  size_t newSize = container_algorithm::RemoveDups( stringPtr );

  ASSERT_EQ( newSize, 0 );
}

} // namespace input_params_tests


namespace remove_dups_in_string_tests
{

/// @brief Набор тестовых данных
static std::vector<std::string> TestData
{
  "aaaAAASDdddddddASXCCBBBA)S(D<F20>A)ASSdcz",
  "ASD=_09788967777790090-00---099-90-292292",
  "_)_()(&*^%%%***)...///asSSss!!!3##4$$$!12",
  "AWEOP{J}$$\%\%ASDqweASD    asdDDDaAAaaaaE",
  "~!@!@!1133331axcvccccasDAwSXCAWEQWEASSSSX",
  "as||\n\n \r\n a   AA     mQqesassssASAA  "
};

struct RemoveDupsParameterizedTestFixture : public testing::TestWithParam<std::string>
{
  std::string GetExpectedString()
  {
    std::string controlString = GetParam();

    auto last = std::unique( controlString.begin(), controlString.end() );
    controlString.erase( last, controlString.end() );

    return controlString;
  }
};


/// @brief Проверка преобразования целочисленного значения в битовую строку
///        для различных типов данных
TEST_P( RemoveDupsParameterizedTestFixture, RemoveDuplicateCharsTest )
{
  std::string string = GetParam();

  size_t newSize = container_algorithm::RemoveDups( string.data() );
  string.resize( newSize );
  
  ASSERT_EQ( string, this->GetExpectedString() );
}

INSTANTIATE_TEST_CASE_P( RemoveDupsTests,
                         RemoveDupsParameterizedTestFixture,
                         testing::ValuesIn( TestData ) );


} // namespace remove_dups_in_string_tests

} // namespace remove_dups_tests



