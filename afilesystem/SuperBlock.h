#pragma once
struct SuperBlock
{
	//i�ڵ����
	int iNodeBlockNumber;

	//����i�ڵ���
	int freeInodeNumber;
	
	//����i�ڵ�ָ�����飬��ſ���i�ڵ�ŵ�һ������
	int freeInodes[512];

	//����i�ڵ�
	int lastInode;

	//���ݿ����
	int dataBlockNumber;

	//���п����
	int freeBlockNumber;

	//���п����
	int freeStackBlockNumber;

	//���п�ָ������
	short freeBlocks[50];

	//�������޸ı�־
	bool modifyFlag;

};

