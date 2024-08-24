#include "c++17_structured_bindings.h"
#include <utility>
#include <string>
#include <map>
#include <iostream>

auto getCoord() ->std::pair<int, int>
{
	return { 0,0 };
}



void Cpp_17_StructuredBindings::example()
{
	// a and b are const int&& becauce of referencing to a temporary object
	const auto [a, b] = getCoord();

	std::map<std::string, int> name_to_id{
		{"name0", 0},
		{"name1", 1},
		{"name2", 2},
	};

	for (const auto& [key, value] : name_to_id)
	{
		std::cout << key << " -> " << value << std::endl;
	}

}