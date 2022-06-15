#include "manager.h"

//Ĭ�Ϲ���
Manager::Manager()
{

}

//�вι���
Manager::Manager(string name, string pwd)
{
	m_Name = name;
	m_Pwd = pwd;

	//��ʼ����ʦ��ѧ������
	initVector();

	//��ʼ��ʵ��������
	initLabVector();
}

//�˵�����
void Manager::openMenu()
{
	cout << "��ӭ����Ա��" << m_Name << "��½" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "\t\t|  1.  ����˺�        |" << endl;
	cout << "\t\t|  2.  �鿴�˺�        |" << endl;
	cout << "\t\t|  3.  �鿴ʵ����        |" << endl;
	cout << "\t\t|  4.  ���ԤԼ        |" << endl;
	cout << "\t\t|  0.  ע����½        |" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "����������ѡ��:";
}

//����˺�
void Manager::addPerson()
{
	cout << "����������˺ŵ�����" << endl;
	cout << "1�����ѧ��" << endl;
	cout << "2�������ʦ" << endl;

	string fileName;//Ҫд�����˺ŵ��ļ�������ʦ��ѧ��
	string tip;//��ʾ����ѧ������ʦid���ַ���
	string errorTip;//��ʾѧ������ʦid�ظ����ַ���
	ofstream ofs;
	int select = 0;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			fileName = STUDENT_FILE;
			tip = "������ѧ��";
			errorTip = "ѧ���ظ�������������";
			break;
		}
		else if (select == 2)
		{
			fileName = TEACHER_FILE;
			tip = "������ְ�����";
			errorTip = "ְ�����ظ�������������";
			break;
		}
		else
		{
			cout << "��������ȷ��ѡ��"<< endl;
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
	cout << "����������" << endl;
	cin >> name;
	cout << "����������" << endl;
	cin >> pwd;

	ofs << id << " " << name << " " << pwd << endl;
	cout << "��ӳɹ�" << endl;
	initVector();
	system("pause");
	ofs.close();
}

//�鿴�˺�
void printStudent(Student s)
{
	cout << "ѧ�ţ�" << s.m_Id << "\t������" << s.m_Name << "\t���룺" << s.m_Pwd << endl;
}

void printTeacher(Teacher t)
{
	cout << "ְ���ţ�" << t.m_EmpId << "\t������" << t.m_Name << "\t���룺" << t.m_Pwd << endl;
}

void Manager::showPerson()
{
	cout << "��ѡ��鿴���ݣ�" << endl;
	cout << "1���鿴����ѧ��" << endl;
	cout << "2���鿴������ʦ" << endl;

	int select = 0;

	while (true)
	{
		cin >> select;
		if (select == 1)
		{
			cout << "����ѧ����Ϣ���£�" << endl;
			for_each(vStu.begin(), vStu.end(), printStudent);
			break;
		}
		else if (select == 2)
		{
			cout << "������ʦ��Ϣ���£�" << endl;
			for_each(vTea.begin(), vTea.end(), printTeacher);
			break;
		}
		else
		{
			cout << "��������ȷ��ѡ��" << endl;
		}
	}
	system("pause");
}

//�鿴ʵ������Ϣ
void Manager::showLab()
{
	cout << "ʵ������Ϣ���£�" << endl;
	for (vector<Lab>::iterator it = vLab.begin(); it != vLab.end(); it++)
	{
		cout << "ʵ���ұ�ţ�" << it->m_LabId << "\tʵ�������������" << it->m_MaxNum << endl;
	}
	system("pause");
}

//���ԤԼ��¼
void Manager::cleanFile()
{
	ofstream ofs(ORDER_FILE, ios::trunc);
	ofs.close();

	cout << "��ճɹ���" << endl;
	system("pause");
}

//��ʼ����ʦ��ѧ������
void Manager::initVector()
{
	//����ѧ������
	ifstream ifs;
	ifs.open(STUDENT_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	vStu.clear();
	
	Student s;
	while (ifs >> s.m_Id && ifs >> s.m_Name && ifs >> s.m_Pwd)
	{
		vStu.push_back(s);
	}
	ifs.close();
	
	//������ʦ����
	ifs.open(TEACHER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
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

//��ʼ��ʵ��������
void Manager::initLabVector()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
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

//����ظ�
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
