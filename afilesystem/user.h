#pragma once

#include <string>

using namespace std;

class User
{
	//用户名
	string username;
	
	//用户密码
	string password;

	//用户组
	string group;
public:
	//构造函数
	User();

	//另一个构造函数
	User(string & name, string &  pass, string &  group);



	//析构函数
	~User();
};

