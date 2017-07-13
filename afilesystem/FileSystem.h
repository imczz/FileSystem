#pragma once

#define BLOCKSIZ 512
#define SYSOPENFILE 40
#define DIRNUM 128
#define DIRSIZ 14
#define PWDSIZ 12
#define PWDNUM 32
#define NOFILE 20
#define NADDR 10
#define NHINO 128
#define USERNUM 10
#define DINODESIZ 32
#define DINODEBLK 32
#define FILEBLK 512
#define NICFREE 50
#define NICINOD 50
#define DINODESTART 2*BLOCKSIZ
#define DATASTART (2+DINODEBLK)*BLOCKSIZ

#include <string>

using namespace std;

class FileSystem
{
	int type;

	bool IsInitalized;				//������ʼ��

	int blockSize;		//ÿ���С
	int sysOpenFile;	//ϵͳ���ļ����������
	int dirNum;			//ÿ��Ŀ¼�����������Ŀ¼�������ļ�����
	int dirSize;		//ÿ��Ŀ¼�����ֲ�����ռ�ֽ��������i�ڵ��2���ֽ�
	int pwdSize;		//������
	int pwdNum;			//������32�������¼
	int noFile;			//ÿ���û����ɴ�20���ļ������û����ļ�������
	int nAddr;			//ÿ��i�ڵ����ָ��10�飬addr[0]~addr[9]
	int nHino;			//��128��Hash�����ṩ����i�ڵ㣨����Ϊ2���ݣ�
	int userNum;		//�������10���û���¼
	int dInodeSize;		//ÿ������i�ڵ���ռ�ֽ�
	int dInodeBLK;		//���д���i�ڵ㹲ռ32�������
	int fileBLK;		//����512��Ŀ¼�ļ������
	int nicFree;		//�������п��п������������
	int nicInode;		//�������п��нڵ��������
	int dInodeStart;	//i�ڵ���ʼ��ַ
	int dataStart;		//Ŀ¼���ļ�����ʼ��ַ

	
public:
	FileSystem();

	void init();
	int WriteFileSystemDiskFile(string address);
	int ReadFileSystemDiskFile(string address);
};