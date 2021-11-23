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
    int size;
    int first;
    int last;
    int count;
    
    struct Item
    {
      T obj;
      double priority; 

      bool operator<(const Item& other)
      { 
        return priority < other.priority;
      }
    };
    Item* pMem;


  public:
    TQueue(int _size)
    {
      if((_size < 0) ||(_size > MaxQueueSize))
        throw(string("Incorrect size of queue"));
      size = _size;
      first = -1;
      last = 0;
      count = 0;
      pMem = new Item[size];
    }
    TQueue(const TQueue& other)
    {
      pMem = new Item[other.size];
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
        Item* tmp_mem = new Item[other.size];
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
      for (int i = 0; i < size; i++) {
        if (this->pMem[i].obj != v.pMem[i].obj) {
          return false;
        }
        if (this->pMem[i].priority != v.pMem[i].priority) {
          return false;
        }
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
      return pMem[(first + 1) % size].obj;
    }

    T GetLast() const
    {
      return pMem[last].obj;
    }
    
    double GetFirstPriority() const
    {
      return pMem[first].priority;
    }
    
    void DecreaseFirstPriority(int _priority)
    {
      pMem[first].priority -= _priority;
      sort(pMem, pMem + count);
    }

    T Pop()
    {
      if(IsEmpty())
        throw(string("Queue is empty"));
      count--;
      first = (first + 1) % size;
      return pMem[first].obj;
    }

    void Push(T item, double _priority)
    {
      if(IsFull())
        throw(string("Queue is full"));
      pMem[last].obj = item;
      pMem[last].priority = _priority;
      sort(pMem, pMem + count);
      last = (last + 1) % size;
      count++;
    }
    
    void IncreasePriority(int inc)
    {
      for(int i = 0; i < count; i++) {
        pMem[i].priority += inc;
      }
    }

    ~TQueue()
    {
      delete [] pMem;
    }

};



#endif