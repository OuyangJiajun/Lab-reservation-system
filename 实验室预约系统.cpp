#include <iostream>
#include <string>
#include <fstream>
#include "identity.h"
#include "student.h"
#include "teacher.h"
#include "manager.h"
#include "globalFile.h"
using namespace std;

//�������Ա�Ӳ˵�����
void managerMenu(Identity*& manager)//ָ��������ʽ��delete�󣬸�ָ��=NULL��ԭָ��=NULL�������ΪҰָ��
{
	//������ָ��תΪ����ָ�룬���ܵ����������к���
	Manager* man = (Manager*)manager;

	int select = 0;

	while(true)
	{ 
		system("cls");

		//����ʾ����Ա�˵������ڸ���Ĵ��麯�����������и���ʵ��
		manager->openMenu();

		cin >> select;

		switch (select)
		{
		case 1://����˺�
			man->addPerson();
			break;
		case 2://�鿴�˺�
			man->showPerson();
			break;
		case 3://�鿴ʵ����
			man->showLab();
			break;
		case 4://���ԤԼ
			man->cleanFile();
			break;
		case 0://ע����½
			delete manager;
			manager = NULL;
			cout << "ע���ɹ�" << endl;
			system("pause");
			return;
		default:
			cout << "��������ȷ��ѡ��" << endl;
		}
	}
}

void studentMenu(Identity*& student)
{
	//������ָ��תΪ����ָ�룬���ܵ����������к���
	Student* stu = (Student*)student;

	int select = 0;

	while (true)
	{
		system("cls");

		//����ʾ����Ա�˵������ڸ���Ĵ��麯�����������и���ʵ��
		stu->openMenu();

		cin >> select;

		switch (select)
		{
		case 1://����ԤԼ
			stu->applyOrder();
			break;
		case 2://�鿴����ԤԼ
			stu->showMyOrder();
			break;
		case 3://�鿴����ԤԼ
			stu->showAllOrder();
			break;
		case 4://ȡ��ԤԼ
			stu->cancelOrder();
			break;
		case 0://ע����½
			delete student;
			student = NULL;
			cout << "ע���ɹ�" << endl;
			system("pause");
			return;
		default:
			cout << "��������ȷ��ѡ��" << endl;
		}
	}
}

void teacherMenu(Identity*& teacher)
{
	//������ָ��תΪ����ָ�룬���ܵ����������к���
	Teacher* tea = (Teacher*)teacher;

	int select = 0;

	while (true)
	{
		system("cls");

		//����ʾ����Ա�˵������ڸ���Ĵ��麯�����������и���ʵ��
		tea->openMenu();

		cin >> select;

		switch (select)
		{
		case 1://�鿴����ԤԼ
			tea->showAllOrder();
			break;
		case 2://���ԤԼ
			tea->validOrder();
			break;
		case 0://ע����½
			delete teacher;
			teacher = NULL;
			cout << "ע���ɹ�" << endl;
			system("pause");
			return;
		default:
			cout << "��������ȷ��ѡ��" << endl;
		}
	}
}

//ʵ�ֲ�ͬ��ݵ�¼
void loginIn(string fileName, int type)//1����ѧ��,2������ʦ,3�������Ա
{
	Identity* person=NULL;//����ָ��,����ָ���������

	//���ж��ļ��Ƿ����,Ҫ�ȶ��˺�����
	ifstream ifs;
	ifs.open(fileName, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}

	//�����û���Ϣ
	int id = 0;
	string name;
	string pwd;

	//ѧ������ʦ��Ҫ���
	if (type == 1)
	{
		cout << "������ѧ��" << endl;
		cin >> id;
	}
	else if (type == 2)
	{
		cout << "�������ʦ���" << endl;
		cin >> id;
	}

	//ȫ����Ҫ�û���������
	cout << "����������" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> pwd;

	//��֤
	string fName;//�Ŷ��������
	string fPwd;//�Ŷ��������
	if(type==1 || type==2)
	{ 
		int fId;//�Ŷ����id
		while (ifs >> fId && ifs >> fName && ifs >> fPwd)
		{
			if (fId == id && fName == name && fPwd == pwd)
			{
				ifs.close();
				cout << "��֤��¼�ɹ���" << endl;
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
				cout << "��֤��¼�ɹ���" << endl;
				system("pause");
				person = new Manager(name, pwd);
				managerMenu(person);
				return;
			}
		}
	}
	cout << "��֤��¼ʧ��" << endl;
	system("pause");
}

int main()
{
	int select = 0;
	while (true)
	{
		system("cls");
		cout << "�������������" << endl;
		cout << "\t\t------------------------" << endl;
		cout << "\t\t|  1.  ѧ������        |" << endl;
		cout << "\t\t|  2.  ��    ʦ        |" << endl;
		cout << "\t\t|  3.  �� �� Ա        |" << endl;
		cout << "\t\t|  0.  ��    ��        |" << endl;
		cout << "\t\t------------------------" << endl;
		cout << "����������ѡ��:";

		cin >> select;//������ĸ��������ѭ��

		if (select != 0 && select != 1 && select != 2 && select != 3) continue;//�����ѭ��������

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
			cout << "��ӭ�´�ʹ��!" << endl;
			system("pause");
			return 0;
		default:
			cout << "��������,������ѡ��!" << endl;
			system("pause");
			break;
		}
	}
}