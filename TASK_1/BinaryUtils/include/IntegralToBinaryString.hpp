/// @file IntegralToBinaryString.hpp
/// @brief Заголовочный файл содержащий набор функций для преобразования
///        Целочисленных значений в строку, в бинарном виде 
#ifndef BINARY_UTILS_INTEGRAL_TO_BINARY_STRING_HPP_
#define BINARY_UTILS_INTEGRAL_TO_BINARY_STRING_HPP_

#include <cstdint>
#include <string>
#include <limits.h>
#include <iostream>
#include <type_traits>

#include "CommonBinaryUtils.hpp"

namespace binary_tool
{

/// @brief Конвертация целочесленного значения в строку, в бинарном виде
/// @param[in] value Интегральное значене
/// @return Строка содержащая целочисленное значение в бинарном виде
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
std::string IntegralToBitString( const T value )
{
  constexpr size_t bitsCount = sizeof(T) * CHAR_BIT;

  std::string bitString;
  bitString.reserve( bitsCount );

  for( size_t i = bitsCount; i > 0; --i )
  {
    if( IsBitSet( value, i - 1 ) )
    {
      bitString += "1";
    }
    else
    {
      bitString += "0";
    }
  }

  return bitString;
}

/// @brief Печать целочисленного значения в стандартный поток вывода, в бинарном виде
/// @param[in] value целочисленноe значене
template<typename T, std::enable_if_t<std::is_integral_v<T>, bool> = true>
void PrintBits( const T value )
{
  std::cout << IntegralToBitString( value ) << std::endl;
}

} // namespace binary_tool


#endif // !BINARY_UTILS_INTEGRAL_TO_BINARY_STRING_HPP_
