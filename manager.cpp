#include "manager.h"

//默认构造
Manager::Manager()
{

}

//有参构造
Manager::Manager(string name, string pwd)
{
	m_Name = name;
	m_Pwd = pwd;

	//初始化老师和学生容器
	initVector();

	//初始化实验室容器
	initLabVector();
}

//菜单界面
void Manager::openMenu()
{
	cout << "欢迎管理员：" << m_Name << "登陆" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "\t\t|  1.  添加账号        |" << endl;
	cout << "\t\t|  2.  查看账号        |" << endl;
	cout << "\t\t|  3.  查看实验室        |" << endl;
	cout << "\t\t|  4.  清空预约        |" << endl;
	cout << "\t\t|  0.  注销登陆        |" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "请输入您的选择:";
}

//添加账号
void Manager::addPerson()
{
	cout << "请输入添加账号的类型" << endl;
	cout << "1、添加学生" << endl;
	cout << "2、添加老师" << endl;

	string fileName;//要写入新账号的文件名，老师或学生
	string tip;//提示输入学生或老师id的字符串
	string errorTip;//提示学生或老师id重复的字符串
	ofstream ofs;
	int select = 0;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tip = "请输入学号";
			errorTip = "学号重复，请重新输入";
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "请输入职工编号";
			errorTip = "职工号重复，请重新输入";
			break;
		}
		else
		{
			cout << "请输入正确的选项"<< endl;
		}
	}

	ofs.open(fileName, ios::out | ios::app);

	int id;
	string name;
	string pwd;

	cout << tip << endl;
	while(true)
	{ 
		cin >> id;
		bool ret = checkRepeat(id, select);
		if (ret)
		{
			cout << errorTip << endl;
		}
		else
		{
			break;
		}
	}
	cout << "请输入姓名" << endl;
	cin >> name;
	cout << "请输入密码" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "添加成功" << endl;
	initVector();
	system("pause");
	ofs.close();
}

//查看账号
void printStudent(Student s)
{
	cout << "学号：" << s.m_Id << "\t姓名：" << s.m_Name << "\t密码：" << s.m_Pwd << endl;
}

void printTeacher(Teacher t)
{
	cout << "职工号：" << t.m_EmpId << "\t姓名：" << t.m_Name << "\t密码：" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	cout << "请选择查看内容：" << endl;
	cout << "1、查看所有学生" << endl;
	cout << "2、查看所有老师" << endl;

	int select = 0;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			cout << "所有学生信息如下：" << endl;
			for_each(vStu.begin(), vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "所有老师信息如下：" << endl;
			for_each(vTea.begin(), vTea.end(), printTeacher);
			break;
		}
		else
		{
			cout << "请输入正确的选项" << endl;
		}
	}
	system("pause");
}

//查看实验室信息
void Manager::showLab()
{
	cout << "实验室信息如下：" << endl;
	for (vector<Lab>::iterator it = vLab.begin(); it != vLab.end(); it++)
	{
		cout << "实验室编号：" << it->m_LabId << "\t实验室最大容量：" << it->m_MaxNum << endl;
	}
	system("pause");
}

//清空预约记录
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "清空成功！" << endl;
	system("pause");
}

//初始化老师和学生容器
void Manager::initVector()
{
	//读入学生数据
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	vStu.clear();
	
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();
	
	//读入老师数据
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "文件读取失败" << endl;
		return;
	}

	vTea.clear();

	Teacher t;
	while (ifs >> t.m_EmpId && ifs >> t.m_Name && ifs >> t.m_Pwd)
	{
		vTea.push_back(t);
	}
	ifs.close();
}

//初始化实验室容器
void Manager::initLabVector()
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

//检测重复
bool  Manager::checkRepeat(int id, int type)
{
	if (type == 1)
	{
		for (vector<Student>::iterator it = vStu.begin(); it != vStu.end(); it++)
		{
			if (it->m_Id == id)
			{
				return true;
			}
		}
	}
	else
	{
		for (vector<Teacher>::iterator it = vTea.begin(); it != vTea.end(); it++)
		{
			if (it->m_EmpId == id)
			{
				return true;
			}
		}
	}

	return false;
}
