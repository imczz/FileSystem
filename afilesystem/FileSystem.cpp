#include <fstream>
#include <ctime>

#include "FileSystem.h"
#include "BitOperate.h"
#include "FolderItem.h"

FileSystem::FileSystem()
{
	init();
}

FileSystem::FileSystem(string diskFile)
{
	init();
	this->diskFile = diskFile;
	
	ifstream file(diskFile, ios::in);

	if (file.is_open()) {
		IsInitalized = true;
		file.close();
		return;
	}
	else
	{
		int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;
		char * buffer = (char *)calloc(filesize, sizeof(char));
		if (buffer == NULL) return;						//分配内存空间失败
		ofstream file(diskFile, ios::out | ios::binary);
		if (file.is_open()) {
			file.write(buffer, filesize);					//操作成功
			IsInitalized = true;
			file.close();
		}
	}
	
}

int FileSystem::Initialize()
{
	if (IsInitalized) return 1;
	if (this->diskFile != "") 
	{
		Initialize(this->diskFile);
	}
	return 0;
}

int FileSystem::Initialize(string diskFile)
{
	if (IsInitalized) return 1;
	this->diskFile = diskFile;
	ifstream file(diskFile, ios::in);

	if (file.is_open()) {
		IsInitalized = true;
		file.close();
		ReadSuperBlock();
		for (int i = 0; i < 512; i++)
		{
			inodes[i] = getDiskInode(i);
		}
		return 1;
	}
	else
	{
		int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;
		char * buffer = (char *)calloc(filesize, sizeof(char));
		if (buffer == NULL) return 0;						//分配内存空间失败
		ofstream file(diskFile, ios::out | ios::binary);
		if (file.is_open()) {
			file.write(buffer, filesize);					//操作成功
			IsInitalized = true;
			file.close();
			WriteSuperBlock();
			return 1;
		}
	}
	return 0;
}

int FileSystem::WriteFileSystemDiskFile(string address)
{
	int result = 0;
	if (IsInitalized == false) return -1;				//文件系统未初始化

	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//分配内存空间失败
	for (int i = 0; i < 100; i++)
	{

	}
	ofstream file(address, ios::out | ios::binary );

	if (file.is_open()) {
		file.write(buffer, filesize);					//操作成功
		file.close();
		result = 1;
	}
	else
	{
		result =  -3;										//文件打开失败
	}
	free(buffer);
	return result;
}

int FileSystem::ReadFileSystemDiskFile(string address)
{
	int result = 0;
	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//分配内存空间失败
	ifstream file(address, ios::in | ios::binary);

	if (file.is_open()) {
		file.read(buffer, filesize);					//操作成功
		file.close();
		//char xyz = buffer[1];
		result = 1;
	}
	else
	{
		result = -3;										//文件打开失败
	}
	free(buffer);
	return result;
}

void FileSystem::init()
{
	blockSize = BLOCKSIZ;		//每块大小
	sysOpenFile = SYSOPENFILE;	//系统打开文件表最大项数
	dirNum = DIRNUM;			//每个目录所包含的最大目录项数（文件数）
	dirSize = DIRSIZ;		//每个目录项名字部分所占字节数，另加i节点号2个字节
	pwdSize = PWDSIZ;			//口令字
	pwdNum = PWDNUM;			//最多可设32个口令登录
	noFile = NOFILE;			//每个用户最多可打开20个文件，即用户打开文件最大次数
	nAddr = NADDR;			//每个i节点最多指向10块，addr[0]~addr[9]
	nHino = NHINO;			//共128个Hash链表，提供索引i节点（必须为2的幂）
	userNum = USERNUM;		//最多允许10个用户登录
	dInodeSize = DINODESIZ;		//每个磁盘i节点所占字节
	dInodeBLK = DINODEBLK;		//所有磁盘i节点共占32个物理块
	fileBLK = FILEBLK;		//共有512个目录文件物理块
	nicFree = NICFREE;		//超级块中空闲块数组的最大块数
	nicInode = NICINOD;		//超级块中空闲节点的最大块数
	dInodeStart = DINODESTART;	//i节点起始地址
	dataStart = DATASTART;		//目录、文件区起始地址

	IsInitalized = false;
}

