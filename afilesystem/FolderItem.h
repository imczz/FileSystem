#pragma once

#include <string>

using namespace std;

class FolderItem
{
public:
	string name;
	short inode;

	short blockNumber;				//���ڿ�
	int offset;						//ƫ����

	FolderItem();
	FolderItem(string name, short inode);

	//���ƹ��캯��
	FolderItem(const FolderItem & folderItem);

	void LoadFromBuffer(char * buffer);

	static int FolderItemToBuffer(FolderItem & item, char * buffer);

	~FolderItem();
};

