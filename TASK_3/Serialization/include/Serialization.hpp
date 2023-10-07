/// @file Serializaion.hpp
///
/// @brief Заголовочный файл содержащий реализацию сериализации и десериализации основных типов языка
#ifndef SERIALIZATION_LIB_SERIALIZATION_HPP_
#define SERIALIZATION_LIB_SERIALIZATION_HPP_

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <system_error>
#include <type_traits>
#include <vector>
#include <cstdint>
#include <fstream>

#include "BinaryStorage.hpp"

namespace serialization
{

/// @brief Имлементация сериализации целочисленных значений в хранилищe
/// @param[in] value Целочисленное значение
/// @return Результат выполнения операции, размер сериализованных данных в байтах и код ошибки
template<typename StorageImpl,
         typename T, std::enable_if_t<std::is_integral_v<T>,bool> = true >
Result Serialize( const T& value, Storage<StorageImpl>& storage )
{
  return storage->Write( reinterpret_cast<const uint8_t*>( &value ), sizeof( value ) );  
}

/// @brief Имлементация десереализации целочисленных значений из данных хранилища
/// @param[in] storage Хранилище сериализованных данных
/// @param[out] value Целочисленное значение
/// @return Результат выполнения операции, размер десериализованных данных в байтах и код ошибки
template<typename StorageImpl,
         typename T, std::enable_if_t<std::is_integral_v<T>,bool> = true >
Result Deserialize( Storage<StorageImpl>& storage, T& value )
{
  T tmpValue;

  Result result = storage->Read( reinterpret_cast<uint8_t*>( &tmpValue ), sizeof( value ) );
  if( result )
  {
    value = tmpValue;
  }
  
  return result;
}

/// @brief Имлементация сериализации строковых значений в хранилищe
/// @param[in] value Строка 
/// @param[out] storage Хранилище сериализованных данных
/// @return Результат выполнения операции, размер сериализованных данных в байтах и код ошибки
template<typename StorageImpl>
Result Serialize( const std::string& value, Storage<StorageImpl>& storage )
{
  size_t stringSize = value.size();

  Result result = Serialize( stringSize, storage );
  if( !result )
  {
    return result;
  }

  result += storage->Write( reinterpret_cast<const uint8_t*>( value.data() ), stringSize );
  return result;
}

/// @brief Имлементация десереализации строковых значений из хранилища
/// @param[out] value Строка 
/// @param[in] storage Хранилище сериализованных данных
/// @return Результат выполнения операции, размер десериализованных данных в байтах и код ошибки
template<typename StorageImpl>
Result Deserialize( Storage<StorageImpl>& storage, std::string& value )
{
  std::string tmpValue;
  size_t stringSize;

  Result result = Deserialize( storage, stringSize );
  if ( !result )
  {
    return result;
  }

  tmpValue.resize( stringSize );

  result += storage->Read( reinterpret_cast<uint8_t*>( tmpValue.data() ), stringSize );
  if ( result )
  {
    value = std::move( tmpValue );
  }

  return result;
}

} // namespace Serializaion

#endif // SERIALIZATION_LIB_SERIALIZATION_HPP_