int FileSystem::access(short id, char user, char group)
{
	if (!IsInitalized) return -1;
	int acc = 0;
	if (inodes[id].userName == user)
	{
		if (inodes[id].permissions[0] == true) acc |= 1;
		acc <<= 1;
		if (inodes[id].permissions[1] == true) acc |= 1;
		acc <<= 1;
		if (inodes[id].permissions[2] == true) acc |= 1;
	}
	else
	{
		if (inodes[id].userGroup = group)
		{
			if (inodes[id].permissions[3] == true) acc |= 1;
			acc <<= 1;
			if (inodes[id].permissions[4] == true) acc |= 1;
			acc <<= 1;
			if (inodes[id].permissions[5] == true) acc |= 1;
		}
		else
		{
			if (inodes[id].permissions[6] == true) acc |= 1;
			acc <<= 1;
			if (inodes[id].permissions[7] == true) acc |= 1;
			acc <<= 1;
			if (inodes[id].permissions[8] == true) acc |= 1;
		}
	}
	return acc;
}

int FileSystem::namei(short id, string name)
{
	if (!IsInitalized) return -1;
	if (inodes[id].state == false) return -2;
	if (inodes[id].fileType != 1) return -3;
	if (name.length() == 0) return -4;
	int folderNumber = iname(id);					//所有文件夹数
	int i, j, folderItemNumber;					//folderItemNumber 当前块中项数
	char blockBuffer[512];
	char foderItem[16];
	FolderItem aFolderItem;
	for (i = 0; i < inodes[id].blockNumber; i++)
	{
		ReadABlock(34 + inodes[id].blocksIndex[i], blockBuffer);
		if (folderNumber >= 32) folderItemNumber = 32;
		else folderItemNumber = folderNumber;
		for (j = 0; j < folderItemNumber; j++)
		{
			BitOperate::bitCopy(foderItem, 0, blockBuffer, j * 128, 128);
			aFolderItem.LoadFromBuffer(foderItem);
			if (aFolderItem.name == name)
			{
				return aFolderItem.inode;
			}
		}
	}
	return -1;
}

int FileSystem::iname(short id)
{
	if (!IsInitalized) return -1;
	if (inodes[id].state == false) return -2;
	if (inodes[id].fileType != 1) return -3;
	int size = inodes[id].fileSize;
	if (size < 0) return -4;
	return size / 16;
}

int FileSystem::balloc()
{
	if (!IsInitalized) return -1;
	int r;
	char buffer[512] = { 0 };
	if (superBlock.freeStackBlockNumber == 1)
	{
		if (superBlock.freeBlocks[0] == 0)  //分配失败，进程等待；
		{
			return -2;
		}
		else 
		{
			r = superBlock.freeBlocks[0];
			ReadABlock(this->dataStart + r, buffer);
			if(BufferToStack(buffer, superBlock.freeBlocks) < 0 ) return -2;
			//return r;
		}
	}
	else
	{
		r = superBlock.freeBlocks[superBlock.freeStackBlockNumber - 1];
		superBlock.freeStackBlockNumber--;
		//return r;
	}
	superBlock.freeBlockNumber--;
	return r;
}

int FileSystem::bfree(int blockindex)
{
	if (!IsInitalized) return -1;
	if (superBlock.freeStackBlockNumber == nicFree)
	{
		char buffer[512] = { 0 };
		if (StackToBuffer(superBlock.freeBlocks, buffer) < 0) return -2;
		if (WriteABlock(2 + this->dInodeBLK + blockindex, buffer) < 0) return -3;
		superBlock.freeStackBlockNumber = 1;
		superBlock.freeBlocks[0] = blockindex;
	}
	else
	{
		superBlock.freeBlocks[superBlock.freeStackBlockNumber] = blockindex;
		superBlock.freeStackBlockNumber++;
		
		//课程PPT上提供的方法是栈深51，S[0]是数量，而实验PPT超级快记录了空闲块个数，这样栈深是50
	}
	superBlock.freeBlockNumber++;
	return 1;
}

