#include "additions.h"
#include <iostream>

namespace additions
{
	decltype(auto) summ(int a, int b)
	{
		return a + b;
	}

	EmptyClassWithAllConstructors::EmptyClassWithAllConstructors()
	{
		std::cout << "Default Contructor" << std::endl;
	}

	EmptyClassWithAllConstructors::EmptyClassWithAllConstructors(const EmptyClassWithAllConstructors& other)
	{
		std::cout << "CopyConstructor" << std::endl;
	}

	EmptyClassWithAllConstructors::EmptyClassWithAllConstructors(EmptyClassWithAllConstructors&& other)
	{
		std::cout << "MoveConstructor" << std::endl;
	}

	EmptyClassWithAllConstructors::~EmptyClassWithAllConstructors()
	{
		std::cout << "Desctructor" << std::endl;
	}
}