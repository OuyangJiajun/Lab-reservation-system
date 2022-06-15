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
	//默认构造
	Student();

	//有参构造
	Student(int id,string name,string pwd);

	//菜单界面
	virtual void openMenu();

	//申请预约
	void applyOrder();

	//查看自身预约
	void showMyOrder();

	//查看所有预约
	void showAllOrder();

	//取消预约
	void cancelOrder();

	//初始化实验室容器
	void initLabVector();
	
	//学号
	int m_Id;

	//实验室信息
	vector<Lab> vLab;
};