int FileSystem::format()
{
	if (!IsInitalized) return -1;
	int i;

	superBlock.dataBlockNumber = 512;
	superBlock.freeBlockNumber = 0;
	superBlock.freeBlocks[0] = 0;			//终止指针，指针终止
	superBlock.freeStackBlockNumber = 1;
	superBlock.freeInodeNumber = 0;
	for (int i = 0; i < superBlock.freeInodeNumber; i++)
	{
		superBlock.freeInodes[i] = i;
	}
	superBlock.iNodeBlockNumber = 32;
	superBlock.lastInode = superBlock.freeInodeNumber - 1;
	superBlock.modifyFlag = false;

	for (i = this->blockSize - 1; i >= 0; i--)
	{
		if (bfree(i) < 0)
		{
			;
		}
	}
	for (i = 0; i < 512; i++)
	{
		if (ifree(i) < 0)
		{
			;
		}
	}
	bool permissions[9];
	for (i = 0; i < 8; i++)
	{
		permissions[i] = true;
	}
	permissions[8] = false;
	/*
	short blockIndex[10];
	blockIndex[0] = balloc();
	for (i = 1; i < 10; i++)
	{
		blockIndex[i] = -1;
	}
	*/
	int rootIndex = ialloc();
	inodes[rootIndex].init(1, 1, 0, permissions, 'r', 'R', 0, time(0), NULL);
	refreshDiskInode(rootIndex);
	superBlock.lastInode = rootIndex;
	WriteSuperBlock();
	return 1;
}

int FileSystem::CreateFile(short id, char userName, char userGroup, string fileName)
{
	if (!IsInitalized) return -1;
	if (fileName == "") return -2;
	if (fileName.length() > 14 || fileName.length() < 0) return -3;
	int storeArea = iname(id);
	int thisBlock;				//（有可能）申请一个块
	int newInode;				//申请一个i节点
	int i;
	if (namei(id, fileName) != -1) return -10;			//重名文件
	if (storeArea % 32 == 0)						//没有分配快或者上一块用完了
	{
		thisBlock = balloc();
		if (thisBlock < 0) return -3;
		if (this->inodes[id].blockNumber == 9) return -4;			//一级链接装满了
		this->inodes[id].blocksIndex[this->inodes[id].blockNumber] = thisBlock;
		this->inodes[id].blockNumber++;
	}
	thisBlock = inodes[id].blocksIndex[this->inodes[id].blockNumber - 1];
	newInode = ialloc();
	if (newInode < 0) return -5;					//i节点用光了
	bool permissions[9];
	for (i = 0; i < 8; i++)
	{
		permissions[i] = true;
	}
	permissions[8] = false;
	inodes[newInode].init(1, 0, 0, permissions, userName, userGroup, 0, time(0), NULL);			//普通文件

	this->inodes[id].blocksIndex[this->inodes[id].blockNumber - 1];
	char blockBuffer[512];
	char folderItemBuffer[16];
	ReadABlock(34 + thisBlock, blockBuffer);
	FolderItem fitem(fileName, newInode);
	refreshDiskInode(newInode);
	FolderItem::FolderItemToBuffer(fitem, folderItemBuffer);
	BitOperate::bitCopy(blockBuffer, storeArea % 32 * 128, folderItemBuffer, 0, 128);

	WriteABlock(34 + thisBlock, blockBuffer);
	this->inodes[id].fileSize += 16;

	return 1;
}

int FileSystem::DeleteFile(short id, char userName, char userGroup, string fileName)
{
	if (!IsInitalized) return -1;
	if (inodes[id].state == false) return -2;
	inodes[id].state = false;					//改变标志位
	refreshDiskInode(id);
	return 1;
}

