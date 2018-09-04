#include "state.h"

class A : public cmm::State
{
public:
	bool isReady() const { return true; }
};

class B : public cmm::State
{
public:
	bool isReady() const  { return true; }
};

int main(int argc, char** argv)
{
	A a;
	B b;

	return 0;
}