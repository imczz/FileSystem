#include <iostream>
#include <cstdlib>

using namespace std;

#include "FileSystem.h"

int main()
{
	FileSystem fs;
	cout << fs.WriteFileSystemDiskFile("D:\\1.txt") << endl;
	cout << fs.ReadFileSystemDiskFile("D:\\1.txt") << endl;
	cout << "Hello world!" << endl;
	system("pause");
	return 0;
}