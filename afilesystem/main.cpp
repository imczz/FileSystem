#include <iostream>
#include <cstdlib>

using namespace std;

#include "OS.h"
#include "FileSystem.h"

int main()
{
	OS os;
	string username;
	string password;
	UN user;
	cout << "请输入用户名:" <<endl;
	cin >> username;
	cout << "请输入密码:" << endl;
	cin >> password;
	if (username == "root")
	{
		user = user0;
	}
	else
	{
		if (username.size() == 5 && username.substr(0, 4) == "user")
		{
			switch (username[4])
			{
			case '1':
				user = user1;
				break;
			case '2':
				user = user2;
				break;
			case '3':
				user = user3;
				break;
			case '4':
				user = user4;
				break;
			case '5':
				user = user5;
				break;
			case '6':
				user = user6;
				break;
			case '7':
				user = user7;
				break;
			case '8':
				user = user8;
				break;
			}
		}
		else
		{
			user = unknown;
		}
	}
	if (os.login(user, password) != 200)
	{
		system("pause");
		exit(0);
	}
	FileSystem fs;
	cout << fs.Initialize() << endl;
	cout << fs.Initialize("D:\\disk.txt") << endl;
	cout << fs.WriteFileSystemDiskFile("D:\\1.txt") << endl;
	cout << fs.ReadFileSystemDiskFile("D:\\1.txt") << endl;

	fs.format();
	fs.mkdir(0, 'a', 'A', "user");
	fs.mkdir(0, 'c', 'C', "bin");
	fs.CreateFile(0, 'b', 'B', "1.txt");

	fs.mkdir(1, 'd', 'D', "user0");
	fs.mkdir(1, 'e', 'D', "user1");
	fs.mkdir(1, 'f', 'D', "user2");
	fs.mkdir(1, 'g', 'D', "user3");
	fs.mkdir(1, 'h', 'D', "user4");

	fs.CreateFile(2, 'h', 'E', "sh.bin");
	fs.CreateFile(2, 'h', 'E', "grub.bin");
	fs.CreateFile(2, 'h', 'E', "run.bin");
	fs.CreateFile(2, 'h', 'E', "terminal.bin");
	fs.mkdir(2, 'i', 'F', "image");

	cout << "Hello world!" << endl;
	os.logout();
	system("pause");
	return 0;
}