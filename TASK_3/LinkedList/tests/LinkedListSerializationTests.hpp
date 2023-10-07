



















TEST( LinkedListSerializationTest, ... )
{
  LinkedList controlLinkedList = GetControlLinkedList();
  LinkedList linkedListFromFile;

  linkedList.Serialize( this->filePtr );
  this->ResetFilePosition();
  linkedListFromStorage.Deserialise( this->filePtr );

  ASSERT_TRUE( LinkedListFullCompare( controlLinkedList, linkedListFromFile ) );
}

















