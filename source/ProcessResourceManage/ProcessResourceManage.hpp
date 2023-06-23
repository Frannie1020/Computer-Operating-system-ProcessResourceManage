/**************************************
 * ProcessResourceManage.hpp
 * ������Դ������غ�����ʵ��
 * Created on: May 3, 2019
 * Author: 盖聂
**************************************/

#pragma once
#include "DataStructure.hpp"

using namespace std;

//������Դ����������
class ProcessResourceManage {
private:
	list<int> redyList[3];    //�����洢���̵�����

public:
	int currentRunning;    //��ǰ�������еĽ��̵�id
	RCB rcb[4];    //��Դ���ƿ飬4������Ӧ������Դ
	PCB pcb[20];    //���̿��ƿ飬20���������ͬʱ��20������

	ProcessResourceManage();    //���캯���г�ʼ�����е�һЩ����
	~ProcessResourceManage();    //��������
	void init();    //��ʼ��
	void create(string name, int p);    //��������
	int scheduler();    //���̵���
	void destroy(int n);    //���̳���
	void processList();    //������н��̵���Ϣ
	void processInfo(string name);    //����������̵���Ϣ
	int search(string name);    //���ݽ��������ҽ��̵�λ��

	void request(int n, int unit);    //������Դ
	void release(int n, int unit);    //�ͷ���Դ
	void resourceList();    //���������Դ����Ϣ

	void timeout();    //��ʱ�ж�
};

//���캯������ʼ�����е�һЩ����
ProcessResourceManage::ProcessResourceManage() {
	//��ʼ�����̿��ƿ��id
	for (int i = 0; i < 20; i++) {
		pcb[i].id = i;
	}

	//��ʼ��0�Ž���Ϊ��ʼ������
	pcb[0].pname = "init";
	pcb[0].priority = 0;
	redyList[0].push_back(0);
	currentRunning = 0;

	//��ʼ����Դ���ƿ�
	for (int i = 0; i < 4; i++) {
		rcb[i].initial = 1;
		rcb[i].status = 1;
	}
	//������Դ������
	rcb[0].rname = "R1";
	rcb[1].rname = "R2";
	rcb[2].rname = "R3";
	rcb[3].rname = "R4";
}

//��������
ProcessResourceManage::~ProcessResourceManage() {}

//��ʼ����������Ӧinit����
void ProcessResourceManage::init() {
	//��ʼ�����̿��ƿ��б�����ֵ
	for (int i = 1; i < 20; i++) {
		pcb[i].pname = " ";
		pcb[i].state = "ready";
		pcb[i].parent = -1;
		pcb[i].children = -1;
		pcb[i].next = -1;
		pcb[i].previous = -1;
		pcb[i].priority = -1;
		pcb[i].resource[0].rid = -1;
		pcb[i].resource[1].rid = -1;
		pcb[i].resource[2].rid = -1;
		pcb[i].resource[3].rid = -1;
		pcb[i].resource[0].used = 0;
		pcb[i].resource[1].used = 0;
		pcb[i].resource[2].used = 0;
		pcb[i].resource[3].used = 0;
		pcb[i].resource[0].waitNum = 0;
		pcb[i].resource[1].waitNum = 0;
		pcb[i].resource[2].waitNum = 0;
		pcb[i].resource[3].waitNum = 0;
	}
	currentRunning = 0;    //��ǰ����ִ�еĽ�����init

	//��ʼ����Դ���ƿ�
	for (int i = 0; i < 4; i++) {
		rcb[i].initial = i + 1;
		rcb[i].status = i + 1;
		while (!rcb[i].waitList.empty()) {
			rcb[i].waitList.pop_front();
		}
	}

	//��ʼ�����̶���
	for (int i = 0; i < 3; i++) {
		while (!redyList[i].empty()) {
			redyList[i].pop_back();
		}
	}
}

//��������
void ProcessResourceManage::create(string name, int p) {
	for (int i = 1; i < 20; i++) {
		//�ҵ�һ��δ����Ľ��̿��ƿ���з���
		if (pcb[i].pname == " ") {
			pcb[i].pname = name;   //������
			pcb[i].priority = p;    //���ȼ�
			redyList[p].push_back(pcb[i].id);
			pcb[i].parent = currentRunning;    //������
			//���ý��̿��ƿ��н��̵Ĵ����ϵ
			for (int j = 1; j < 20; j++) {
				if (j < i && pcb[j].parent == pcb[i].parent) {
					pcb[j].previous = i;
					pcb[i].next = j;
				}
			}
			break;
		}
	}
	scheduler();    //���µ���
}

//���̵���
int ProcessResourceManage::scheduler() {
	if (!redyList[2].empty()) {
		currentRunning = redyList[2].front();
		pcb[currentRunning].state = "running";
		return redyList[2].front();
	}
	else if (!redyList[1].empty()) {
		currentRunning = redyList[1].front();
		pcb[currentRunning].state = "running";
		return redyList[1].front();
	}
	else {
		currentRunning = 0;
		pcb[currentRunning].state = "running";
		return 0;
	}
}

