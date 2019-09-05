#ifndef READY_H
#define READY_H
#include<list>
#include "Pcb.h"
class Ready
{
public:
	static int run_priority;
	static int run_pid;
	static list<PCB> RL0;             //���ȼ�Ϊ0�ľ�����������
	static list<PCB> RL1;             //���ȼ�Ϊ1�ľ�����������
	static list<PCB> RL2;             //���ȼ�Ϊ2�ľ�����������
public:
	static void remove(int priority,int pid);
	static void insert(int priority,int pid);
	static void set_res(int priority,int pid,int rid,int n);
	static void show_ready();
	static void time_out();
	static void schedule();
};
#endif