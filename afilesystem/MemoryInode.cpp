#include "MemoryInode.h"


int MemoryInode::Open()
{
	referencedCount++;
	return 0;
}

int MemoryInode::Close()
{
	referencedCount--;
	return 0;
}

MemoryInode::MemoryInode()
{
	referencedCount = 0;
}


MemoryInode::~MemoryInode()
{

}
