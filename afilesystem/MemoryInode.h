#pragma once

#include "Inode.h"

class MemoryInode : public Inode
{
	friend class OS;
public:
	int referencedCount;					//引用计数

	int Open();

	int Close();

	MemoryInode();
	~MemoryInode();
};

