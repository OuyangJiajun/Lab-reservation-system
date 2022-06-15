#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "globalFile.h"
#include "lab.h"
using namespace std;

class Manager :public Identity
{
public:
	//Ĭ�Ϲ���
	Manager();

	//�вι���
	Manager(string name, string pwd);

	//�˵�����
	virtual void openMenu();

	//����˺�
	void addPerson();

	//�鿴�˺�
	void showPerson();

	//�鿴ʵ������Ϣ
	void showLab();

	//���ԤԼ��¼
	void cleanFile();

	//��ʼ����ʦ��ѧ������
	void initVector();

	//��ʼ��ʵ��������
	void initLabVector();

	//����ظ�
	bool checkRepeat(int id, int type);

	//ѧ������
	vector<Student> vStu;

	//��ʦ����
	vector<Teacher> vTea;

	//ʵ������Ϣ
	vector<Lab> vLab;
};