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

#include "SuperBlock.h"

using namespace std;

class FileSystem
{
	string diskFile;
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
	int nicInode;		//�������п���i�ڵ��������
	int dInodeStart;	//i�ڵ���ʼ��ַ
	int dataStart;		//Ŀ¼���ļ�����ʼ��ַ

	SuperBlock superBlock;

	//��ʼ������
	void init();
public:
	//���캯���������δ����ʼ�����޷�ʹ��
	FileSystem();

	//���Գ�ʼ���Ĺ��캯��
	FileSystem(string diskFile);

	//��ʼ���ļ�ϵͳ��û�е�ַ���ʼ��ʧ�ܣ����ɹ�����1��ʧ�ܷ���0
	int Initialize();

	//���Ի�һ���ļ�ϵͳ�ļ����ҳ��Գ�ʼ�����ɹ�����1��ʧ�ܷ���0
	int Initialize(string diskFile);

	//���ļ�ϵͳд�뵽�ļ���
	int WriteFileSystemDiskFile(string address);

	//���ļ�ϵͳ���ļ��ж�ȡ
	int ReadFileSystemDiskFile(string address);

	//�����ļ�ϵͳ�ļ�disk.txt
	int CreateDiskFile(string address);

	//��һ����
	int ReadABlock(int blockNumber, char * buffer);

	//дһ����
	int WriteABlock(int blockNumber, char * buffer);

	int BufferToStack(char * buffer, int * blockStack);

	int StackToBuffer(int * blockStack, char * buffer);

	//����i�ڵ�ķ���
	int ialloc();

	//����i�ڵ�Ļ���
	int ifree();

	//�ڴ�i�ڵ��ȡ
	int iget();

	//�ڴ�i�ڵ��ͷ�
	int iput();

	//�ж��û����ļ�����ĳ�����Է���Ȩ��
	int access();

	//ʵ�ֶ��ļ��Ĵ�ȡ��������������·����ת������Ҫ�������ļ����ڴ�i���ָ�루��Ŀ¼�����е�λ�ã�
	int namei();

	//�ڵ�ǰĿ¼��������һ���յ�Ŀ¼���飬�Ա㽨���µ�Ŀ¼���ļ�ʱʹ��
	int iname();

	//���п�ķ���
	int balloc();

	//index��Ļ���
	int bfree(int blockindex);

	//�ļ�ϵͳ��ʽ��
	int format();

	//�ļ���
	int open();

	//�ļ��ر�
	int close();

	//�ļ�����
	int CreateFile();

	//�ļ�ɾ��
	int DeleteFile();

	//��ȡ�ļ�
	int read();

	//д���ļ�
	int write();

	//����Ŀ¼
	int mkdir();

	//�ı䵱ǰĿ¼
	int chdir();

	//�г��ļ�Ŀ¼
	int dir();
};