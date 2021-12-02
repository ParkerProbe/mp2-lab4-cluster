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
  // Max count of tacts that task can take
  const int kmax_task_len = 10;
  
  // Max count of tasks generated on every tact
  const int kmax_task_cnt = 4;

  // Limits
  const int kmin_tacts = 10;
  const int kmax_tacts = 1000;
  const int kmin_size_queue = 5;
  const int kmax_size_queue = 50;
  const double klimit_chance = 0.0;
  const double kmax_chance = 1.0;
  const int kmin_cpu = 1;
  const int kmax_cpu = 64;



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
  Cluster(int _tacts = 1000, int _sizequeue = 50, double _chance = 0.5, int _cpu = 4);
  void Start();
  void Get_Status();
};

#endif