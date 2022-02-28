#pragma once
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "globalFile.h"
using namespace std;

class OrderFile
{
public:
	OrderFile();
	~OrderFile();

	//更新预约记录
	void updateOrder();

	//记录预约条数
	int m_Size;

	//记录所有预约信息
	map<int, map<string,string>> m_orderData;
};

