#pragma once

//i节点
class Inode
{
	int fileType;				//文件类型
	int fileSize;				//文件大小
	int blockNumber;			//盘块数
	int indexType;				//混合索引分配方式 0 直接 1 一次 2 二次 3 三次
	int blocksIndex[10];		//直接块号addr[0]-addr[9]
	char permissions[9];		//权限
	char userName;				//创建者
	char userGroup;				//创建者所在组
	long createTime;			//创建时间
	long modifyTime;			//修改时间
public:
	Inode();

	static char * ToBuffer(Inode & inode);
	static Inode & ToINode(char * buffer);
	~Inode();
};

