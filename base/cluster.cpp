#include "cluster.h"
#include <iostream>
#include <vector>

Cluster::Cluster(int _tacts, int _sizequeue, double _chance, int _cpu)
: fail_tasks(0), complete_tasks(0), error_tasks(0), downtime(0),
all_time(0), all_tasks(0), average_load(0)
{
  if((_tacts > kmax_tacts) || (_tacts < kmin_tacts))
    throw(string("Incorrect number of tacts"));
  if((_cpu > kmax_cpu) || (_cpu < kmin_cpu))
    throw(string("Incorrect number of cpu"));
  if((_sizequeue > kmax_size_queue) || (_sizequeue < kmin_size_queue))
    throw(string("Incorrect size of queue"));
  if((_chance > kmax_chance) || (_chance <= klimit_chance))
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
  task.ticks = Random(1, kmax_task_len);
  task.is_work = false;
  task.pid = pid;
  return task;
}

void Cluster::Get_Status()
{
  average_load /= all_tacts;

  cout << "----------------[Cluster Status]--------------------" << endl;
  cout << "Total number of tasks:" << all_tasks << endl;
  cout << "Number of completed tasks:" << complete_tasks << endl;
  cout << "Number of error tasks:" << error_tasks << endl;
  cout << "Number of failed tasks:" << fail_tasks << endl;
  cout << "Number of downtime tacts:" << downtime << endl;
  cout << "Average system load:" << average_load << endl;
  cout << "Average cpu load:" << average_load << endl;
  cout << endl;
  cout << "Cpu load model:\n";
  cout << "\n";
  for (int i = 1; i <= all_cpu; i++) {
    if (i % 2 == 0) {
      if (i <= average_load)
        cout << "[x]\n";
      else
        cout << "[ ]\n";
    }
    else
      if (i <= average_load)
        cout << "[x] ";
      else
        cout << "[ ] ";
  }
}

void Cluster::Start()
{
  TQueue<Task> queue(size_queue);
  int active_tasks = 0;

  struct PrTask { 
    Task task;
    int priority;
    PrTask() : task(), priority() {}
    PrTask(Task _task, int _priority) :
      task(_task), priority(_priority) {}
  };

  vector<PrTask> made_tasks(0);
  Task temp;
  int pid_acc = 0;
  for(int i = 0; i < all_tacts; i++) {
    //Start new tasks
    int cnt_gen_tasks = Random(1, kmax_task_cnt);
    for (int i = 0; i < cnt_gen_tasks; i++) {
      if (static_cast<double>(Random(0, 10)) / 10 > chance) {
        if (queue.IsFull()) {

          // Statistic
          error_tasks++;
        }
        else {
          queue.Push(StartNewTask(pid_acc), Random(2, 8));
          pid_acc++;

          // Statistics
          all_tasks++;
        }
      }
    }

    //Do tasks
    if(!queue.IsEmpty()) {
      PrTask temp;

      while (!queue.IsEmpty()) {
        temp.priority = queue.GetFirstPriority();
        temp.task = queue.Pop();
        cout << temp.priority << endl;
        if(temp.task.ticks == 0) {
          active_tasks--;
          complete_tasks++;
          free_cpu += temp.task.cpu;
          load_cpu -= temp.task.cpu;
        }
        else {
          if (!temp.task.is_work) {
            if (temp.task.cpu <= free_cpu) {
              active_tasks++;
              temp.task.is_work = true;
              free_cpu -= temp.task.cpu;
              load_cpu += temp.task.cpu;
              temp.priority--;
              temp.task.ticks--;
              made_tasks.push_back(PrTask(temp.task, temp.priority));
            }
            else {
              temp.priority--;
              if (temp.priority < 0) {
                made_tasks.push_back(PrTask(temp.task, 2));
              }
              else {
                queue.Push(temp.task, temp.priority);
              }
            }
          }
          else {
            temp.task.ticks--;
            temp.priority--;
            made_tasks.push_back(PrTask(temp.task, temp.priority));
          }
        }
      }
      // Statistics
      if (load_cpu == 0)
        downtime++;
      average_load += load_cpu;

      // Copy to queue from made_tasks
      for(int i = 0; i < made_tasks.size(); i++) {
        queue.Push(made_tasks[i].task, made_tasks[i].priority);
      }
      queue.IncreasePriority(1);
      made_tasks.clear();
    }   
  }
  
  //Count fail tasks
  fail_tasks = queue.GetCount();
}