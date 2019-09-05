#include "Ready.h"
#include "Pcb.h"
#include "pcb_rcb.h"
#include "Manager.h"
#include <list>
#include <iostream>
using namespace std;
int Ready::run_priority = -1;
int Ready::run_pid = -1;//用来标志运行进程
int time = -1;
void Ready::insert(int priority,int pid)
{
	list<PCB>::iterator i=PCB::serch_pcb(pid);
	if(i->m_ipriority == 0 )
	{
		Ready::RL0.push_back(*i);
	}
	if(i->m_ipriority == 1 )
	{
		Ready::RL1.push_back(*i);
	}
	if(i->m_ipriority == 2 )
	{
		Ready::RL2.push_back(*i);
	}

}

void Ready::remove(int priority,int pid)
{
	if(priority == 1)
	{
		list<PCB>::iterator i;
		for(i=Ready::RL1.begin();i != Ready::RL1.end();)
		{
			if(i->m_iPID >= pid)
			{
				i = Ready::RL1.erase(i++);
			}
			else
			{
				i++;
			}
		}
	}
	else if( priority == 2)
	{
		list<PCB>::iterator i;
		for(i=Ready::RL2.begin();i != Ready::RL2.end();)
		{
			if(i->m_iPID >= pid)
			{
				i = Ready::RL2.erase(i++);
			}
			else
			{
				i++;
			}
		}
	}
}

void Ready::time_out()
{
	time = 1;
	schedule();
}

void Ready::show_ready()
{
	{
		cout << "0:";
		list<PCB>::iterator i;
		for(i=Ready::RL0.begin();i != Ready::RL0.end();i++)
		{
			cout<< i->m_strname <<"  ";
		}
		cout << endl;
	}
	{
		cout << "1:";
		list<PCB>::iterator i;
		for(i=Ready::RL1.begin();i != Ready::RL1.end();i++)
		{
			cout<< i->m_strname <<"  ";
		}
		cout << endl;
	}
	{
		cout << "2:";
		list<PCB>::iterator i;
		for(i=Ready::RL2.begin();i != Ready::RL2.end();i++)
		{
			cout<< i->m_strname <<"  ";
		}
		cout << endl;
	}
}

void Ready::schedule()
{
	int First_PID = -1;
	if (!RL2.empty() && run_priority<=2)
	{
		First_PID = RL2.front().m_iPID;
		if (run_priority < 2|| time)
		{
			if (run_pid != -1)
			{
				list<PCB>::iterator i=PCB::serch_pcb(run_pid);
				i->m_istate = 1;
				Ready::insert(run_priority,run_pid);
			}
			run_pid = First_PID;
			run_priority = 2;
			RL2.begin()->m_istate = 0;
			list<PCB>::iterator i=PCB::serch_pcb(RL2.begin()->m_iPID);
			i->m_istate = 0;
			RL2.pop_front();
		}

	}
	else if (!RL1.empty() && run_priority <= 1)
	{
		First_PID = RL1.front().m_iPID;
		if (run_priority < 1|| time)
		{
			if (run_pid != -1)
			{
				list<PCB>::iterator i=PCB::serch_pcb(run_pid);
				i->m_istate = 1;
				Ready::insert(run_priority,run_pid);
			}
			run_pid = First_PID;
			run_priority = 1;
			RL1.begin()->m_istate = 0;
			list<PCB>::iterator i=PCB::serch_pcb(RL1.begin()->m_iPID);
			i->m_istate = 0;
			RL1.pop_front();
		}
	}
	else if (!RL0.empty() && run_priority <= 0)
	{
		First_PID = RL0.front().m_iPID;
		if (run_priority < 0|| time)
		{
			if (run_pid != -1)
			{
				list<PCB>::iterator i=PCB::serch_pcb(run_pid);
				i->m_istate = 1;
				Ready::insert(run_priority,run_pid);
			}
			run_pid = First_PID;
			run_priority = 0;
			RL0.begin()->m_istate = 0;
			list<PCB>::iterator i=PCB::serch_pcb(RL0.begin()->m_iPID);
			i->m_istate = 0;
			RL0.pop_front();
		}
	}
	time = 0;
	list<PCB>::iterator i=PCB::serch_pcb(run_pid);
	cout << "running process:  " <<i->m_strname <<endl;
}

void Ready::set_res(int priority,int pid,int rid,int n)
{
	if(priority == 0)
	{
		list<PCB>::iterator i;
		for(i=Ready::RL0.begin();i != Ready::RL0.end();i++)
		{
			if(pid == i->m_iPID)
				i->r[rid-1]+=n;
		}
	}
	if(priority == 1)
	{
		list<PCB>::iterator i;
		for(i=Ready::RL1.begin();i != Ready::RL1.end();i++)
		{
			if(pid == i->m_iPID)
				i->r[rid-1]+=n;
		}
	}
	if(priority == 2)
	{
		list<PCB>::iterator i;
		for(i=Ready::RL2.begin();i != Ready::RL2.end();i++)
		{
			if(pid == i->m_iPID)
				i->r[rid-1]+=n;
		}
	}

}