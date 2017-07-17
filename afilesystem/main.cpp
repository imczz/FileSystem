#include <iostream>
#include <cstdlib>

using namespace std;

#include "OS.h"
#include "FileSystem.h"

int main()
{
	OS os;
	/*
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
	fs.CreateFile(2, 'h', 'E', "terminal.bin");
	fs.mkdir(2, 'i', 'F', "image");

	fs.DeleteFile(2, '2', 'k', "terminal.bin");

	char str[36] = "Hello world!in the file";
	char buffer[5120] = { 0 };
	int len;

	fs.write(11, 'x', 'y', 36, str);
	fs.read(11, 'z', 'p', len, buffer);

	cout << buffer << endl << "length :" << len << endl;;
	os.logout();
	*/
	os.start();

	system("pause");
	return 0;
}