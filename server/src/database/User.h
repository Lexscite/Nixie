#ifndef USER_H
#define USER_H

#include <string>

class User
{
public:
	User();
	~User();

	int GetId();

	static User* Create(std::string username, std::string password);
	void Delete();

	static std::string GeneratePasswordHash(std::string password);

private:
	int id;
};

#endif // !USER_H
