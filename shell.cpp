#include<iostream>
#include <list>
#include <vector>
#include <string>
#include "Pcb.h"
#include "Manager.h"
#include "Ready.h"
using namespace std;
int cmd(string str1)
{
	string str[]={"init","to","lres","lblk","lrea","de","cr","req","rel"};
	for(int i=0;i<10;i++)
	{
		if(str1 == str[i])
			return i;
	}
	return -1;
}
int r_id(string str2){
	string res[] = { "R1", "R2", "R3", "R4" };
	for (int i = 0; i < 4; i++)
	{
		if (str2 == res[i]) return i+1;
	}
	return -1;
}
void devide_str(const string& str,  const string& c,vector<string>& v)
{
	string::size_type y = str.find(c);
	string::size_type x = 0;
	while (string::npos != y)
	{
		v.push_back(str.substr(x, y - x));
		x = y + c.size();
		y = str.find(c, x);
	}
	if (x != str.length())
		v.push_back(str.substr(x));
}
int main(int argc,char *argv[])
{
	string str;
	while (getline(cin,str))
	{
		int id;
		int arg0 ;
		string arg1;
		int arg2 ;
		vector<string> v_str  ;
		devide_str(str, " ",v_str);
		if (v_str.size() >= 1) arg0 = cmd(v_str[0]);
		if (v_str.size()>=2) arg1 = v_str[1];
		if (v_str.size()>= 3) arg2 = atoi(v_str[2].c_str());
		switch(arg0)
		{
		case 0:
			RCB_class::init();
			PCB::create("init",0);
			break;
		case 1:
			Ready::time_out();
			break;
		case 2:
			RCB_class::show_res();
			break;
		case 3:
			RCB_class::show_waiting_list();
			break;
		case 4:
			Ready::show_ready();
			break;
		case 5:
			PCB::Distory(arg1);
			break;
		case 6:
			PCB::create(arg1,arg2);
			break;
		case 7:
			id = r_id(arg1);
			RCB_class::request(Ready::run_pid,id,arg2);
			break;
		case 8:
			id = r_id(arg1);
			RCB_class::release_some(Ready::run_pid,id,arg2);
			break;
		default:
			cout << "ÇëÊäÈëÓÐÐ§ÃüÁî£¡"<<endl;
		}
	}
	return 0;
}
