/**************************************
 * ReadOptions.hpp
 * ��ȡ�����в����Ĳ���
 * Created on: May 3, 2019
 * Author: 盖聂
**************************************/

#pragma once
#include "DataStructure.hpp"

using namespace std;

//��ӡ������Ϣ
void help()
{
	cout << "ʹ�÷�����" << endl;
	cout << "    - ProcessResourceManege.exe" << endl;
	cout << "      ʹ��Ĭ�������ļ�input.txt������ļ�output.txt��" << endl;
	cout << "    - ProcessResourceManege.exe input.txt output.txt" << endl;
	cout << "      ����input.txtΪ�����ļ����ļ�����output.txtΪ����ļ����ļ�����" << endl;
	cout << "    - ProcessResourceManege.exe -h    ��ȡ������Ϣ\n" << endl;
}

//��ӡTestShell֧�ֵ�ָ��
void info()
{
	help();
	cout << "TestShell֧�ֵ�ָ�" << endl;
	cout << "    -init\t��ʼ��" << endl;
	cout << "    -cr <name> <priority>(= 1 or 2)  \t��������" << endl;
	cout << "    -de <name>                       \t��������" << endl;
	cout << "    -req <resource name> <# of units>\t������Դ" << endl;
	cout << "    -rel <resource name> <# of units>\t�ͷ���Դ" << endl;
	cout << "    -to                              \t��ʱ�ж�" << endl;
	cout << "    -lp                              \t�����б���״̬��Ϣ" << endl;
	cout << "    -lr                              \t��Դ�б���״̬��Ϣ" << endl;
	cout << "    -pi <name>                       \tָ�����̵���Ϣ\n" << endl;
}

//��ȡ�����в���
void readOptions(int argc, char *argv[])
{
	//��һ�������в�����-h
	if (argc == 2)
	{
		if (strcmp(argv[1], "-h") == 0)
		{
			info();
			exit(0);
		}
		else
		{
			cout << "��֧�ֵĲ���ѡ�" << argv[1] << "�����������룡" << endl;
			help();
			exit(0);
		}
	}
	//�����������в������ֱ�����������ļ�
	else if (argc == 3)
	{
		infile.open(argv[1]);
		outfile.open(argv[2], ios::out);
		//�ж��ļ��Ƿ�򿪳ɹ������û�д�˵��������ļ�������
		if (!infile.is_open()) {
			cout << "�����ļ�" << argv[1] << "�����ڣ������ļ����Ƿ���ȷ��" << endl;
			exit(0);
		}
	}
	//û�������в�����Ĭ����������ļ�
	else if (argc == 1)
	{
		infile.open("input.txt");
		outfile.open("output.txt", ios::out);
	}
	//�����������
	else
	{
		cout << "������������������������룡��ʹ��-hѡ���ȡ������Ϣ��" << endl;
		help();
		exit(0);
	}
}
