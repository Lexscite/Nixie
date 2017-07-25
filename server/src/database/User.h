#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	User();
	~User();

	int getId();

	static User* create(std::string username, std::string password);
	void remove();

	static std::string generatePasswordHash(std::string password);

public:
	int id;
	std::string username;
	std::string password;
};

#endif // !USER_H
