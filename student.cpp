#include "student.h"
//�޲ι���
Student::Student()
{
	
}

//�вι���
Student::Student(int id, string name, string pwd)
{
	m_Id = id;
	m_Name = name;
	m_Pwd = pwd;

	//��ʼ����������
	initComVector();
}

//�˵�����
void Student::openMenu()
{
	cout << "��ӭѧ����" << m_Name << "��½" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "\t\t|  1.  ����ԤԼ        |" << endl;
	cout << "\t\t|  2.  �鿴�ҵ�ԤԼ    |" << endl;
	cout << "\t\t|  3.  �鿴����ԤԼ    |" << endl;
	cout << "\t\t|  4.  ȡ��ԤԼ        |" << endl;
	cout << "\t\t|  0.  ע����½        |" << endl;
	cout << "\t\t------------------------" << endl;
	cout << "����������ѡ��:";
}

//����ԤԼ
void Student::applyOrder()
{
	int date = 0;//������һ������
	int interval = 0;//�������������
	int room = 0;//���ջ�����

	cout << "��������ʱ��Ϊ��һ�����壡" << endl;
	cout << "����������ԤԼ��ʱ�䣺" << endl;
	cout << "1����һ" << endl;
	cout << "2���ܶ�" << endl;
	cout << "3������" << endl;
	cout << "4������" << endl;
	cout << "5������" << endl;
	while (true)
	{
		cin >> date;
		if (date == 1 || date == 2 || date == 3 || date == 4 || date == 5)
		{
			break;
		}
		else
		{
			cout << "��������ȷ��ѡ��" << endl;
		}
	}

	cout << "����������ԤԼ����������磺" << endl;
	cout << "1������" << endl;
	cout << "2������" << endl;
	while (true)
	{
		cin >> interval;
		if (interval == 1 || interval == 2)
		{
			break;
		}
		else
		{
			cout << "��������ȷ��ѡ��" << endl;
		}
	}

	cout << "����������ԤԼ�Ļ�����" << endl;
	for (int i = 0; i < vCom.size(); i++)
	{
		cout << vCom[i].m_ComId << "�Ż�������Ϊ��" << vCom[i].m_MaxNum << endl;
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
			cout << "��������ȷ��ѡ��" << endl;
		}
	}
	
	cout << "ԤԼ�ɹ��������" << endl;

	ofstream ofs;
	ofs.open(ORDER_FILE,ios::out| ios::app);
	ofs << "date:" << date << "\tinterval:" << interval << "\tstuId:" << m_Id << "\tstuName:" << m_Name << "\troomId:" << room << "\tstatus:" << 1 << endl;
	ofs.close();

	system("pause");
}

//�鿴����ԤԼ
void Student::showMyOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		string str=of.m_orderData[i]["stuId"];
		if (str==to_string(m_Id))
		{
			cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
			cout << "\tʱ�Σ�" << ((of.m_orderData[i]["interval"] == "1") ? "����": "����");
			cout << "\t������" << of.m_orderData[i]["roomId"];
			string status = "\t״̬��";
			if (of.m_orderData[i]["status"] == "1")
			{
				status += "�����";
			}
			else if (of.m_orderData[i]["status"] == "2")
			{
				status += "ԤԼ�ɹ�";
			}
			else if (of.m_orderData[i]["status"] == "-1")
			{
				status += "���δͨ����ԤԼʧ��";
			}
			else if (of.m_orderData[i]["status"] == "0")
			{
				status += "ԤԼ��ȡ��";
			}
			cout << status << endl;
		}
	}
	system("pause");
}

//�鿴����ԤԼ
void Student::showAllOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		return;
	}
	for (int i = 0; i < of.m_Size; i++)
	{
		cout << i + 1 << "��";
		cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
		cout << "\tʱ�Σ�" << ((of.m_orderData[i]["interval"] == "1") ? "����" : "����");
		cout << "\tѧ�ţ�" << of.m_orderData[i]["stuId"];
		cout << "\t������" << of.m_orderData[i]["stuName"];
		cout << "\t������" << of.m_orderData[i]["roomId"];
		string status = "\t״̬��";
		if (of.m_orderData[i]["status"] == "1")
		{
			status += "�����";
		}
		else if (of.m_orderData[i]["status"] == "2")
		{
			status += "ԤԼ�ɹ�";
		}
		else if (of.m_orderData[i]["status"] == "-1")
		{
			status += "���δͨ����ԤԼʧ��";
		}
		else if (of.m_orderData[i]["status"] == "0")
		{
			status += "ԤԼ��ȡ��";
		}
		cout << status << endl;
	}
	system("pause");
}

//ȡ��ԤԼ
void Student::cancelOrder()
{
	OrderFile of;
	if (of.m_Size == 0)
	{
		cout << "��ԤԼ��¼" << endl;
		system("pause");
		return;
	}

	cout << "����л�ԤԼ�ɹ��ļ�¼����ȡ����������ȡ���ļ�¼" << endl;

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
				cout << index++ << "��";
				cout << "ԤԼ���ڣ���" << of.m_orderData[i]["date"];
				cout << "\tʱ�Σ�" << ((of.m_orderData[i]["interval"] == "1") ? "����" : "����");
				cout << "\t������" << of.m_orderData[i]["roomId"];
				string status = "\t״̬��";
				if (of.m_orderData[i]["status"] == "1")
				{
					status += "�����";
				}
				else if (of.m_orderData[i]["status"] == "2")
				{
					status += "ԤԼ�ɹ�";
				}
				else if (of.m_orderData[i]["status"] == "-1")
				{
					status += "���δͨ����ԤԼʧ��";
				}
				else if (of.m_orderData[i]["status"] == "0")
				{
					status += "ԤԼ��ȡ��";
				}
				cout << status << endl;
			}
		}
	}

	cout << "������ȡ���ļ�¼��0������" << endl;
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
				cout << "��¼����λ�ã�" << v[select - 1] << endl;
				of.m_orderData[v[select - 1]]["status"] = "0";
				of.updateOrder();
				cout << "��ȡ��ԤԼ" << endl;
				break;
			}
		}
		cout << "������������������" << endl;
	}
	system("pause");
}

//��ʼ����������
void Student::initComVector()
{
	ifstream ifs;
	ifs.open(COMPUTER_FILE, ios::in);
	if (!ifs.is_open())
	{
		cout << "�ļ���ȡʧ��" << endl;
		return;
	}

	vCom.clear();

	ComputerRoom c;
	while (ifs >> c.m_ComId && ifs >> c.m_MaxNum)
	{
		vCom.push_back(c);
	}
	ifs.close();
}