int FileSystem::read(short id, char userName, char userGroup, char * buffer)
{
	if (!IsInitalized) return -1;
	if (inodes[id].state == false) return -2;				//不存在的文件

	int storeArea = iname(id);
	int thisBlock;				//（有可能）申请一个块
	int newInode;				//申请一个i节点
	int i;
	//if (namei(id, folderName) != -1) return -10;						//重名文件
	if (storeArea % 32 == 0)						//没有分配快或者上一块用完了
	{
		thisBlock = balloc();
		if (thisBlock < 0) return -3;
		if (this->inodes[id].blockNumber == 9) return -4;			//一级链接装满了
		this->inodes[id].blocksIndex[this->inodes[id].blockNumber] = thisBlock;
		this->inodes[id].blockNumber++;
	}
	thisBlock = inodes[id].blocksIndex[this->inodes[id].blockNumber - 1];

	ReadABlock(thisBlock, buffer);

	return 1;
}

int FileSystem::write(short id, char userName, char userGroup, char * buffer)
{
	if (!IsInitalized) return -1;
	if (inodes[id].state == false) return -2;				//不存在的文件

	int storeArea = iname(id);
	int thisBlock;				//（有可能）申请一个块
	int newInode;				//申请一个i节点
	int i;
	//if (namei(id, folderName) != -1) return -10;						//重名文件
	if (storeArea % 32 == 0)						//没有分配快或者上一块用完了
	{
		thisBlock = balloc();
		if (thisBlock < 0) return -3;
		if (this->inodes[id].blockNumber == 9) return -4;			//一级链接装满了
		this->inodes[id].blocksIndex[this->inodes[id].blockNumber] = thisBlock;
		this->inodes[id].blockNumber++;
	}
	thisBlock = inodes[id].blocksIndex[this->inodes[id].blockNumber - 1];

	WriteABlock(thisBlock, buffer);

	return 1;
}



int FileSystem::ReadABlock(int blockNumber, char * buffer)
{
	if (buffer == NULL || !IsInitalized) return -1;
	ifstream file(diskFile, ios::in | ios::binary);

	if (file.is_open()) {
		file.seekg(blockNumber * this->blockSize, ios::beg);
		file.read(buffer, this->blockSize);					//操作成功
		file.close();
		return 1;
	}
	return -1;
}

int FileSystem::WriteABlock(int blockNumber, char * buffer)
{
	if (this->diskFile == "" || !IsInitalized || buffer == NULL) return -1;
	ofstream file(this->diskFile, ios::in | ios::binary | ios::ate);
	if (file.is_open()) {
		file.seekp(blockNumber * this->blockSize, ios::beg);
		file.write(buffer, this->blockSize);					//操作成功
		file.close();
		return 1;
	}
	return -1;
}

//整型转换为缓冲区
void IntToCharP(int nums, char * numc)
{
	int i;
	int n = nums;
	for (i = 0; i < 4; i++)
	{
		numc[3 - i] = n;
		n >>= 8;
	}
}

//缓冲区转换为整型
int CharPToInt(char * numc)
{
	int i;
	int n, nums;
	nums = 0;
	for (i = 0; i < 4; i++)
	{
		nums <<= 8;
		n = numc[i];
		if (n < 0) n += 256;			//避免转换时的变号
		nums |= n;
	}
	return nums;
}

int FileSystem::ReadSuperBlock()
{
	if (!IsInitalized) return -1;
	char buffer[512] = { 0 };
	char stackBuffer[512] = { 0 };
	char intBuffer[4];
	if (ReadABlock(1, buffer) < 0) return -2;				//读取失败

	BitOperate::bitCopy(intBuffer, 0, buffer, 0, 32);
	superBlock.iNodeBlockNumber = CharPToInt(intBuffer);

	BitOperate::bitCopy(intBuffer, 0, buffer, 32, 32);
	superBlock.freeInodeNumber = CharPToInt(intBuffer);

	BitOperate::bitCopy(intBuffer, 0, buffer, 64, 32);
	superBlock.lastInode = CharPToInt(intBuffer);

	BitOperate::bitCopy(intBuffer, 0, buffer, 96, 32);
	superBlock.dataBlockNumber = CharPToInt(intBuffer);

	BitOperate::bitCopy(intBuffer, 0, buffer, 128, 32);
	superBlock.freeBlockNumber = CharPToInt(intBuffer);

	BitOperate::bitCopy(intBuffer, 0, buffer, 160, 32);
	superBlock.freeStackBlockNumber = CharPToInt(intBuffer);

	BitOperate::bitCopy(intBuffer, 0, buffer, 192, 32);
	superBlock.modifyFlag = CharPToInt(intBuffer);

	BitOperate::bitCopy(stackBuffer, 0, buffer, 256, 816);
	BufferToStack(stackBuffer, superBlock.freeBlocks);

	return 1;
}

