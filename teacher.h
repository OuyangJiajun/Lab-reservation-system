#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "identity.h"
#include "orderFile.h"
using namespace std;

class Teacher :public Identity
{
public:
	//默认构造
	Teacher();

	//有参构造
	Teacher(int empId, string name, string pwd);

	//菜单界面
	virtual void openMenu();

	//查看所有预约
	void showAllOrder();

	//审核预约
	void validOrder();

	//教师编号
	int m_EmpId;
};