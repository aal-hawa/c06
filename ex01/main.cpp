#include <iostream>
#include "Serializer.hpp"

int main()
{
	Data original;
	original.name = "Ali";
	original.age = 42;

	uintptr_t raw = Serializer::serialize(&original);
	Data* result = Serializer::deserialize(raw);

	std::cout << "Original Data Address: " << &original << std::endl;
	std::cout << "Deserialized Address: " << result << std::endl;
	std::cout << "Name: " << result->name << ", Age: " << result->age << std::endl;

	if (result == &original)
		std::cout << " Success: Same memory address!" << std::endl;
	else
		std::cout << " Failure: Different memory address!" << std::endl;

	return 0;
}