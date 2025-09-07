#include "Identify.hpp"
#include <iostream>

int main ()
{
	std::srand(std::time(0));
	Base* ptr = generate();
	std::cout << "Identify by pointer: ";
	identify(ptr);

	std::cout << "Identify by reference: ";
	identify(*ptr);

	delete ptr;
	return 0;
}