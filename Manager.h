#ifndef MANANGER_H
#define MANANGER_H
#include "Pcb.h"
#include "pcb_rcb.h"
#include <list>
#include <vector>
class RCB_class
{
public:
	static vector<RCB> rcb_vec;
public:
	static void init();
	static void release_all(int pid);
	static void request(int pid,int rid,int n);
	static void release_some(int pid,int rid,int n);
	static void show_waiting_list();
	static void show_res();
};

#endif