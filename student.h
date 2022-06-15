#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "identity.h"
#include "lab.h"
#include "globalFile.h"
#include "orderFile.h"
using namespace std;

class Student :public Identity
{
public:
	//Ĭ�Ϲ���
	Student();

	//�вι���
	Student(int id,string name,string pwd);

	//�˵�����
	virtual void openMenu();

	//����ԤԼ
	void applyOrder();

	//�鿴����ԤԼ
	void showMyOrder();

	//�鿴����ԤԼ
	void showAllOrder();

	//ȡ��ԤԼ
	void cancelOrder();

	//��ʼ��ʵ��������
	void initLabVector();
	
	//ѧ��
	int m_Id;

	//ʵ������Ϣ
	vector<Lab> vLab;
};