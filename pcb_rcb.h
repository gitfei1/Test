#ifndef PCB_RCB_H
#define PCB_RCB_H
#include <string>
#include <list>
#include "Pcb.h"
using namespace std;

struct RCB
{
	int m_iRID;
	string m_strname;
	int m_inial;
	int m_iavailable;
	list<PCB>waiting_list;
};
#endif