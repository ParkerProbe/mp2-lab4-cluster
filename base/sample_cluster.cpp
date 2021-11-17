
#include "cluster.h"

int main()
{
  int _tacts, _sizequeue, _cpu;
  double _chance;
  cin >> _tacts >> _sizequeue >> _chance >> _cpu;
  Cluster cluster(_tacts,_sizequeue, _chance, _cpu);
  try {
    cluster.Start();
  }
  catch(string& e) {
    cout << "Error:" << e << endl;
  }
  catch (bad_alloc& e) {
    cout << "Error: " << "Dynamic Memory Allocation" << endl; 
    return 1;
  }
  catch(...){
    return 2;
  }
  cluster.Get_Status();
  return 0;
}