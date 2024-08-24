#include "different_tests.h"
#include "additions.h"

additions::EmptyClassWithAllConstructors getObject()
{
	return additions::EmptyClassWithAllConstructors();
}

void DifferentTests::example()
{
	// 1
	auto object = getObject(); // only one default constructor will be called 
	//


}