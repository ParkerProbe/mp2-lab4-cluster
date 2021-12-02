
#include "cluster.h"

int main()
{
  int _tacts, _sizequeue, _cpu;
  double _chance;
  cout << "[Cluster Simulation program]" << endl << endl;
  cout << "Please write simulation parameters" << endl;
  
  cout << "1) Count of cluster working tacts:" << endl;
  cin >> _tacts;
  
  cout << "2) Size of cluster`s queue:" << endl;
  cin >> _sizequeue;
  
  cout << "3) Chance to generate new task on cluster`s tick" << endl;
  cin >> _chance;
  
  cout << "4) Count of cpu in cluster" << endl;
  cin >> _cpu;

  try {
    Cluster cluster(_tacts, _sizequeue, _chance, _cpu);
    cluster.Start();
    cluster.Get_Status();
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
  return 0;
}