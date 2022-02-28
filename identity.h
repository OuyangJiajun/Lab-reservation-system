#pragma once
#include <iostream>
using namespace std;

//身份抽象基类
class Identity
{
public:
	//显示对应的操作菜单,纯虚函数由子类做各自实现
	virtual void openMenu()=0;

	//用户名
	string m_Name;
	//密码
	string m_Pwd;
};