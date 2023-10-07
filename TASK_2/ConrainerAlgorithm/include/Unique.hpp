/// @file Unique.hpp
/// @brief Заголовочный файл содержит реализацию алгоритма 
///        удаления подряд идущих повторяющихся элементов
#ifndef CONTAINER_ALGORITHM_UNIQUE_HPP_
#define CONTAINER_ALGORITHM_UNIQUE_HPP_

#include <stdio.h>
#include <string.h>
#include <array>
#include <string>
#include <algorithm>
#include <iostream>
#include <type_traits>
#include <utility>

namespace container_algorithm
{

namespace detail
{

template<class T, class EqualTo>
struct has_operator_equal_impl
{
  template<class U, class V>
    static auto test(U*) -> decltype(std::declval<U>() == std::declval<V>());
  template<typename, typename>
    static auto test(...) -> std::false_type;

  using type = typename std::is_same<bool, decltype(test<T, EqualTo>(0))>::type;
};

template<class T, class EqualTo = T>
struct has_operator_equal : has_operator_equal_impl<T, EqualTo>::type {};

} // namespace detail


/// @brief Удаление эквивалентных подряд идущих объектов в последовательности 
/// @param[in|out] data - Указатель на начало последовательности
/// @param[in] size - Исходный размер последовательности
/// @return Размер последовательности после преобразования
/// @return 0 - В случае, если был передан nullptr или последовательность пуста
/// @remark Использование значений выходящие за пределы размера последовательности,
///         после преобразования не рекомендуется, поведение не определено.
/// @remark В случае передачи размера, большего, чем реальный размер выделенной области памяти, поведение не определено
template<typename T, std::enable_if_t<detail::has_operator_equal<T>::value,bool> = true>
[[nodiscard]] size_t UniqueImpl( T* data, const size_t size )
{
  if( data == nullptr ) 
  {
    return 0;
  }

  if( size <= 1 )
  {
    return size;
  }

  size_t lastUniqueIndex = 0;

  for( size_t index = 1; index < size; ++index )
  {
    if( data[lastUniqueIndex] == data[index] )
    {
      continue;
    }

    if( ++lastUniqueIndex != index )
    {
      data[lastUniqueIndex] = std::move( data[index] );
    }
  }

  return lastUniqueIndex + 1;
}

/// @brief Удаление эквивалентных подряд идущих символов из строки
/// @param[in|out] str - Указатель на начало строки
/// @return Длина строки после преобразования
/// @return 0 - В случае, если был передан nullptr или строка пуста
inline size_t RemoveDups( char* str )
{
  if( str == nullptr )
  {
    return 0;
  }

  const size_t strLen = strlen( str );
  if( strLen <= 1 )
  {
    return strLen;
  }

  const size_t newStrLen = UniqueImpl( str, strLen );
  if( newStrLen < strLen )
  {
    str[newStrLen] = '\0';        
  }

  return newStrLen;
}

} // namespace container_algorithm

#endif // !CONTAINER_ALGORITHM_UNIQUE_HPP_
