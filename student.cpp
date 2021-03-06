#include "student.h"
//无参构造
Student::Student()
{
	
}

//有参构造
Student::Student(int id, string name, string pwd)
{
	m_Id = id;
	m_Name = name;
	m_Pwd = pwd;

	//初始化实验室容器
	initLabVector();
}

//菜单界面
void Student::openMenu()
{
	cout << "欢迎学生：" << m_Name << "登陆" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "\t\t|  1.  申请预约        |" << endl;
	cout << "\t\t|  2.  查看我的预约    |" << endl;
	cout << "\t\t|  3.  查看所有预约    |" << endl;
	cout << "\t\t|  4.  取消预约        |" << endl;
	cout << "\t\t|  0.  注销登陆        |" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "请输入您的选择:";
}

//申请预约
void Student::applyOrder()
{
	int date = 0;//接收周一到周五
	int interval = 0;//接收上午或下午
	int room = 0;//接收实验室号

	cout << "实验室开放时间为周一至周五！" << endl;
	cout << "请输入申请预约的时间：" << endl;
	cout << "1、周一" << endl;
	cout << "2、周二" << endl;
	cout << "3、周三" << endl;
	cout << "4、周四" << endl;
	cout << "5、周五" << endl;
	while (true)
	{
		cin >> date;
		if (date == 1 || date == 2 || date == 3 || date == 4 || date == 5)
		{
			break;
		}
		else
		{
			cout << "请输入正确的选项" << endl;
		}
	}

	cout << "请输入申请预约的上午或下午：" << endl;
	cout << "1、上午" << endl;
	cout << "2、下午" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		else
		{
			cout << "请输入正确的选项" << endl;
		}
	}

	cout << "请输入申请预约的实验室：" << endl;
	for (int i = 0; i < vLab.size(); i++)
	{
		cout << vLab[i].m_LabId << "号实验室容量为：" << vLab[i].m_MaxNum << endl;
	}
	while (true)
	{
		cin >> room;
		if (room == 1 || room == 2 || room == 3)
		{
			break;
		}
		else
		{
			cout << "请输入正确的选项" << endl;
		}
	}
	
	cout << "预约成功，审核中" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE,ios::out| ios::app);
	ofs << "date:" << date << "\tinterval:" << interval << "\tstuId:" << m_Id << "\tstuName:" << m_Name << "\troomId:" << room << "\tstatus:" << 1 << endl;
	ofs.close();

	system("pause");
}

//查看自身预约
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		string str=of.m_orderData[i]["stuId"];
		if (str==to_string(m_Id))
		{
			cout << "预约日期：周" << of.m_orderData[i]["date"];
			cout << "\t时段：" << ((of.m_orderData[i]["interval"] == "1") ? "上午": "下午");
			cout << "\t实验室：" << of.m_orderData[i]["roomId"];
			string status = "\t状态：";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "审核中";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "预约成功";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "审核未通过，预约失败";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "预约已取消";
			}
			cout << status << endl;
		}
	}
	system("pause");
}

//查看所有预约
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "、";
		cout << "预约日期：周" << of.m_orderData[i]["date"];
		cout << "\t时段：" << ((of.m_orderData[i]["interval"] == "1") ? "上午" : "下午");
		cout << "\t学号：" << of.m_orderData[i]["stuId"];
		cout << "\t姓名：" << of.m_orderData[i]["stuName"];
		cout << "\t实验室：" << of.m_orderData[i]["roomId"];
		string status = "\t状态：";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "审核中";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "预约成功";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "审核未通过，预约失败";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status += "预约已取消";
		}
		cout << status << endl;
	}
	system("pause");
}

//取消预约
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "无预约记录" << endl;
		system("pause");
		return;
	}

	cout << "审核中或预约成功的记录可以取消，请输入取消的记录" << endl;

	vector<int> v;
	int index = 1;

	for (int i = 0; i < of.m_Size; i++)
	{
		string str = of.m_orderData[i]["stuId"];
		if (str == to_string(m_Id))
		{
			if (of.m_orderData[i]["status"] == "1" || of.m_orderData[i]["status"] == "2")
			{
				v.push_back(i);
				cout << index++ << "、";
				cout << "预约日期：周" << of.m_orderData[i]["date"];
				cout << "\t时段：" << ((of.m_orderData[i]["interval"] == "1") ? "上午" : "下午");
				cout << "\t实验室：" << of.m_orderData[i]["roomId"];
				string status = "\t状态：";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "审核中";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "预约成功";
				}
				else if (of.m_orderData[i]["status"] == "-1")
				{
					status += "审核未通过，预约失败";
				}
				else if (of.m_orderData[i]["status"] == "0")
				{
					status += "预约已取消";
				}
				cout << status << endl;
			}
		}
	}

	cout << "请输入取消的记录，0代表返回" << endl;
	int select = 0;
	while (true)
	{
		cin >> select;
		if (select >= 0 && select <= v.size())
		{
			if (select == 0)
			{
				break;
			}
			else
			{
				cout << "记录所在位置：" << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "已取消预约" << endl;
				break;
			}
		}
		cout << "输入有误，请重新输入" << endl;
	}
	system("pause");
}

//初始化实验室容器
void Student::initLabVector()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	vLab.clear();

	Lab c;
	while (ifs >> c.m_LabId && ifs >> c.m_MaxNum)
	{
		vLab.push_back(c);
	}
	ifs.close();
}