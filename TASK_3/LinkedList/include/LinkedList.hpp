#ifndef LINKED_LIST_HPP_
#define LINKED_LIST_HPP_

#include <cstddef>
#include <cwchar>
#include <exception>
#include <iterator>
#include <limits>
#include <new>
#include <stdexcept>
#include <string>
#include <map>

#include <iostream>
#include <string_view>



/// @brief 
class RandomLinkedList
{
public:
  /// @brief Элемент двусвязного списка
  struct Node
  {
    /// @brief Указатель предыдущую ноду списка
    Node* prev = nullptr;
    /// @brief Указатель на следующую ноду списка
    Node* next = nullptr;
    /// @brief Указатель на произвольную ноду списка
    Node* rand = nullptr;
    /// @brief Данные 
    std::string data;
  };
public:

  RandomLinkedList()
  {

  }

  ~RandomLinkedList()
  {
  }

  RandomLinkedList( const size_t size )
  {

  }

  Node* First() const
  {
    return head;
  }

  Node* Last() const
  {
    return head;
  }

  size_t Size() const
  {
    return size_;
  }

  Node* Insert( Node* position, std::string_view data )
  {


  }
  

  Node* AddNode( const std::string& str )
  {

  }

  ///void Serialize(FILE* file)
  //{
  //}
  //void Deserialize(FILE* file)
  //{
  //}
private:
  Node* head;
  Node* last;
  size_t size_;
};

#endif // LINKED_LIST_HPP_

