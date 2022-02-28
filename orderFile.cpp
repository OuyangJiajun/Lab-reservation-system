#include "orderFile.h"

OrderFile::OrderFile()
{
	ifstream ifs;
	ifs.open(ORDER_FILE, ios::in);

	//暂存读取的信息
	string date;
	string interval;
	string stuId;
	string stuName;
	string roomId;
	string status;

	//把容器归零
	m_Size = 0;
	m_orderData.clear();

	while (ifs >> date && ifs >> interval && ifs >> stuId && ifs >> stuName && ifs >> roomId && ifs >> status)
	{
		/*测试
		cout << data << endl;
		cout << interval << endl;
		cout << stuId << endl;
		cout << stuName << endl;
		cout << roomId << endl;
		cout << status << endl;
		cout << endl;
		*/

		//要用的临时变量
		string key;
		string value;
		map<string, string> m;
		int pos;

		//放入data
		pos = date.find(':');
		if (pos != -1)
		{
			key = date.substr(0, pos);
			value = date.substr(pos + 1, date.size() - pos - 1);
			m.insert(pair<string, string>(key, value));
		}

		//放入interval
		pos = interval.find(':');
		if (pos != -1)
		{
			key = interval.substr(0, pos);
			value = interval.substr(pos + 1, interval.size() - pos - 1);
			m.insert(pair<string, string>(key, value));
		}

		//放入stuId
		pos = stuId.find(':');
		if (pos != -1)
		{
			key = stuId.substr(0, pos);
			value = stuId.substr(pos + 1, stuId.size() - pos - 1);
			m.insert(pair<string, string>(key, value));
		}

		//放入stuName
		pos = stuName.find(':');
		if (pos != -1)
		{
			key = stuName.substr(0, pos);
			value = stuName.substr(pos + 1, stuName.size() - pos - 1);
			m.insert(pair<string, string>(key, value));
		}

		//放入roomId
		pos = roomId.find(':');
		if (pos != -1)
		{
			key = roomId.substr(0, pos);
			value = roomId.substr(pos + 1, roomId.size() - pos - 1);
			m.insert(pair<string, string>(key, value));
		}

		//放入status
		pos = status.find(':');
		if (pos != -1)
		{
			key = status.substr(0, pos);
			value = status.substr(pos + 1, status.size() - pos - 1);
			m.insert(pair<string, string>(key, value));
		}

		//小map插入大map
		m_orderData[m_Size] = m;
		//记录条数+1
		m_Size++;
	}
	ifs.close();

	/*测试
	for (map<int, map<string, string>>::iterator it = m_orderData.begin(); it != m_orderData.end(); it++)
	{
		cout << "记录条数：" << it->first << "\t记录内容：" << endl;
		for (map<string, string>::iterator it2 = it->second.begin(); it2!=it->second.end(); it2++)
		{
			cout << "key=" << it2->first << "\tvalue=" << it2->second<< endl;
		}
		cout << endl;
	}
	*/
}

OrderFile::~OrderFile()
{
}

//更新预约记录
void OrderFile::updateOrder()
{
	if (m_Size == 0)
	{
		return;
	}

	ofstream ofs(ORDER_FILE, ios::out | ios::trunc);
	for (int i = 0; i < m_Size; i++)
	{
		ofs << "date:" << m_orderData[i]["date"] << "\tinterval:" << m_orderData[i]["interval"] << "\tstuId:" << m_orderData[i]["stuId"] << "\tstuName:" << m_orderData[i]["m_Name"] << "\troomId:" << m_orderData[i]["roomId"] << "\tstatus:" << m_orderData[i]["status"] << endl;
	}
	ofs.close();
}