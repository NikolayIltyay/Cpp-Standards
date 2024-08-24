#include "c++11_tuple.h"
#include <tuple>
#include <string>

decltype(auto) getPersonInfo()
{
	return std::make_tuple("Name", "Second Name", 190, "Eductation");
}

void Cpp_11_Tuple::example()
{
	std::string name;
	std::string secondName;
	int height{0};
	std::string education;

	std::tie(name, secondName, height, education) = getPersonInfo();

	std::string onlyEducation;
	std::tie(std::ignore, std::ignore, std::ignore, onlyEducation) = getPersonInfo();
}