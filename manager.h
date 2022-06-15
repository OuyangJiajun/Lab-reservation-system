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
	//默认构造
	Manager();

	//有参构造
	Manager(string name, string pwd);

	//菜单界面
	virtual void openMenu();

	//添加账号
	void addPerson();

	//查看账号
	void showPerson();

	//查看实验室信息
	void showLab();

	//清空预约记录
	void cleanFile();

	//初始化老师和学生容器
	void initVector();

	//初始化实验室容器
	void initLabVector();

	//检测重复
	bool checkRepeat(int id, int type);

	//学生容器
	vector<Student> vStu;

	//教师容器
	vector<Teacher> vTea;

	//实验室信息
	vector<Lab> vLab;
};