#include "Manager.h"
#include "Ready.h"
#include "Pcb.h"
#include "pcb_rcb.h"
#include <vector>
#include <iostream>
#include <string>
#include <list>
using namespace std;
vector<RCB>RCB_class::rcb_vec;
RCB Res_set[4] = { { 1, "R1", 1, 1 }, { 2, "R2", 2, 2 }, { 3, "R3", 3, 3 }, { 4, "R4", 4, 4 } };
void RCB_class::init(){

	for (int i = 0; i < 4; i++)
	{
		RCB_class::rcb_vec.push_back(Res_set[i]);
	}
	cout << "init resources success!" << endl;
}

void RCB_class::release_all(int pid)//删除进程才使用
{
	list<PCB>::iterator j=PCB::serch_pcb(pid);
	for (int i = 0; i < RCB_class::rcb_vec.size(); i++)
	{
		RCB_class::rcb_vec[i].m_iavailable += j->r[i]; //释放资源
	}
	for(int q=0;q<RCB_class::rcb_vec.size();q++)//删除进程后，遍历阻塞队列，满足资源需求的进程移到就绪队列中
	{
		if((!RCB_class::rcb_vec[q].waiting_list.empty())&& RCB_class::rcb_vec[q].waiting_list.begin()->block_num<=RCB_class::rcb_vec[q].m_iavailable)
		{
			Ready::insert(RCB_class::rcb_vec[q].waiting_list.begin()->m_ipriority,RCB_class::rcb_vec[q].waiting_list.begin()->m_iPID);
			RCB_class::rcb_vec[q].waiting_list.pop_front();
		}
	}
}

void RCB_class::request(int pid,int rid,int n)//请求资源
{

	if(RCB_class::rcb_vec[rid-1].m_iavailable >= n)
	{
		RCB_class::rcb_vec[rid-1].m_iavailable -= n;  //allocate
		list<PCB>::iterator i = PCB::serch_pcb(pid);
		i->r[rid-1] += n;
		int x = i->r[rid-1];
		if(x < 0) cout << "failed to add " << endl;
		Ready::set_res(i->m_ipriority,i->m_iPID,rid,n);
		cout << "request success!" << endl;
	}
	else
	{
		if(n > RCB_class::rcb_vec[rid-1].m_inial)
		{
			cout << "request most than inialize" << endl;
			//exit(1);
		}
		list<PCB>::iterator i=PCB::serch_pcb(pid);
		i->m_istate = 2;//blocked
		i->block_num = n;
		i->block_rid = rid;
		RCB_class::rcb_vec[rid-1].waiting_list.push_back(*i);
		//Ready::remove(i->m_ipriority,pid);
		Ready::run_pid = -1;
		Ready::run_priority = -1;
		cout << "block: " <<i->m_strname<<endl;
		Ready::schedule();
	}
}

void RCB_class::release_some(int pid,int rid,int n)//释放部分资源
{
	RCB_class::rcb_vec[rid-1].m_iavailable += n;//释放资源
	int number = 0;
	number = RCB_class::rcb_vec[rid-1].waiting_list.begin()->block_num;
	int id = RCB_class::rcb_vec[rid-1].waiting_list.begin()->m_iPID;
	int pri = RCB_class::rcb_vec[rid-1].waiting_list.begin()->m_ipriority;
	while(RCB_class::rcb_vec[rid-1].waiting_list.size() != 0 && number <= RCB_class::rcb_vec[rid-1].m_iavailable)
	{
		RCB_class::rcb_vec[rid-1].m_iavailable -= number;
		RCB_class::rcb_vec[rid-1].waiting_list.begin()->r[rid-1] = number;
		list<PCB>::iterator i=PCB::serch_pcb(id);
		i->r[rid-1] = number;
		Ready::insert(pri,id);
		RCB_class::rcb_vec[rid-1].waiting_list.pop_front();//如果释放资源导致阻塞队列第一个进程满足资源需求就移到就绪队列
	}
	cout << "release_some success!" << endl;
	Ready::schedule();
}

void RCB_class::show_waiting_list()
{
	//cout << "wait_list:"<<endl;
	list<PCB>::iterator j;
	for(int i=0;i<RCB_class::rcb_vec.size();i++)
	{
		cout << "r" << i+1 << "  " ;
		for(j=RCB_class::rcb_vec[i].waiting_list.begin();j != RCB_class::rcb_vec[i].waiting_list.end();j++)
		{
			cout << "   " << j->m_strname ;
		}
		cout << endl;
	}
}

void RCB_class::show_res()
{
	for (int i = 0; i < 4; i++)
	{
		cout << "R" << i+1 << "  " <<RCB_class::rcb_vec[i].m_iavailable<<endl;
	}
}