#include "cluster.h"
#include <iostream>
#include <vector>

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

Task Cluster::StartNewTask(int pid)
{
  Task task;
  task.cpu = Random(1, all_cpu);
  task.ticks = Random(1, 10); //Need check
  task.is_work = false;
  task.pid = pid;
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
  vector<Task> made_tasks(size_queue);
  int made_tasks_pr[size_queue];
  Task temp;
  int pid_acc = 0;
  for(int i = 0; i < all_tacts; i++) {
    //Start new tasks
    if(static_cast<double>(Random(0, 10))/10 > chance) {
      if(queue.IsFull()) {
        error_tasks++;
      }
      else{
        queue.Push(StartNewTask(pid_acc), Random(1, 8));
        pid_acc++;
        all_tasks++;
      }
    }

    //Statistic
    if (load_cpu == 0)
      downtime++;
    average_load += load_cpu;
    
    //Do tasks
    if(!queue.IsEmpty()) {
      for(Task temp = queue.GetFirst(); free_cpu || !queue.IsEmpty(); temp = queue.GetFirst()) {
        if(temp.ticks == 0) {
          active_tasks--;
          complete_tasks++;
          free_cpu += temp.cpu;
          load_cpu -= temp.cpu;
          queue.Pop();
        }
        if(temp.cpu <= free_cpu) {
          if(!temp.is_work) {
            active_tasks++;
            temp.is_work = true;
            free_cpu -= temp.cpu;
            load_cpu += temp.cpu;
          }
          temp.ticks--;
          queue.DecreaseFirstPriority(1);
          made_tasks.push_back(temp);
        }
        cout << temp.cpu << "|" <<  free_cpu << "|" << active_tasks << endl;
      }

      // Copy to queue from made_tasks
      for(int i = 0; i < made_tasks.size(); i++) {
        queue.Push(made_tasks[i], made_tasks_pr[i]);
      }
      queue.IncreasePriority(1);
      made_tasks.clear();
    }   
  }
  
  //Count fail tasks
  fail_tasks = queue.GetSize();
}