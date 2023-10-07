/// @file SerializationError.hpp
///
/// @brief Файл содержащий коды ошибок библиотеки сериализации 
#ifndef SERIALIZATION_LIB_ERROR_HPP_
#define SERIALIZATION_LIB_ERROR_HPP_

#include <system_error>
#include <type_traits>

namespace serialization
{

/// @brief Перечесление кодов ошибок библиотеки сериализации
enum class SerializationErr : int
{
  Success = 0,              ///< Успех
  DataCorrupted,            ///< Данные повреждены 
  StorageCorrupted,         ///< Хранилище невалидно
  SerializationFailed,      ///< Ошибка сериализации
  DeserializationFailed,    ///< Ошибка десериализации 
  EndOfStorage,             ///< Достигнут конец хранилища
  InvalidArguments,         ///< Аргументы невалидны
  UnknownError,             ///< Неизвестная ошибка 
};

/// @brief Категория ошибок сериализации
struct SerializationErrCategoryImpl : std::error_category
{
  /// @brief Получение имени категории ошибок
  const char* name() const noexcept override
  {
    return "Serialization";
  }

  /// @brief Получение сообщения об ошибке
  std::string message( int errc ) const override
  {
    switch ( static_cast<SerializationErr>( errc ) )
    {
    case SerializationErr::Success:
      return "Success";
    case SerializationErr::DataCorrupted:
      return "Data corrupted";
    case SerializationErr::StorageCorrupted:
      return "Data storage corrupted";
    case SerializationErr::SerializationFailed:
      return "Serialization to storage failed";
    case SerializationErr::DeserializationFailed:
      return "Deserialization to storage failed";
    case SerializationErr::EndOfStorage:
      return "End of storage reached";
    case SerializationErr::InvalidArguments:
      return "Invalid arguments";
    case SerializationErr::UnknownError:
      return "Unknown error";
    default:
      return "Unrecognized error";
    }
  }
};

/// @brief Получение ссылки на категорию ошибок сериализации
inline const std::error_category& SerializationErrCategory()
{
  static SerializationErrCategoryImpl instance;
  return instance;
}

/// @brief Создание объекта std::error_code из элемента перечесления кодов ошибок сериализации
inline std::error_code make_error_code( SerializationErr errc )
{
  return std::error_code( static_cast<int>( errc ),
                          SerializationErrCategory() );  
}

} // namespace serialization

namespace std
{

  /// @brief 
  template<>
  struct is_error_code_enum<serialization::SerializationErr> : true_type{};

} // namespace std

#endif // SERIALIZATION_LIB_ERROR_HPP_
