#ifndef PCB_H
#define PCB_H
#include <string>
#include <list>
using namespace std;

class PCB
{
public:
	int m_iPID;                  //����id  ��������
	string m_strname;
	int r[4];					 //ӵ��������Դ������
	int m_istate;                //"running"/"ready"/"block"0,1,2
	int m_ipriority;             //�������ȼ� 0,1��2
	int block_num;
	int block_rid;
	static list<PCB>process_tree;
public:
	static PCB create(string name,int priority);
	static void Distory(string name);
	static list<PCB>::iterator serch_pcb(int pid);
	//void print();
};
#endif