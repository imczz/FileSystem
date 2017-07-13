#include <cstdlib>

#include "Inode.h"



Inode::Inode()
{
}


char * Inode::ToBuffer(Inode & inode)
{
	char * result = (char *)calloc(32, sizeof(char));
	if (result == NULL) return NULL;
	//result[0] |= (char)7;
	return result;
}

Inode & Inode::ToINode(char * buffer)
{
	Inode inode;

	return inode;
}

Inode::~Inode()
{
}
