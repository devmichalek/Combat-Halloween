#include "user.h"
#include "converter.h"
#include <stdio.h>
#include <iostream>

int main(int argc, char** argv)
{
	printf("Username: %s%sPassword: %s%s", cmm::User::getUsername().c_str(), cmm::CSNEWLINE, cmm::User::getPassword().c_str(), cmm::CSNEWLINE);

	std::cout << "Press Enter to Continue..." << std::endl;
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), cmm::CNEWLINE);

	return 0;
}