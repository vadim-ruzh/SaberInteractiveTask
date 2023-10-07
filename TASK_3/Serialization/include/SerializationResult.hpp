/// @file SerializationError.hpp
/// @brief Заголовочный файл содержащий реализацию структура - результат операций сериализаци/десериализации 
#ifndef SERIALIZATION_LIB_RESULT_HPP_
#define SERIALIZATION_LIB_RESULT_HPP_

#include "SerializationError.hpp"

namespace serialization
{

/// @brief Структура содержащая результат выполнения операций сериализации/десериализации 
struct Result 
{
  /// @brief Оператор приведения типа к std::error_code
  operator bool() const
  {
    return error == SerializationErr::Success;
  }

  /// @brief 
  Result& operator+=( const Result& other )
  {
    size += other.size;
    error = other.error;

    return *this;
  }

  /// @brief Размер в байтах
  size_t size = 0;
  /// @brief Код ошибки 
  std::error_code error = SerializationErr::Success;
};

} //namespace serialization

#endif // SERIALIZATION_LIB_RESULT_HPP_
