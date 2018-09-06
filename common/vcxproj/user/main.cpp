#include "user.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	printf("Username: %s\nPassword: %s\n", cmm::User::getUsername().c_str(), cmm::User::getPassword().c_str());

	std::cout << "Press Enter to Continue...\n";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	return 0;
}