#include <iostream>
#include <string>
#include <fstream>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
using namespace std;

//进入管理员子菜单界面
void managerMenu(Identity*& manager)//指针引用形式，delete后，该指针=NULL即原指针=NULL，不会变为野指针
{
	//将父类指针转为子类指针，才能调用子类特有函数
	Manager* man = (Manager*)manager;

	int select = 0;

	while(true)
	{ 
		system("cls");

		//先显示管理员菜单，属于父类的纯虚函数，在子类中各自实现
		manager->openMenu();

		cin >> select;

		switch (select)
		{
		case 1://添加账号
			man->addPerson();
			break;
		case 2://查看账号
			man->showPerson();
			break;
		case 3://查看实验室
			man->showLab();
			break;
		case 4://清空预约
			man->cleanFile();
			break;
		case 0://注销登陆
			delete manager;
			manager = NULL;
			cout << "注销成功" << endl;
			system("pause");
			return;
		default:
			cout << "请输入正确的选项" << endl;
		}
	}
}

void studentMenu(Identity*& student)
{
	//将父类指针转为子类指针，才能调用子类特有函数
	Student* stu = (Student*)student;

	int select = 0;

	while (true)
	{
		system("cls");

		//先显示管理员菜单，属于父类的纯虚函数，在子类中各自实现
		stu->openMenu();

		cin >> select;

		switch (select)
		{
		case 1://申请预约
			stu->applyOrder();
			break;
		case 2://查看自身预约
			stu->showMyOrder();
			break;
		case 3://查看所有预约
			stu->showAllOrder();
			break;
		case 4://取消预约
			stu->cancelOrder();
			break;
		case 0://注销登陆
			delete student;
			student = NULL;
			cout << "注销成功" << endl;
			system("pause");
			return;
		default:
			cout << "请输入正确的选项" << endl;
		}
	}
}

void teacherMenu(Identity*& teacher)
{
	//将父类指针转为子类指针，才能调用子类特有函数
	Teacher* tea = (Teacher*)teacher;

	int select = 0;

	while (true)
	{
		system("cls");

		//先显示管理员菜单，属于父类的纯虚函数，在子类中各自实现
		tea->openMenu();

		cin >> select;

		switch (select)
		{
		case 1://查看所有预约
			tea->showAllOrder();
			break;
		case 2://审核预约
			tea->validOrder();
			break;
		case 0://注销登陆
			delete teacher;
			teacher = NULL;
			cout << "注销成功" << endl;
			system("pause");
			return;
		default:
			cout << "请输入正确的选项" << endl;
		}
	}
}

//实现不同身份登录
void loginIn(string fileName, int type)//1代表学生,2代表老师,3代表管理员
{
	Identity* person=NULL;//父类指针,用于指向子类对象

	//先判断文件是否存在,要比对账号密码
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件不存在" << endl;
		ifs.close();
		return;
	}

	//接收用户信息
	int id = 0;
	string name;
	string pwd;

	//学生和老师还要编号
	if (type == 1)
	{
		cout << "请输入学号" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "请输入教师编号" << endl;
		cin >> id;
	}

	//全部都要用户名和密码
	cout << "请输入姓名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> pwd;

	//验证
	string fName;//放读入的名字
	string fPwd;//放读入的密码
	if(type==1 || type==2)
	{ 
		int fId;//放读入的id
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				ifs.close();
				cout << "验证登录成功！" << endl;
				system("pause");
				if (type == 1)
				{
					person = new Student(id, name, pwd);
					studentMenu(person);
				}
				else
				{
					person = new Teacher(id, name, pwd);
					teacherMenu(person);
				}
				return;
			}
		}
	}
	else
	{
		while (ifs >> fName && ifs >> fPwd)
		{
			if (fName == name && fPwd == pwd)
			{
				ifs.close();
				cout << "验证登录成功！" << endl;
				system("pause");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "验证登录失败" << endl;
	system("pause");
}

int main()
{
	int select = 0;
	while (true)
	{
		system("cls");
		cout << "请输入您的身份" << endl;
		cout << "\t\t------------------------" << endl;
		cout << "\t\t|  1.  学生代表        |" << endl;
		cout << "\t\t|  2.  老    师        |" << endl;
		cout << "\t\t|  3.  管 理 员        |" << endl;
		cout << "\t\t|  0.  退    出        |" << endl;
		cout << "\t\t------------------------" << endl;
		cout << "请输入您的选择:";

		cin >> select;//输入字母会陷入死循环

		if (select != 0 && select != 1 && select != 2 && select != 3) continue;//解决死循环的问题

		switch (select)
		{
		case 1:
			loginIn(STUDENT_FILE, 1);
			break;
		case 2:
			loginIn(TEACHER_FILE, 2);
			break;
		case 3:
			loginIn(ADMIN_FILE, 3);
			break;
		case 0:
			cout << "欢迎下次使用!" << endl;
			system("pause");
			return 0;
		default:
			cout << "输入有误,请重新选择!" << endl;
			system("pause");
			break;
		}
	}
}