#ifndef FHhashQPwFind_h
#define FHhashQPwFind_h

#include <iostream>
#include "FHhashQP.h"
using namespace std;

//------------------FHhashQPwFind prototpe------------------------
template <class Object, typename KeyType>
class FHhashQPwFind : public FHhashQP<Object>
{
public:
   const Object find(const KeyType & key);
   class NotFoundException {};

protected:
   int myHashKey(const KeyType & key) const;
   int findPosKey(const KeyType & key) const;
};

//----------------FHhashQPwFind definition------------------------
//Check if the hash table have certain key
template <class Object, typename KeyType>
const Object FHhashQPwFind<Object, KeyType>::find(const KeyType & key) {
   typename FHhashQP<Object>::HashEntry result;

   result = this->mArray[findPosKey(key)];

   //If found, return the data. If not found, throw exception
   if (result.state == FHhashQP<Object>::ACTIVE)
      return result.data;
   else
      throw NotFoundException();;
}

//modulus the hash number to get the position
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::myHashKey(const KeyType & key) const {
   int hashVal;

   hashVal = Hash(key) % this->mTableSize;
   if (hashVal < 0)
      hashVal += this->mTableSize;

   return hashVal;
}

//Find the position for the key
template <class Object, typename KeyType>
int FHhashQPwFind<Object, KeyType>::findPosKey(const KeyType & key) const {

   int oddNum = 1;
   int index = myHashKey(key);

   //When the space is not empty and the position value not equal to key
   //keep traveling
   while (this->mArray[index].state != FHhashQP<Object>::EMPTY &&
      getKey(this->mArray[index].data) != key) {

      //update the index. index = hashindex + k*k or index += oddNum
      index += oddNum;

      //If the index go out of size, move back to beginning
      if (index >= this->mTableSize) {
         index -= this->mTableSize;
      }

      //Update the odd number to next odd number
      oddNum += 2;
   }

   return index;
}
#endif // !FHhashQPwFind