#include <fstream>

#include "FileSystem.h"


FileSystem::FileSystem()
{
	IsInitalized = false;
	init();
}

int FileSystem::WriteFileSystemDiskFile(string address)
{
	int result = 0;
	if (IsInitalized == false) return -1;				//�ļ�ϵͳδ��ʼ��

	int filesize = (2 + this->dInodeBLK + this->fileBLK) * this->blockSize;

	char * buffer = (char *)calloc(filesize, sizeof(char));
	if (buffer == NULL) return -2;						//�����ڴ�ռ�ʧ��
	buffer[1] = 'D';
	buffer[2] = 'K';
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
		char xyz = buffer[1];
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
	IsInitalized = true;
}
