/// @file Storage.hpp
///
/// @brief Заголовочный файл содержит интерфейс хранилища данных
#ifndef SERIALIZATION_LIB_STORAGE_HPP_
#define SERIALIZATION_LIB_STORAGE_HPP_

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <vector>
#include <cstdint>
#include <fstream>
#include <memory>

#include "SerializationResult.hpp"

namespace serialization
{

/// @brief Интерфейс хранилища сериализованных данных
template<typename Implementation>
class Storage
{
public:
  /// @brief Запись данных в хранилище
  /// @param[in] Указатель на начало данных которуе необходимо записать в хранилище
  /// @param[in] Размер данных записываемых в хранилище в байтах
  /// @return Результат выполнения операции, размер записанных данных в байтах и код ошибки
  Result Write( const uint8_t* data, const size_t size )
  {
    Result result;

    if( data != nullptr )
    {
      result = Impl()->WriteImpl( data, size );
    }
    else
    {
      result.error = SerializationErr::DataCorrupted;
    }

    return result;
  }

  /// @brief Чтение данных из хранилища 
  /// @param[out] Указатель на начало области памяти, в которую будут записаны данные из хранилища 
  /// @param[in] Размер считываемых из хранилища данных в байтах 
  /// @return Результат выполнения операции, размер записанных данных в байтах и код ошибки
  Result Read( uint8_t* data, const size_t size )
  {
    Result result;

    if( data != nullptr )
    {
      result = Impl()->ReadImpl( data, size );
    }
    else
    {
      result.error = SerializationErr::DataCorrupted;
    }

    return result;
  }
private:
  /// @brief Получение указателя на реализацию хранилища
  /// @return Указатель на реализацию хранилища
  Implementation* Impl()
  {
    return static_cast<Implementation*>( this );
  }
};

template <typename StorageImpl>
using StoragePtr = std::shared_ptr<Storage<StorageImpl>>;

} // namespace Serializaion

#endif // SERIALIZATION_LIB_STORAGE_HPP_
