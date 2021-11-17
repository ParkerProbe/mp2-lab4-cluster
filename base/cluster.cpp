#include "cluster.h"
#include <iostream>

Cluster::Cluster(int _tacts, int _sizequeue, double _chance, int _cpu)
: fail_tasks(0), complete_tasks(0), error_tasks(0), active_tasks(0), downtime(0),
all_time(0), all_tasks(0), average_load(0)
{
  if((_tacts > 1000) || (_tacts < 10))
    throw(string("Incorrect number of tacts"));
  if((_cpu > 64) || (_cpu < 1))
    throw(string("Incorrect number of cpu"));
  if((_sizequeue > 50) || (_sizequeue < 5))
    throw(string("Incorrect size of queue"));
  if((_chance > 1) || (_chance <= 0))
    throw(string("Incorrect value of task generation chance"));

  all_tacts = _tacts;
  size_queue = _sizequeue;
  chance = _chance;
  all_cpu = _cpu;
  free_cpu = _cpu;
  load_cpu = 0;
}

int Cluster::Random(int min, int max) const
{
  random_device rd;
  mt19937 engine(rd());
  uniform_int_distribution<int> dist{min, max};
  return dist(engine);
}

Task Cluster::StartNewTask()
{
  Task task;
  task.Cpu = Random(1, all_cpu);
  task.Ticks = Random(1, 10); //Need check
  return task;
}

void Cluster::Get_Status()
{
  average_load /= all_tacts;
  cout << "----------------[System Status]--------------------" << endl;
  cout << "Total number of tasks:" << all_tasks << endl;
  cout << "Number of completed tasks:" << complete_tasks << endl;
  cout << "Number of error tasks:" << error_tasks << endl;
  cout << "Number of failed tasks:" << fail_tasks << endl;
  cout << "Number of downtime tacts:" << downtime << endl;
  cout << "Average system load:" << average_load << endl;
  cout << "Number of failed tasks:" << fail_tasks << endl;
}



void Cluster::Start()
{
  TQueue<Task> queue(size_queue);
  Task temp;
  for(int i = 0; i < all_tacts; i++) {
    //Start new task
    if(static_cast<double>(Random(0, 10))/10 > chance) {
      if(queue.IsFull()) {
        error_tasks++;
      }
      else{
        temp = StartNewTask();
        queue.Push(temp);
        all_tasks++;
      }
    }

    //Add new tasks
    if(free_cpu) {
      while(queue.GetFirst().Cpu <= free_cpu && !queue.IsEmpty()) {
        active_tasks++;
        free_cpu -= queue.GetFirst().Cpu;
        load_cpu += queue.GetFirst().Cpu;
        jobs.push_back(queue.Pop());
      }
    }

    //Do tasks
    for(int j = 0; j < jobs.size(); j++) {
      if(jobs[j].Ticks != 0) {
        jobs[j].Ticks--;
      }
      else {
        free_cpu += jobs[j].Cpu;
        load_cpu -= jobs[j].Cpu;
        active_tasks--;
        complete_tasks++;
        jobs.erase(jobs.begin() + j);
      }
    }

    //Statistic
    if (load_cpu == 0)
      downtime++;
    average_load += load_cpu;
  }
  //Count fail tasks
  for(int j = 0; j < jobs.size(); j++) {
    if(jobs[j].Ticks != 0) {
      fail_tasks++;
    }
  }
}

