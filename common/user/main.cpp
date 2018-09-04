#include "user.h"
#include <stdio.h>

int main(int argc, char** argv)
{
	printf("Username: %s\nPassword: %s\n", cmm::User::getUsername(), cmm::User::getPassword());
	return 0;
}