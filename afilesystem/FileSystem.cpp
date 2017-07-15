#include <fstream>
#include <ctime>

#include "FileSystem.h"
#include "BitOperate.h"

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
		if (buffer == NULL) return;						//�����ڴ�ռ�ʧ��
		ofstream file(diskFile, ios::out | ios::binary);
		if (file.is_open()) {
			file.write(buffer, filesize);					//�����ɹ�
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
		return 1;
	}
	else
	{
		int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;
		char * buffer = (char *)calloc(filesize, sizeof(char));
		if (buffer == NULL) return 0;						//�����ڴ�ռ�ʧ��
		ofstream file(diskFile, ios::out | ios::binary);
		if (file.is_open()) {
			file.write(buffer, filesize);					//�����ɹ�
			IsInitalized = true;
			file.close();
			return 1;
		}
	}
	return 0;
}

int FileSystem::WriteFileSystemDiskFile(string address)
{
	int result = 0;
	if (IsInitalized == false) return -1;				//�ļ�ϵͳδ��ʼ��

	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//�����ڴ�ռ�ʧ��
	for (int i = 0; i < 100; i++)
	{

	}
	ofstream file(address, ios::out | ios::binary );

	if (file.is_open()) {
		file.write(buffer, filesize);					//�����ɹ�
		file.close();
		result = 1;
	}
	else
	{
		result =  -3;										//�ļ���ʧ��
	}
	free(buffer);
	return result;
}

int FileSystem::ReadFileSystemDiskFile(string address)
{
	int result = 0;
	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//�����ڴ�ռ�ʧ��
	ifstream file(address, ios::in | ios::binary);

	if (file.is_open()) {
		file.read(buffer, filesize);					//�����ɹ�
		file.close();
		//char xyz = buffer[1];
		result = 1;
	}
	else
	{
		result = -3;										//�ļ���ʧ��
	}
	free(buffer);
	return result;
}

void FileSystem::init()
{
	blockSize = BLOCKSIZ;		//ÿ���С
	sysOpenFile = SYSOPENFILE;	//ϵͳ���ļ����������
	dirNum = DIRNUM;			//ÿ��Ŀ¼�����������Ŀ¼�������ļ�����
	dirSize = DIRSIZ;		//ÿ��Ŀ¼�����ֲ�����ռ�ֽ��������i�ڵ��2���ֽ�
	pwdSize = PWDSIZ;			//������
	pwdNum = PWDNUM;			//������32�������¼
	noFile = NOFILE;			//ÿ���û����ɴ�20���ļ������û����ļ�������
	nAddr = NADDR;			//ÿ��i�ڵ����ָ��10�飬addr[0]~addr[9]
	nHino = NHINO;			//��128��Hash�����ṩ����i�ڵ㣨����Ϊ2���ݣ�
	userNum = USERNUM;		//�������10���û���¼
	dInodeSize = DINODESIZ;		//ÿ������i�ڵ���ռ�ֽ�
	dInodeBLK = DINODEBLK;		//���д���i�ڵ㹲ռ32�������
	fileBLK = FILEBLK;		//����512��Ŀ¼�ļ������
	nicFree = NICFREE;		//�������п��п������������
	nicInode = NICINOD;		//�������п��нڵ��������
	dInodeStart = DINODESTART;	//i�ڵ���ʼ��ַ
	dataStart = DATASTART;		//Ŀ¼���ļ�����ʼ��ַ

	superBlock.dataBlockNumber = 512;
	superBlock.freeBlockNumber = 0;
	superBlock.freeBlocks[0] = 0;			//��ָֹ�룬ָ����ֹ
	superBlock.freeStackBlockNumber = 1;
	superBlock.freeInodeNumber = 512;
	for (int i = 0; i < superBlock.freeInodeNumber; i++)
	{
		superBlock.freeInodes[i] = i;
	}
	superBlock.iNodeBlockNumber = 32;
	superBlock.lastInode = superBlock.freeInodeNumber - 1;
	superBlock.modifyFlag = false;

	IsInitalized = false;
}

int FileSystem::balloc()
{
	if (!IsInitalized) return -1;
	int r;
	char buffer[512] = { 0 };
	if (superBlock.freeStackBlockNumber == 1)
	{
		if (superBlock.freeBlocks[0] == 0)  //����ʧ�ܣ����̵ȴ���
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
		
		//�γ�PPT���ṩ�ķ�����ջ��51��S[0]����������ʵ��PPT�������¼�˿��п����������ջ����50
	}
	superBlock.freeBlockNumber++;
	return 1;
}

int FileSystem::format()
{
	if (!IsInitalized) return -1;
	int i;
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
	short blockIndex[10];
	blockIndex[0] = balloc();
	for (i = 1; i < 10; i++)
	{
		blockIndex[i] = -1;
	}
	int rootIndex = ialloc();
	inodes[rootIndex].init(1, 1, 1, permissions, 'r', 'R', 0, time(0), blockIndex);
	refreshInode(rootIndex);
	return 1;
}



int FileSystem::ReadABlock(int blockNumber, char * buffer)
{
	if (buffer == NULL || !IsInitalized) return -1;
	ifstream file(diskFile, ios::in | ios::binary);

	if (file.is_open()) {
		file.seekg(blockNumber * this->blockSize, ios::beg);
		file.read(buffer, this->blockSize);					//�����ɹ�
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
		file.write(buffer, this->blockSize);					//�����ɹ�
		file.close();
		return 1;
	}
	return -1;
}

//�洢�ڴ��̿��еĿ��п�ջת�����ڴ��еı��ڳ���ʹ�õ����飨ջ��
int FileSystem::BufferToStack(char * buffer, short * blockStack)
{
	int pointer = 2;			//һ��ָ��
	int number = 0;
	number = buffer[0];
	number <<= 8;
	short tempshort = buffer[1];
	if (tempshort < 0) tempshort = -tempshort;
	number |= tempshort;
	if (number != this->nicFree) return 0;
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

//�ڴ��еı��ڳ���ʹ�õ����飨ջ��ת���ɴ洢�ڴ��̿��еĿ��п�ջ
int FileSystem::StackToBuffer(short * blockStack, char * buffer)
{
	if (blockStack == NULL || buffer == NULL) return 0;
	int pointer = 2;		//λ��ָ��
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
		buffer[i] = 0;					//ʣ�ಿ�����0
	}
	return 1;
}

int FileSystem::ialloc()
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
		refreshInode(i);
		return i;
	}
	return -2;			//û�п��õ�i�ڵ�
}

int FileSystem::ifree(int index)
{
	if (!IsInitalized) return -1;
	if (index < 0 || index >= 512) return -2;
	//if (this->inodes[index].state == false);					//��ʽ��������¿��ܻ�ǿ���ͷţ����ﲻ���ж�
	int i = index;
	this->inodes[index].state = false;
	this->inodes[i].init(false, 0, 0, NULL, '\0', '\0', 0, 0, NULL);
	refreshInode(i);
	return 1;
}

int FileSystem::refreshInode(int index)
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

