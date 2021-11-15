#ifndef __QUEUE_H__
#define __QUEUE_H__

#include "string"

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