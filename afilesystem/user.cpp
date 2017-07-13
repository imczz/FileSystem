#include "user.h"



user::user()
{
}

user::user(string & name, string & pass, string & group)
{
	this->username = name;
	this->password = pass;
	this->group = group;
}


user::~user()
{
}
