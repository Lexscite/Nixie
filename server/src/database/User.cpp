#include "User.h"

User::User()
{
}

User::~User()
{
}

int User::getId()
{
	return this->id;
}

User* User::create(std::string username, std::string password)
{
	User* newUser = new User;
	newUser->username = username;
	newUser->password = generatePasswordHash(password);

	return newUser;
}

void User::remove()
{
}

std::string User::generatePasswordHash(std::string password)
{
	//TODO: Hash realization

	return password;
}