//��������
void ProcessResourceManage::destroy(int n) {
	//���ͷŽ���ռ�õ���Դ
	for (int i = 0; i < 4; i++) {
		if (pcb[n].resource[i].used != 0) {
			release(i, pcb[n].resource[i].used);
			if (rcb[i].status > rcb[i].initial) {
				cout << "destroy failed: delete resources error" << endl;
			}
			pcb[n].resource[i].rid = -1;
			pcb[n].resource[i].used = 0;
		}
	}
	//��������������л��ھ���״̬����Ӿ�������ɾ��
	if (pcb[n].state == "ready" or pcb[n].state == "running") {
		int p = pcb[n].priority;
		redyList[p].remove(n);
	}
	//�������������״̬��������������ɾ��
	else if ((pcb[n].state).compare("blocked") == 0) {
		for (int i = 0; i < 4; i++) {
			rcb[i].waitList.remove(n);
		}
	}
	//����ɾ����pcb��Ӧλ�õı���
	for (int i = 0; i < 20; i++) {
		if (pcb[i].parent == n) {
			destroy(pcb[i].id);
		}
		if (pcb[i].id == n) {
			pcb[i].pname = " ";
			pcb[i].state = "ready";
			pcb[i].parent = -1;
			pcb[i].children = -1;
			pcb[i].next = -1;
			pcb[i].previous = -1;
			pcb[i].priority = -1;
			pcb[i].resource[0].rid = -1;
			pcb[i].resource[1].rid = -1;
			pcb[i].resource[2].rid = -1;
			pcb[i].resource[3].rid = -1;
			pcb[i].resource[0].used = 0;
			pcb[i].resource[1].used = 0;
			pcb[i].resource[2].used = 0;
			pcb[i].resource[3].used = 0;
			pcb[i].resource[0].waitNum = 0;
			pcb[i].resource[1].waitNum = 0;
			pcb[i].resource[2].waitNum = 0;
			pcb[i].resource[3].waitNum = 0;
		}
		if (pcb[i].next == n) {
			pcb[i].next = -1;
		}
		if (pcb[i].previous == n) {
			pcb[i].previous = -1;
		}
	}
	scheduler();
}

//��ʾ���н���
void ProcessResourceManage::processList()
{
	cout << "All processes and their status��" << endl;
	//�������н��̿��ƿ飬������ֲ�Ϊ�����ӡ����Ӧ����Ϣ
	for (int i = 1; i < 20; i++) {
		if (pcb[i].pname != " ") {
			cout << "    " << pcb[i].pname << "  " << pcb[i].state << endl;
		}
	}
}

//����������̵���Ϣ
void ProcessResourceManage::processInfo(string name)
{
	int t = search(name);    //��������Ӧ�Ľ���
	if (t != -1)    //����ҵ����ӡ������Ϣ
	{
		cout << "the info of process " << name << " ��" << endl;
		cout << "    " << pcb[t].pname << "  " << pcb[t].state << endl;
	}
	else
	{
		cout << "the process does not exist!" << endl;
	}
}

//�����������������ý�����PCB�е�λ��
int ProcessResourceManage::search(string name) {
	//��������
	for (int i = 0; i < 20; i++) {
		if (name.compare(pcb[i].pname) == 0) {
			return i;
		}
	}
	return -1;
}

//������Դ
void ProcessResourceManage::request(int n, int unit) {
	//����������ԴС��ʣ����Դ�����
	if (rcb[n].status >= unit) {
		rcb[n].status = rcb[n].status - unit;
		pcb[currentRunning].resource[n].rid = n;
		pcb[currentRunning].resource[n].used += unit;
	}
	//��Դ�����ã���������
	else {
		pcb[currentRunning].state = "blocked";
		pcb[currentRunning].resource[n].waitNum += unit;
		rcb[n].waitList.push_back(currentRunning);
		redyList[pcb[currentRunning].priority].remove(currentRunning);
	}
	scheduler();
}

//�ͷ���Դ
void ProcessResourceManage::release(int n, int unit) {
	pcb[currentRunning].resource[n].used -= unit;
	rcb[n].status += unit;
	int temp_pcb = rcb[n].waitList.front();
	while (temp_pcb != 0 && pcb[temp_pcb].resource[n].waitNum <= rcb[n].status) {
		rcb[n].status -= pcb[temp_pcb].resource[n].waitNum;
		rcb[n].waitList.remove(temp_pcb);
		pcb[temp_pcb].state = "ready";
		pcb[temp_pcb].resource[n].used += pcb[temp_pcb].resource[n].waitNum;
		redyList[pcb[temp_pcb].priority].push_back(temp_pcb);
	}
	scheduler();//���ȳ���
}

//���������Դ����Ϣ
void ProcessResourceManage::resourceList()
{
	cout << "All resources and their status��" << endl;
	//����������Դ����ӡ����Ϣ
	for (int i = 0; i < 4; i++) {
		cout << "    " << rcb[i].rname << " " << rcb[i].initial << " " << rcb[i].status << endl;
	}
}

//��ʱ�ж�
void ProcessResourceManage::timeout() {
	//���ᵱǰ���̵�ִ�У����µ���
	int p = pcb[currentRunning].priority;
	redyList[p].remove(currentRunning);
	pcb[currentRunning].state = "ready";
	redyList[p].push_back(currentRunning);
	scheduler();
}
