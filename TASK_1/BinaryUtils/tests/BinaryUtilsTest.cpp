#include "gtest/gtest.h"

#include <vector>
#include <bitset>
#include <cstdint>
#include <climits>

#include "include/IntegralToBinaryString.hpp"

namespace integral_to_bitstring_tests
{

template <typename T>
using ParamPack = std::vector<T>;

/// @brief Набор тестовых данных разных типов
static std::tuple<ParamPack<int>, ParamPack<long long>, ParamPack<size_t>, ParamPack<uint8_t>> testData
{
  { -112231,INT_MIN, 91123, INT_MAX},                 // int
  { -11223, LONG_LONG_MIN, 9123123, LONG_LONG_MAX },  // long long
  { 1412, 522, SIZE_MAX, 1233333 },                   // size_t
  { 31,53, 23, UINT8_MAX },                           // uint8_t
};

template <typename T>
struct IntegralToBitStringParameterizedTestFixture : public testing::Test 
{
  IntegralToBitStringParameterizedTestFixture() 
  : params( std::get<ParamPack<T>>( testData ) )
  {
  }

  std::string GetExpectedString( const T value )
  {
    controlBitset = value;
    return controlBitset.to_string();
  }

  ParamPack<T> params;
  std::bitset<sizeof( T ) * CHAR_BIT> controlBitset;
};

TYPED_TEST_SUITE_P( IntegralToBitStringParameterizedTestFixture );

/// @brief Проверка преобразования целочисленного значения в битовую строку
///        для значений различных типов данных
TYPED_TEST_P( IntegralToBitStringParameterizedTestFixture, IntegralToBitStringTest )
{
  for( auto const& value : this->params )
  {
    std::string expectBitString = this->GetExpectedString( value );

    std::string resultBitString = binary_tool::IntegralToBitString( value );

    ASSERT_EQ( resultBitString, expectBitString )
               << resultBitString << " != " << expectBitString;
  }
}

REGISTER_TYPED_TEST_SUITE_P( IntegralToBitStringParameterizedTestFixture, IntegralToBitStringTest );

using Types = testing::Types<int, long long, size_t, uint8_t>;
INSTANTIATE_TYPED_TEST_SUITE_P( Typed, IntegralToBitStringParameterizedTestFixture, Types );

} // namespace integral_to_bitstring_tests

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  
  return RUN_ALL_TESTS();
}
