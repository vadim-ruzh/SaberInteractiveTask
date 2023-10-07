#pragma once

#include "gtest/gtest.h"

#include <algorithm>
#include <iterator>
#include <vector>
#include <cstdint>
#include <string>

#include "../include/FileBinaryStorage.hpp"

using namespace serialization;

static const std::vector<uint8_t> testData 
{
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
  0xFF, 0x10, 0x14, 0xBA, 0xCA, 0x12,
};

template <typename T>
struct FileSerializationTestFixture : public testing::Test 
{
  using value_type = T;

  T GetControlValue() const
  {
    return std::get<T>( testData );
  }
};

TEST( FileStorageInputParamsTests, InvalidFilePtr )
{

}

TEST( FileStorageInputParamsTests, InvalidDataPtrOnWrite )
{

}

TEST( FileStorageInputParamsTests, InvalidDataPtrOnRead )
{

}

TEST( WriteToFileStorageTests, FileWasRemoved )
{

}

TEST( WriteToFileStorageTests, FileWasRemoved )
{

}

TEST( WriteToFileStorageTests, CorrectReturnedSize )
{

}

TEST( WriteToFileStorageTests, PermissionDenied )
{

}

TEST( ReadFromFileStorageTests, FileWasRemoved )
{

}

TEST( ReadFromFileStorageTests, FileWasEmpty )
{

}

TEST( ReadFromFileStorageTests, CorrectReturnedSize )
{

}

TEST( ReadFromFileStorageTests, PermissionDenied )
{

}

TEST( SerializationAndDeserializationTestFixture, ReliabilityOfDataTest )
{
  std::vector<uint8_t> valueFromStorage( testData.size() );

  {
    Storage<FileBinaryStorage> storage( this->OpenFilePtr );

    Result result = storage.Write( testData.data(), testData.size() );  

    ASSERT_EQ( result.error, SerializationErr::Success )
               << "Error: " << result.error.message() << ", Bytes serialized: " << result.size;
  }

  {
    Storage<FileBinaryStorage> storage( this->OpenFilePtr );

    Result result = storage.Read( valueFromStorage.data(), valueFromStorage.size() );  

    ASSERT_EQ( result.error, SerializationErr::Success );
              << "Error: " << result.error.message() << ", Bytes deserialized: " << result.size;
  }

  ASSERT_EQ( valueFromStorage, testData );
}

