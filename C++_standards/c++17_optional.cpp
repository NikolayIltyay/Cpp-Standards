#include "c++17_optional.h"
#include <optional>
#include <map>
#include <string>
#include <iostream>

std::map<int, std::string> idToName;

std::optional<std::string> getNameById(int id)
{
	if (idToName.contains(id))
		return idToName[id];
	else
		return {};
}

void Cpp_17_Optional::example()
{
	idToName[0] = "Bob";

	auto name = getNameById(0);
	
	if (name.has_value())
	{
		std::cout << "value is " << *name << std::endl;
	}

	name = getNameById(1);

	if (!name.has_value())
	{
		std::cout << "value is empty" << std::endl;
	}

}