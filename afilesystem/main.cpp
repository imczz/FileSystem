#include <iostream>
#include <cstdlib>

using namespace std;

#include "FileSystem.h"

int main()
{
	FileSystem fs;
	cout << fs.Initialize() << endl;
	cout << fs.Initialize("D:\\disk.txt") << endl;
	cout << fs.WriteFileSystemDiskFile("D:\\1.txt") << endl;
	cout << fs.ReadFileSystemDiskFile("D:\\1.txt") << endl;

	char buffer[512] = {0};
	buffer[510] = '0';
	buffer[511] = '0';
	for (int i = 0; i < 100; i++)
	{
		buffer[i] = 'A' + i % 26;
	}
	fs.WriteABlock(3, buffer);
	for (int i = 0; i < 100; i++)
	{
		buffer[i] = 'a' + i % 26;
	}
	fs.WriteABlock(2, buffer);
	cout << "Hello world!" << endl;
	system("pause");
	return 0;
}