#pragma once

#include "Inode.h"

class MemoryInode : public Inode
{
	friend class OS;
public:
	int referencedCount;					//���ü���

	int Open();

	int Close();

	MemoryInode();
	~MemoryInode();
};

