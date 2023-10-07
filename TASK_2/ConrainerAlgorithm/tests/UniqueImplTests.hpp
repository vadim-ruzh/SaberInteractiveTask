#pragma once
#include "gtest/gtest.h"

#include <cstdint>
#include <climits>
#include <vector>
#include <bitset>
#include <string>
#include <algorithm>

#include "RemoveDupsTests.hpp"
#include "include/Unique.hpp"

namespace unique_impl_tests
{

namespace input_params_tests
{

TEST( UniqueImplInputParamsTests, InvalidPtr )
{
  uint8_t* sequencePtr = nullptr;
  size_t sequenceSize = 12;

  size_t newSize = container_algorithm::UniqueImpl( sequencePtr, sequenceSize );

  ASSERT_EQ( newSize, 0 );
}

} // namespace input_params_tests

namespace remove_dups_in_sequence_tests
{

template <typename T>
using Sequence = std::vector<T>;

/// @brief Набор тестовых данных
static std::tuple<Sequence<uint8_t>, Sequence<int>, Sequence<std::string>> TestData
{
  { 31, 53, 53, 23, 23, 55, 0, 0, 0, 1, 1 },    // uint8_t
  { INT_MIN, INT_MIN, 0, INT_MAX, INT_MAX },    // int
  { "aa", "a", "aa", "bb", "bb", "a", "a" },    // std::string 
};

template <typename T>
struct UniqueImplParameterizedTestFixture : public testing::Test 
{
  UniqueImplParameterizedTestFixture() 
  : sequence( std::get<Sequence<T>>( TestData ) )
  {
  }
  
  Sequence<T> GetExpectedSequence()
  {
    Sequence<T> controlSequence = sequence;

    auto last = std::unique( controlSequence.begin(), controlSequence.end() );
    controlSequence.erase( last, controlSequence.end() );

    return controlSequence;
  }

  Sequence<T> sequence;
};

TYPED_TEST_SUITE_P( UniqueImplParameterizedTestFixture );

/// @brief Проверка преобразования целочисленного значения в битовую строку
///        для различных типов данных
TYPED_TEST_P( UniqueImplParameterizedTestFixture, RemoveDuplicateTest )
{
  auto sequence = this->sequence;
  
  size_t newSize = container_algorithm::UniqueImpl( sequence.data(), sequence.size() );

  sequence.resize( newSize );
  
  ASSERT_EQ( sequence, this->GetExpectedSequence() );
}

REGISTER_TYPED_TEST_SUITE_P( UniqueImplParameterizedTestFixture, RemoveDuplicateTest );

using Types = testing::Types<uint8_t, int, std::string>;
INSTANTIATE_TYPED_TEST_SUITE_P( Typed, UniqueImplParameterizedTestFixture, Types);

} // namespace remove_dups_in_sequence_tests

} // namespace unique_impl_tests
