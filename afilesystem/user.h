#pragma once

#include <string>

using namespace std;

class User
{
	//�û���
	string username;
	
	//�û�����
	string password;

	//�û���
	string group;
public:
	//���캯��
	User();

	//��һ�����캯��
	User(string & name, string &  pass, string &  group);



	//��������
	~User();
};

