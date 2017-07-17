#pragma once

#include <string>

using namespace std;

class FolderItem
{
public:
	string name;
	short inode;

	short blockNumber;				//所在块
	int offset;						//偏移量

	FolderItem();
	FolderItem(string name, short inode);

	//复制构造函数
	FolderItem(const FolderItem & folderItem);

	void LoadFromBuffer(char * buffer);

	static int FolderItemToBuffer(FolderItem & item, char * buffer);

	~FolderItem();
};

