/**************************************
 * TestShell.hpp
 * TestShell�ľ���ʵ��
 * Created on: May 3, 2019
 * Author: 盖聂
**************************************/

#pragma once
#include "ProcessResourceManage.hpp"

using namespace std;

void testShell()
{
	string command, line, name;    //command���ڶ�ȡ���line���ڴ��ļ��а��ж�ȡ,name����������Դʱ������Դ��
	int priority, unit;    //priority�Ǵ�������ʱ���̵����ȼ���unit��Ҫ������ͷŵ���Դ����
	ProcessResourceManage prm;    //ʵ������Դ������
	//���ϴ��ļ��а��ж�ȡ��ֱ�������ļ�ĩβ
	while (getline(infile, line)) {
		istringstream linestream(line);    //����ȡ����һ��ת��Ϊ�ַ�����

		//��ȡ�����в�Ϊ���ҳ��ȴ��ڶ�
		if (!line.empty() && line.length() >= 2) {

			linestream >> command;    //�Ӷ����һ���еõ�����

			//��ʼ������
			if (command == "init") {
				prm.init();
				cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running����" << endl;
				outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running����" << endl;
			}
			//������������
			else if (command == "cr") {
				linestream >> name >> priority;
				if (prm.search(name) != -1) {
					cout << "error (duplicate name)" << endl;
					outfile << "error (duplicate name)" << endl;
				}
				else if (priority > 2 or priority <= 0) {
					cout << "error" << endl;
				}
				else {
					prm.create(name, priority);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
				}
			}
			//������������
			else if (command == "de") {
				linestream >> name;
				int t = prm.search(name);
				if (t == -1) {
					cout << "error (process not existed)" << endl;
					outfile << "error (process not existed)" << endl;
				}
				else {
					prm.destroy(t);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
				}
			}
			//������Դ����
			else if (command == "req") {
				linestream >> name >> unit;
				if (name == "R1" && unit == 1) {
					prm.request(0, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
				}
				else if (name == "R2" && (0 < unit && unit <= 2)) {
					prm.request(1, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
				}
				else if (name == "R3" && (0 < unit && unit <= 3)) {
					prm.request(2, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
				}
				else if (name == "R4" && (0 < unit && unit <= 4)) {
					prm.request(3, unit);
					cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
					outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
				}
				else {
					cout << "error (invalid request)" << endl;
					outfile << "error (invalid request)" << endl;
				}
			}
			//�ͷ���Դ����
			else if (command == "rel") {
				linestream >> name >> unit;
				if (name == "R1" && unit == 1) {
					if (prm.pcb[prm.currentRunning].resource[0].used >= unit) {
						prm.release(0, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
					}
					else {
						cout << "error (release exceed actual R1 units)" << endl;
						outfile << "error (release exceed actual R1 units)" << endl;
					}
				}
				else if (name == "R2" && (0 < unit && unit <= 2)) {
					if (prm.pcb[prm.currentRunning].resource[1].used >= unit) {
						prm.release(1, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
					}
					else {
						cout << "error (release exceed actual R2 units)" << endl;
						outfile << "error (release exceed actual R2 units)" << endl;
					}
				}
				else if (name == "R3" && (0 < unit && unit <= 3)) {
					if (prm.pcb[prm.currentRunning].resource[2].used >= unit) {
						prm.release(2, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
					}
					else {
						cout << "error (release exceed actual R3 units)" << endl;
						outfile << "error (release exceed actual R3 units)" << endl;
					}
				}
				else if (name == "R4" && (0 < unit && unit <= 4)) {
					if (prm.pcb[prm.currentRunning].resource[3].used >= unit) {
						prm.release(3, unit);
						cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
						outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
					}
					else {
						cout << "error (release exceed actual R4 units)" << endl;
						outfile << "error (release exceed actual R4 units)" << endl;
					}
				}
				else {
					cout << "error (invalid release)" << endl;
					outfile << "error (invalid release)" << endl;
				}

			}
			//��ʱ�ж�����
			else if (command == "to") {
				prm.timeout();
				cout << "Process " << prm.pcb[prm.currentRunning].pname << " is running!" << endl;
				outfile << "Process " << prm.pcb[prm.currentRunning].pname << " is running��" << endl;
			}
			//�г����н�������
			else if (command == "lp"){
			    prm.processList();
            }
			//�г�������Դ����
			else if (command == "lr"){
			    prm.resourceList();
            }
			//�г�ָ��������Ϣ����
			else if (command == "pi"){
			    linestream >> name;
				prm.processInfo(name);
            }
			//��������Ч������
			else {
				cout << "error command��" << endl;
				outfile << "error command��" << endl;
			}
		}
		//��ȡ������Ч��
		else {
			cout << endl;
			outfile << endl;
		}
	}

	cout << "end" << endl;    //������ɣ����end

}