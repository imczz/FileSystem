#include <fstream>

#include "FileSystem.h"


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
	superBlock.freeBlocks[0] = 0;
	superBlock.freeStackBlockNumber = 0;
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
	

	return 1;
}

int FileSystem::bfree(int blockindex)
{
	if (!IsInitalized) return 0;
	if (superBlock.freeStackBlockNumber == nicInode)
	{
		//wtire ��ջS  ����BlockNo�У�
		//S[0] = 1��
		//S[1] = BlockNo
	}
	else
	{
		//S[0] ++;
		//S[S[0]] = BlockNo;
	}
	return 0;
}

int FileSystem::format()
{
	if (!IsInitalized) return 0;


	return 1;
}
