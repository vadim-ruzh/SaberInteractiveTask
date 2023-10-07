/// @file LinkedListSerialization.hpp
///
/// @brief Заголовочный файл содержащий реализацию сериализации и десериализации двусвяного списка 
#ifndef LINKED_LIST_SERIALIZATION_HPP_
#define LINKED_LIST_SERIALIZATION_HPP_

#include <cstdlib>
#include <exception>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include "../../../Serialization/include/Serialization.hpp"
#include "../../../Serialization/include/SerializationError.hpp"
#include <map>
#include <system_error>
#include <unordered_map>

#include "../LinkedList.hpp"

namespace
{

/// @brief Индекс отсутсвующей рандомной ноды
inline const size_t RAND_NODE_MISSING_MARKER = std::numeric_limits<size_t>::max();

/// @brief Вспомогательная структура, содержащая указатель на ноду списка
/// и индекс рандомной ноды на которую указывает данная нода
struct ListNodePair
{
  ListNode* nodePtr = nullptr;
  size_t randomNodeIndex = RAND_NODE_MISSING_MARKER;
};

/// @brief Получение хэш таблицы ключем которой является указатель на ноду списка,
///        а значением индекс ноды в списке
inline std::unordered_map<const ListNode*,size_t> GetNodeHashMap(const LinkedList& value )
{
  std::unordered_map<const ListNode*,size_t> randomNodeMap; 
  
  const ListNode* currentNode = value.First();
  for( size_t i = 0; i < value.Size(); ++i )
  {
    randomNodeMap.insert( std::make_pair( currentNode, i ) );
    currentNode = currentNode->next; 
  }

  return randomNodeMap;
}

/// @brief Получение индекса рандомно ноды
/// @param[in] Хэш таблица содержащая указатели и индексы нод списка
/// @param[in] Указатель на рандомную ноду списка 
/// @return Индекс ноды случае если данная нода присутсвует в хэш таблице 
/// @return RAND_NODE_MISSING в случае отсутсвия ноды в хэш таблице
inline size_t GetRandNodeIndex( const std::unordered_map<const ListNode*,size_t>& nodeMap, const ListNode* randNodePtr )
{
  if( randNodePtr != nullptr )
  {
    auto randNodeIter = nodeMap.find( randNodePtr );
    if( randNodeIter != nodeMap.end() )
    {
      return randNodeIter->second;
    }
  }

  return RAND_NODE_MISSING_MARKER;
}

/// @brief Нормализация ссылок на рандомные ноды списка
/// @param[in] nodeMap Вектор содержащий указатель на ноду и индекс рандомной ноды на которую он указывает
///                    иднекс элемента вектора является индексом ноды
/// @return SerializationErr::DataCorrupted в случае, если индекс рандомной ноды невалиден
inline std::error_code NormalizeRandomNodesLinks( std::vector<ListNodePair>& nodeMap )
{
  for ( auto elem : nodeMap )
  {
    if ( elem.randomNodeIndex > nodeMap.size() - 1 )
    {
      return serialization::SerializationErr::DataCorrupted;
    }

    if ( elem.randomNodeIndex != RAND_NODE_MISSING_MARKER )
    {
      elem.nodePtr->rand = nodeMap.at( elem.randomNodeIndex ).nodePtr;
    }
  }

  return serialization::SerializationErr::Success;
}

} // anonymous namespace 


namespace serialization
{

/// @brief Сериализация двусвязного списка в хранилище
/// @param[in] value Двусвязный список
/// @param[out] storage Хранилище сериализованных данных
/// @return Результат выполнения операции, размер сериализованных данных в байтах и код ошибки
template<typename StorageImpl>
Result Serialize( const LinkedList& value, Storage<StorageImpl>& storage )
{
  Result result = Serialize( value.Size(), storage );
  if ( !result )
  {
    return result;
  }

  auto nodeMap = GetNodeHashMap( value );

  const ListNode* currentNode = value.First();
  while ( currentNode != nullptr )
  {
    result = Serialize( currentNode->data, storage );
    if ( !result )
    {
      return result;
    }

    result = Serialize( GetRandNodeIndex( nodeMap, currentNode->rand ), storage );
    if ( !result )
    {
      return result;
    }

    currentNode = currentNode->next;
  }
  
  return result;
}

/// @brief Десериализация двусвяного списка с восстановлением ссылок на случайные элементы
/// @param[in] storage Хранилище сериализованных данных
/// @param[out] value Двусвязный список
/// @return Результат выполнения операции, размер десериализованных данных в байтах и код ошибки
template<typename StorageImpl>
Result Deserialize( Storage<StorageImpl>& storage, LinkedList& value )
{
  LinkedList tmpValue;
  size_t listSize;

  Result result = Deserialize( storage, listSize );
  if ( !result || listSize == 0 )
  {
    return result;
  }

  std::vector<ListNodePair> nodeMap( listSize );
  for ( auto elem : nodeMap )
  {
    elem.nodePtr = tmpValue.AddNode("");

    result += Deserialize( storage, elem.nodePtr->data );
    if ( !result )
    {
      return result;
    }

    result = Deserialize( storage, elem.randomNodeIndex );
    if ( !result )
    {
      return result;
    }
  }

  result.error = NormalizeRandomNodesLinks( nodeMap );
  if ( result )
  {
    value = std::move( tmpValue );
  }
  
  return result;
}

} // namespace Serialization

#endif // LINKED_LIST_SERIALIZATION_HPP_


