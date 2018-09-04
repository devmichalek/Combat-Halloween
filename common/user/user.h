#pragma once

namespace cmm
{
	class User
	{
	public:
		static char* username;
		static char* password;
		static char* getUsername() { return username; }
		static char* getPassword() { return password; }
	};
}