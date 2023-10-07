#pragma once

#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdint>
#include <string>

#include "../include/Serialization.hpp"
#include "MockStorage.hpp"

using namespace serialization;

/// @brief Набор тестовых данных разных типов
static std::tuple<int, long long, size_t, std::string> testData
{
  { -1123 },                 // int
  { -13123233 },             // long long
  { 12323333123 },           // size_t
  { "asdASDASDdddd" },       // std::string 
};

template <typename T>
struct SerializationAndDeserializationTestFixture : public testing::Test 
{
  using value_type = T;

  T GetControlValue() const
  {
    return std::get<T>( testData );
  }


  std::vector<uint8_t> byteVector;
};
TYPED_TEST_SUITE_P( SerializationAndDeserializationTestFixture );


TYPED_TEST_P( SerializationAndDeserializationTestFixture, ReliabilityOfDataTest )
{
  value_type valueFromStorage;

  {
    Storage<MockStorage> mockStorage( this->byteVector );

    Result result = Serialize( this->GetControlValue(), mockStorage );  

    ASSERT_EQ( result.error, SerializationErr::Success )
               <<"Error: "<< result.error.message() << ", Bytes serialized: " << result.size;
  }

  {
    Storage<MockStorage> mockStorage( this->byteVector );

    Result result = Deserialize( mockStorage, value );

    ASSERT_EQ( result.error, SerializationErr::Success );
              <<"Error: "<< result.error.message() << ", Bytes deserialized: " << result.size;
  }

  ASSERT_EQ( valueFromStorage, this->GetControlValue() );
}
REGISTER_TYPED_TEST_SUITE_P( SerializationAndDeserializationTestFixture, ReliabilityOfDataTest );

using Types = testing::Types<int, long long, size_t, std::string>;
INSTANTIATE_TYPED_TEST_SUITE_P( Typed, SerializationAndDeserializationTestFixture, Types );