int FileSystem::WriteSuperBlock()
{
	if (!IsInitalized) return -1;
	char buffer[512] = { 0 };
	char stackBuffer[512] = { 0 };
	char intBuffer[4] = { 0 };

	IntToCharP(superBlock.iNodeBlockNumber, intBuffer);
	BitOperate::bitCopy(buffer, 0, intBuffer, 0, 32);

	IntToCharP(superBlock.freeInodeNumber, intBuffer);
	BitOperate::bitCopy(buffer, 32, intBuffer, 0, 32);
	
	IntToCharP(superBlock.lastInode, intBuffer);
	BitOperate::bitCopy(buffer, 64, intBuffer, 0, 32);
	
	IntToCharP(superBlock.dataBlockNumber, intBuffer);
	BitOperate::bitCopy(buffer, 96, intBuffer, 0, 32);
	
	IntToCharP(superBlock.freeBlockNumber, intBuffer);
	BitOperate::bitCopy(buffer, 128, intBuffer, 0, 32);
	
	IntToCharP(superBlock.freeStackBlockNumber,intBuffer);
	BitOperate::bitCopy(buffer, 160, intBuffer, 0, 32);
	
	IntToCharP(superBlock.modifyFlag, intBuffer);
	BitOperate::bitCopy(buffer, 192, intBuffer, 0, 32);
	
	StackToBuffer(superBlock.freeBlocks, stackBuffer);
	BitOperate::bitCopy(buffer, 256, stackBuffer, 0, 816);

	if (WriteABlock(1, buffer) < 0) return -2;				//写入失败
	return 1;
}

//存储在磁盘块中的空闲块栈转化成内存中的便于程序使用的数组（栈）
int FileSystem::BufferToStack(char * buffer, short * blockStack)
{
	int pointer = 2;			//一个指针
	int number = 0;
	number = buffer[0];
	number <<= 8;
	short tempshort = buffer[1];
	if (tempshort < 0) tempshort = -tempshort;
	number |= tempshort;
	//if (number != this->nicFree) return 0;
	for (int i = 0; i < this->nicFree; i++)
	{
		blockStack[i] = buffer[pointer];
		blockStack[i] <<= 8;
		tempshort = buffer[pointer + 1];
		if (tempshort < 0) tempshort = -tempshort;
		blockStack[i] |= tempshort;
		pointer += 2;
	}
	return 1;
}

//内存中的便于程序使用的数组（栈）转化成存储在磁盘块中的空闲块栈
int FileSystem::StackToBuffer(short * blockStack, char * buffer)
{
	if (blockStack == NULL || buffer == NULL) return 0;
	int pointer = 2;		//位置指针
	int number = this->nicFree;
	int i;
	buffer[0] = number >> 8;
	buffer[1] = number;
	for (i = 0; i < this->nicFree; i++)
	{
		buffer[pointer] = blockStack[i] >> 8;
		buffer[pointer + 1] = blockStack[i];
		pointer += 2;
	}
	for (i = pointer; i < this->blockSize; i++)
	{
		buffer[i] = 0;					//剩余部分填充0
	}
	return 1;
}

