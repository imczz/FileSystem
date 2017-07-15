#pragma once

#include <string>
#include <iostream>

using namespace std;

const enum UN { user0, user1, user2, user3, user4, user5, user6, user7, user8, unknown };

class OS
{
public:



	/* -1：无登陆

	0：管理员

	1，2，3，4，5，6，7，8：用户1-8

	*/

	int user = -1;





	//登入

	int login(UN id, string key);



	//登出

	void logout();



	//打开文件

	void open(string fileName);



	//关闭文件

	void close(string fileName);



	//创建文件

	void create(string fileName);



	//读文件

	void read(string fileName);



	//写文件

	void write(string fileName);


	//创建目录

	void mkdir();



	//改变当前目录

	void chdir();


	//列出文件目录

	void dir();


	//格式化

	void format();

};

