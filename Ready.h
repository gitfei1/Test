#ifndef READY_H
#define READY_H
#include<list>
#include "Pcb.h"
class Ready
{
public:
	static int run_priority;
	static int run_pid;
	static list<PCB> RL0;             //优先级为0的就绪队列链表
	static list<PCB> RL1;             //优先级为1的就绪队列链表
	static list<PCB> RL2;             //优先级为2的就绪队列链表
public:
	static void remove(int priority,int pid);
	static void insert(int priority,int pid);
	static void set_res(int priority,int pid,int rid,int n);
	static void show_ready();
	static void time_out();
	static void schedule();
};
#endif