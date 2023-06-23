/**************************************
 * main.cpp
 * ������
 * Created on: May 3, 2019
 * Author: 盖聂
**************************************/
 
#include "ProcessResourceManage.hpp"
#include "ReadOptions.hpp"
#include "TestShell.hpp"

using namespace std;

//����������ļ�
ifstream infile;
ofstream outfile;

int main(int argc, char *argv[]) {
	readOptions(argc, argv);    //��ȡ�����в���������������ļ�

	testShell();    //����testShell����ִ���ļ��е�����

	//�رմ򿪵��ļ����˳�����
	infile.close();
	outfile.close();
	system("pause");
	return 0;
}