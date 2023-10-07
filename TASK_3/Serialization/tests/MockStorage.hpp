#pragma once

#include "../include/BinaryStorage.hpp"

namespace serialization
{

namespace test
{

/// @remark По сути из этого можно сделать полноценную реализацию хранилища
struct MockStorage : Storage<MockStorage>
{
  MockStorage( std::vector<uint8_t>& serializedData )
  : serializedData_( serializedData ), currentPosition_( serializedData_.begin() )
  {
  }

  Result WriteImpl( const uint8_t* data, const size_t size )
  {
    serializedData_.resize( serializedData_.size() + size );

    std::copy_n( data, size, currentPosition_ );

    std::advance( currentPosition_, size );

    return { size ,SerializationErr::Success };
  }

  Result ReadImpl( uint8_t* data, const size_t size )
  {
    if( std::distance( currentPosition_, serializedData_.end() ) < size )
    {
      return { 0 , SerializationErr::EndOfStorage };
    }

    std::copy_n( currentPosition_, size, data );

    std::advance( currentPosition_, size );

    return { size ,SerializationErr::Success };
  }

  std::vector<uint8_t>& serializedData_;
  std::vector<uint8_t>::iterator currentPosition_;
};

} // namespace test

} // namespace serialization
