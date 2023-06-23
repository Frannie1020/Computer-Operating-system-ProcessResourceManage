/**************************************
 * DataStructue.hpp
 * ������ص����ݽṹ
 * Created on: May 3, 2019
 * Author: 盖聂
**************************************/
#pragma once
#include<list>
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//ȫ�ֱ��������ڱ�����������ļ�
extern ifstream infile;
extern ofstream outfile;

//��Դ���ƿ�
struct RCB {
	string rname = "Ri";    //��Դ����
	int initial = 0;    //��Դ����
	int status = 0;    //��Դ״̬
	list<int> waitList;    //�ȴ���Դ�Ľ����б�
};

//��Դ 
struct resource {
	int rid = -1;    //��ԴID
	int used = 0;    //�Ƿ�ռ��
	int waitNum = 0;    //�ȴ�����Դ�Ľ�����
};

//���̿��ƿ�
struct PCB {
	string pname = " ";    //������
	string  state = "ready";    //����״̬
	int id = -1;    //����id
	int parent = -1;    //������
	int children = -1;    //�ӽ���
	int previous = -1;    //�ý��̵�ǰһ������
	int next = -1;    //�ý��̵ĺ�һ������
	int priority = -1;    //�������ȼ�
	resource resource[4];    //������Դ
};