/// @file CommonBinaryUtils.hpp
/// @brief Заголовочный файл содержащий набор общих функций 
///        для работы с побитывыми операциям 
#ifndef BINARY_UTILS_COMMON_BINARY_UTILS_HPP_
#define BINARY_UTILS_COMMON_BINARY_UTILS_HPP_

#include <cstdint>
#include <type_traits>

namespace binary_tool
{

/// @brief Проверка значения бита в целочисленном значении
/// @param[in] value Целочисленное значение
/// @param[in] bitNum Номер проверяемого бита
/// @return true в случае, если бит установлен в 1,
///         false если установлен в 0 
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
constexpr bool IsBitSet( const T value, const size_t bitNum )
{
  return ( value >> bitNum ) & 1;
}

} // namespace binary_tool

#endif // !BINARY_UTILS_COMMON_BINARY_UTILS_HPP_
