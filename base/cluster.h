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
	int Ticks;
	int Cpu;
};

class TClasster
{
private:
	double chance;  //Интенсивность потока задач
	int all_tacts;  //Количество тактов
	int all_cpu;  //Всего процессоров
	int size_queue;  //очередь кластера

	int fail_tasks;  //Число незавершенных задач
	int complete_tasks;  //Число завершенных задач
	int error_tasks;  //Число откланённых задач (из-за переполнения очереди)
  int active_tasks;
	int downtime;  //такты простоя
	int all_time;  //Все время выполнения всех задач
	int all_tasks;  //Всего задач
  int average_load; //сколько процессоров на кажом такте
	int free_cpu; //Свободные процессоры
	int load_cpu;  //Загруженные процессоры

	vector<Task> jobs;
	Task StartNewTask();
	int Random(int min, int max) const;

public:
  TClasster(int _tacts = 1000, int _sizequeue = 50, double _chance = 0.5, int _cpu = 4);
	void Start();
	void Get_Status();
};

#endif