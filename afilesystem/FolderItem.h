#pragma once

#include <string>

using namespace std;

class FolderItem
{
public:
	string name;
	short inode;

	FolderItem();
	FolderItem(string name, short inode);

	void LoadFromBuffer(char * buffer);

	static int FolderItemToBuffer(FolderItem & item, char * buffer);

	~FolderItem();
};

