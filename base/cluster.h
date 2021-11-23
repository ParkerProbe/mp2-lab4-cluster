#ifndef __POSTFIX_H__
#define __POSTFIX_H__
#include "queue.h"
#include <vector>
#include <time.h>
#include <iostream>
#include <chrono>
#include <random>

using namespace std;

struct Task
{
  int pid;
  bool is_work;

  int ticks;
  int cpu;
};

class Cluster
{
private:
  const int cnst_max_task_len = 10; 
  const int cnst_max_task_cnt = 4;

  double chance;  //Интенсивность потока задач
  int all_tacts;  //Количество тактов
  int all_cpu;  //Всего процессоров
  int size_queue;  //очередь кластера
  int fail_tasks;  //Число незавершенных задач
  int complete_tasks;  //Число завершенных задач
  int error_tasks;  //Число откланённых задач (из-за переполнения очереди)
  int downtime;  //такты простоя
  int all_time;  //Все время выполнения всех задач
  int all_tasks;  //Всего задач
  int average_load; //сколько процессоров на кажом такте
  int free_cpu; //Свободные процессоры
  int load_cpu;  //Загруженные процессоры

  Task StartNewTask(int pid);
  int Random(int min, int max) const;

public:
  // _tacts - [10; 1000] ; _sizequeue - [5 , 50]; _chance - (0, 1]; _cpu - [1, 64] 
  Cluster(int _tacts = 1000, int _sizequeue = 50, double _chance = 0.5, int _cpu = 4);
  void Start();
  void Get_Status();
};

#endif