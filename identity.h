#pragma once
#include <iostream>
using namespace std;

//��ݳ������
class Identity
{
public:
	//��ʾ��Ӧ�Ĳ����˵�,���麯��������������ʵ��
	virtual void openMenu()=0;

	//�û���
	string m_Name;
	//����
	string m_Pwd;
};