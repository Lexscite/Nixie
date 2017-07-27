#include "User.h"

User::User()
{
}

User::~User()
{
}

int User::GetId()
{
	return this->id;
}

User* User::Create(std::string username, std::string password)
{
	User* newUser = new User;

	return newUser;
}

void User::Delete()
{
}

std::string User::GeneratePasswordHash(std::string password)
{
	return password;
}