//获得一个可用的i节点
short FileSystem::ialloc()
{
	if (!IsInitalized) return -1;
	int result;
	int i;
	for (i = 0; i < 512; i++)
	{
		if (!this->inodes[i].state) break;
	}
	if (i >= 0 && i < 512)
	{
		this->inodes[i].init(false, 0, 0, NULL, '\0', '\0', 0, 0, NULL);
		refreshDiskInode(i);
		superBlock.freeInodeNumber--;
		superBlock.modifyFlag = true;
		WriteSuperBlock();
		superBlock.modifyFlag = false;
		return i;
	}
	return -2;			//没有可用的i节点
}

//释放一个曾经被使用的i节点
int FileSystem::ifree(short index)
{
	if (!IsInitalized) return -1;
	if (index < 0 || index >= 512) return -2;
	//if (this->inodes[index].state == false);					//格式化的情况下可能会强行释放，这里不做判断
	int i = index;
	this->inodes[index].state = false;
	this->inodes[i].init(false, 0, 0, NULL, '\0', '\0', 0, 0, NULL);
	refreshDiskInode(i);
	superBlock.freeInodeNumber++;
	superBlock.modifyFlag = true;
	WriteSuperBlock();
	superBlock.modifyFlag = false;
	return 1;
}

int FileSystem::refreshDiskInode(short index)
{
	if (!IsInitalized) return -1;
	if (index < 0 || index >= 512) return -2;
	char inodeBuffer[32] = { 0 };
	char blockBuffer[512] = { 0 };
	int i = index;
	Inode::CreateBufferFromInode(inodes[i], inodeBuffer);
	ReadABlock(2 + i / 16, blockBuffer);
	BitOperate::bitCopy(blockBuffer, i % 16 * 256, inodeBuffer, 0, 256);
	WriteABlock(2 + i / 16, blockBuffer);
	return 1;
}

Inode & FileSystem::getDiskInode(short index)
{
	Inode inode;
	char inodeBuffer[32] = { 0 };
	char blockBuffer[512] = { 0 };
	int i = index;
	ReadABlock(2 + i / 16, blockBuffer);
	BitOperate::bitCopy(inodeBuffer, 0, blockBuffer, i % 16 * 256, 256);
	inode.LoadInodeInBuffer(inodeBuffer);
	return inode;
}

int FileSystem::mkdir(short id, char userName, char userGroup, string folderName)
{
	if (this->inodes[id].state != true) return -1;				//空节点
	if (this->inodes[id].fileType != 1) return -2;				//只能在 文件夹 下创建 文件夹
	if (folderName.length() > 14 || folderName.length() < 0) return -3;
	int storeArea = iname(id);
	int thisBlock;				//（有可能）申请一个块
	int newInode;				//申请一个i节点
	int i;
	if (namei(id, folderName) != -1) return -10;						//重名文件
	if (storeArea % 32 == 0)						//没有分配快或者上一块用完了
	{
		thisBlock = balloc();
		if (thisBlock < 0) return -3;
		if (this->inodes[id].blockNumber == 9) return -4;			//一级链接装满了
		this->inodes[id].blocksIndex[this->inodes[id].blockNumber] = thisBlock;
		this->inodes[id].blockNumber++;
	}
	thisBlock = inodes[id].blocksIndex[this->inodes[id].blockNumber - 1];
	newInode = ialloc();
	if (newInode < 0) return -5;					//i节点用光了
	bool permissions[9];
	for (i = 0; i < 8; i++)
	{
		permissions[i] = true;
	}
	permissions[8] = false;
	inodes[newInode].init(1, 1, 0, permissions, userName, userGroup, 0, time(0), NULL);			//目录文件

	this->inodes[id].blocksIndex[this->inodes[id].blockNumber - 1];
	char blockBuffer[512];
	char folderItemBuffer[32];
	ReadABlock(34 + thisBlock, blockBuffer);
	FolderItem fitem(folderName, newInode);
	refreshDiskInode(newInode);
	FolderItem::FolderItemToBuffer(fitem, folderItemBuffer);
	BitOperate::bitCopy(blockBuffer, storeArea % 32 * 128, folderItemBuffer, 0, 128);

	WriteABlock(34 + thisBlock, blockBuffer);
	this->inodes[id].fileSize += 16;

	return 1;
}
