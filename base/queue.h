#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "string"
#include <algorithm>
using namespace std;

const int MaxQueueSize = 100;



template <class T>
class TQueue
{
  private:
    T* pMem;
    int size;
    int first;
    int last;
    int count;
  public:
    TQueue(int _size)
    {
      if((_size < 0) ||(_size > MaxQueueSize))
        throw(string("Incorrect size of queue"));
      size = _size;
      first = -1;
      last = 0;
      count = 0;
      pMem = new T[size];
    }
    TQueue(const TQueue& other)
    {
      pMem = new T[other.size];
      size = other.size;
      first = other.first;
      last = other.last;
      count = other.count;
      copy(other.pMem, other.pMem + other.size, pMem);
    }
    TQueue& operator=(const TQueue& other)
    {
      if(this == &other)
        return *this;
      
      if(size != other.size) {
        T* tmp_mem = new T[other.size];
        delete [] pMem;
        pMem = tmp_mem;
        copy(other.pMem, other.pMem + other.size, pMem);
        size = other.size;
        first = other.count;
        count = other.count;
        last = other.last;
      }
      else {
        copy(other.pMem, other.pMem + other.size, pMem);
        size = other.size;
        first = other.count;
        count = other.count;
        last = other.last;
      }
      return *this;
    }
    bool operator==(const TQueue& v) const
	  {
	  	if (this->size != v.size)
	  		return false;
			for (int i = 0; i < size; i++)
			{
				if (this->pMem[i] != v.pMem[i])
					return false;
			}
			return true;
		}
	  bool operator!=(const TQueue& v) const
    { 
      return!(*this == v); 
    }



    int GetSize() const
    {
      return size;
    }
    bool IsFull() const
    {
      return count == size;
    }

    bool IsEmpty() const
    {
      return !count;
    }

    T GetFirst() const
    {
      return pMem[(first + 1) % size];
    }

    T GetLast() const
    {
      return pMem[last];
    }

    



    T Pop()
    {
      if(IsEmpty())
        throw(string("Queue is empty"));
      count--;
      first = (first + 1) % size;
      return pMem[first];
    }

    void Push(T item)
    {
      if(IsFull())
        throw(string("Queue is full"));
      pMem[last] = item;
      last = (last + 1) % size;
      count++;
    }

    ~TQueue()
    {
      delete [] pMem;
    }

};



#endif