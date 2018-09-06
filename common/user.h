#pragma once
#include <string>

namespace cmm
{
	class User
	{
	public:
		static std::string username;
		static std::string password;
		static std::string getUsername() { return username; }
		static std::string getPassword() { return password; }
		static void setUsername(std::string newUsername) { username = newUsername; }
		static void setPassword(std::string newPassword) { password = newPassword; }
	};
}