#include "user.h"



User::User()
{
}

User::User(string & name, string & pass, string & group)
{
	this->username = name;
	this->password = pass;
	this->group = group;
}


User::~User()
{
}
