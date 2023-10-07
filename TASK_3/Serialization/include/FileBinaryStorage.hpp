/// @file FileStorage.hpp
///
/// @brief Заголовочный файл содержит реализацию файлового хранилища данных
#ifndef SERIALIZATION_LIB_FILE_STORAGE_HPP_
#define SERIALIZATION_LIB_FILE_STORAGE_HPP_

#include "BinaryStorage.hpp"
#include <cstdint>
#include <stdio.h>
#include <system_error>

namespace serialization
{

/// @brief Реализация файлового хранилища сериализованных данных
class FileStorage : public Storage<FileStorage>
{
public:
  /// @brief Инициализация файловго хранилища сериализованных данных
  /// @param[in] Указатель на открытый файл
  /// @throw std::system_error в случае, если был передан невалидный указатель на файл
  FileStorage( FILE* filePtr ) : filePtr_( filePtr )
  {
    if( filePtr == nullptr )
    {
      throw std::system_error( SerializationErr::StorageCorrupted );
    }
  }

  /// @brief Запись данных в хранилище
  /// @param[in] Указатель на начало данных которуе необходимо записать в хранилище
  /// @param[in] Размер данных записываемых в хранилище в байтах
  /// @return Результат выполнения операции, размер записанных данных в байтах и код ошибки
  Result WriteImpl( const uint8_t* data, const size_t size )
  {
    Result result; 

    result.size = fwrite( data, sizeof( uint8_t ), size, filePtr_ );

    if( result.size == size )
    {
      result.error = SerializationErr::Success;
    }
    else if( ferror( filePtr_ ) != 0 )
    {
      result.error = SerializationErr::SerializationFailed;
    }
    else
    {
      result.error = SerializationErr::UnknownError;
    }

    return result;
  }

  /// @brief Запись данных в хранилище
  /// @param[in] Указатель на начало данных которуе необходимо записать в хранилище
  /// @param[in] Размер данных записываемых в хранилище в байтах
  /// @return Результат выполнения операции, размер считанных данных в байтах и код ошибки
  Result ReadImpl( uint8_t* data, const size_t size )
  {
    Result result; 

    result.size = fread( data, sizeof( uint8_t ), size, filePtr_ );

    if( result.size == size )
    {
      result.error = SerializationErr::Success;
    }
    else if( feof( filePtr_ ) != 0 )
    {
      result.error = SerializationErr::EndOfStorage;
    }
    else if( ferror( filePtr_ ) != 0 )
    {
      result.error = SerializationErr::DeserializationFailed;
    }
    else
    {
      result.error = SerializationErr::UnknownError;
    }

    return result;
  }
private:
  /// @brief Указатель на открытый файл
  FILE* filePtr_;
};

} // namespace serialization

#endif // SERIALIZATION_LIB_FILE_STORAGE_HPP_

