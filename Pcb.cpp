#include "Pcb.h"
#include "Ready.h"
#include "Manager.h"
#include <iostream>
#include <list>
#include <string>
using namespace std;
list<PCB> Ready::RL0;             //���ȼ�Ϊ0�ľ�����������
list<PCB> Ready::RL1;             //���ȼ�Ϊ1�ľ�����������
list<PCB> Ready::RL2;  
list<PCB>PCB::process_tree;
int pid = -1;

PCB PCB::create(string name,int priority)
{
	PCB pcb;
	pcb.m_iPID = ++pid;//����pid
	pcb.m_strname = name;
	pcb.m_istate = 1;
	pcb.m_ipriority = priority;
	pcb.block_num = 0;
	pcb.block_rid = 0;
	memset(pcb.r, 0, sizeof(pcb.r));
	PCB::process_tree.push_back(pcb);//���������
	Ready::insert(priority,pid);//�����������
	cout << "create: " << pcb.m_strname << "  successful" << endl;
	Ready::schedule();
	return pcb;
}
void PCB::Distory(string name)
{
	int pid;
	list<PCB>::iterator it;
	for(it=PCB::process_tree.begin();it != PCB::process_tree.end();it++)
	{
		if(it->m_strname == name)
		{
			pid = it->m_iPID;
		}
	}

	RCB_class::release_all(pid);//�ͷ�������Դ
	/////////////////////////ɾ���������еĽ���///////////////
	list<PCB>::iterator i;
	int priority = 0;
	int state = 0;
	int rid;
	int k = PCB::process_tree.size();
	int m=0,j=0;
	for(i=PCB::process_tree.begin();i != PCB::process_tree.end();i++,j++)
	{
		if(i->m_iPID == pid)
		{
			m = j;	
			priority = i->m_ipriority;
			state = i->m_istate;
			rid = i->block_rid;
		}
	}
	for(;k>m;k--)
	{
		PCB::process_tree.pop_back();//ɾ���ý��̵��ӽ���
	}
	/////////////////////////ɾ�����������еĽ���///////////////
	if(state ==1)
	{
		Ready::remove(priority,pid);
	}
	else if(state == 2)
	{
		list<PCB>::iterator i2;
		for(i2=RCB_class::rcb_vec[rid-1].waiting_list.begin();i2 != RCB_class::rcb_vec[rid-1].waiting_list.end();)
		{
			if(i2->m_iPID == pid)
			{
				i2 = RCB_class::rcb_vec[rid-1].waiting_list.erase(i2++);
			}
			else
			{
				i2++;
			}
		}
	}
	if (pid <= Ready::run_pid)
	{
		Ready::run_priority = -1;
		Ready::run_pid = -1;
	}
	cout << "delete success!"<<endl;;
	Ready::schedule();
}

list<PCB>::iterator PCB::serch_pcb(int pid)
{
	static list<PCB>::iterator it; 
	for (it = PCB::process_tree.begin(); it != PCB::process_tree.end(); it++)
	{
		if (it->m_iPID == pid)
		{
			return it;
		}
	}

}
