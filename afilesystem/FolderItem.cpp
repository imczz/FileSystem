#include "FolderItem.h"
#include "BitOperate.h"


FolderItem::FolderItem()
{
	name = "";
	inode = -1;
}

FolderItem::FolderItem(string name, short inode)
{
	this->name = name;
	this->inode = inode;
}

void FolderItem::LoadFromBuffer(char * buffer)
{
	char fname[16] = { 0 };
	int i;
	for (i = 0; i < 14; i++)
	{
		fname[i] = buffer[i];
		if (buffer[i] == 0) break;
	}
	this->name = string(fname);
	inode = 0;
	inode |= buffer[14];
	inode <<= 8;
	short tempShort;
	tempShort = buffer[15];
	if (tempShort < 0) tempShort = !tempShort;
	inode |= tempShort;
}

int FolderItem::FolderItemToBuffer(FolderItem & item, char * buffer)
{
	FolderItem fitem;
	if (item.name == "") return -1;
	char fname[16] = { 0 };
	int i;
	for (i = 0; i < item.name.length() && i < 14; i++)
	{
		fname[i] = item.name[i];
	}
	char inode[2];
	inode[1] = item.inode;
	inode[0] = item.inode >> 8;
	BitOperate::bitCopy(buffer, 0, fname, 0, 112);
	BitOperate::bitCopy(buffer, 112, inode, 0, 16);
	return 1;
}


FolderItem::~FolderItem()
{
}
