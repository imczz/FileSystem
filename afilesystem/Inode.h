#pragma once

//i�ڵ�
class Inode
{
	int fileType;				//�ļ�����
	int fileSize;				//�ļ���С
	int blockNumber;			//�̿���
	int indexType;				//����������䷽ʽ 0 ֱ�� 1 һ�� 2 ���� 3 ����
	int blocksIndex[10];		//ֱ�ӿ��addr[0]-addr[9]
	char permissions[9];		//Ȩ��
	char userName;				//������
	char userGroup;				//������������
	long createTime;			//����ʱ��
	long modifyTime;			//�޸�ʱ��
public:
	Inode();

	static char * ToBuffer(Inode & inode);
	static Inode & ToINode(char * buffer);
	~Inode();
};

