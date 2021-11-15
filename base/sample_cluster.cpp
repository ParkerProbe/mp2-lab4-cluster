
#include "cluster.h"

int main()
{
  int _tacts, _sizequeue, _cpu;
  double _chance;
  cin >> _tacts >> _sizequeue >> _chance >> _cpu;
  TClasster cluster(_tacts,_sizequeue, _chance, _cpu);
  cluster.Start();
  cluster.Get_Status();
  return 0;
}