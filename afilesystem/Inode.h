#pragma once

//i�ڵ�
class Inode
{
	friend class FileSystem;
protected:
	bool state;					//״̬��true:used��false:empty						(1 bit)
	int fileType;				//�ļ�����		0 ��ͨ�ļ� 1 Ŀ¼�ļ� 2 �����ļ�	(2 bit)
	int blockNumber;			//�̿���											(4 bit)
	bool permissions[9];		//Ȩ��												(9 bit)
	//2 Byte

	char userName;				//������											(8 bit)
	char userGroup;				//������������										(8 bit)
	//2 Byte

	long fileSize;				//�ļ���С											(64 bit)
	//8 Byte
	long createTime;			//����ʱ��											(64 bit)
	//8 Byte

	short blocksIndex[10];		//ֱ�ӿ��addr[0]-addr[9]							(96 bit - 6 bit)
	//12 Byte

	//long modifyTime;			//�޸�ʱ��
public:
	Inode();
	Inode(bool state, int fileType, int blockNumber, bool * permissions, char userName, char userGroup, long fileSize, long createTime, short * blocksIndex);
	
	Inode(const Inode & inode);

	void init(bool state, int fileType, int blockNumber, bool * permissions, char userName, char userGroup, long fileSize, long createTime, short * blocksIndex);

	int LoadInodeInBuffer(char * buffer);			//char buffer[32]			
	static int CreateBufferFromInode(Inode & inode, char * buffer);		//�ⲿ��char buffer[32]

	~Inode();
};

