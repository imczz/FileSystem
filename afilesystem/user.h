#pragma once

#include <string>

using namespace std;

class user
{
	//�û���
	string username;
	
	//�û�����
	string password;

	//�û���
	string group;
public:
	//���캯��
	user();

	//��һ�����캯��
	user(string & name, string &  pass, string &  group);



	//��������
	~user();
};

