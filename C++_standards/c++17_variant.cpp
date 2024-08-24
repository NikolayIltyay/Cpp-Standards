#include "c++17_variant.h"
#include <variant>
#include <string>
#include <iostream>
#include <cassert>

void Cpp_17_Variant::example()
{
	std::variant<float, int, double, std::string> v0;

    v0 = "Hello";

	auto value = std::get<std::string>(v0);

    try
    {
        std::get<float>(v0); // w contains int, not float: will throw
    }
    catch (const std::bad_variant_access& ex)
    {
        std::cout << ex.what() << '\n';
    }

    using namespace std::literals;

    // void const* is prefered in value type deduction than std::string 
    std::variant<std::string, void const*> v1("abc");
    // casts to void const * when passed a char const *
    assert(std::holds_alternative<void const*>(v1)); // succeeds
    v1 = "xyz"s;
    assert(std::holds_alternative<std::string>(v1)); // succeeds


    // Directly specifying that value type must be std::string
    std::variant<std::string, void const*> v2(std::in_place_type<std::string>, "abc");
    std::visit([](auto&& arg) {
        using T = std::decay_t<decltype(arg)>;

        if constexpr (std::is_same_v<T, std::string>) {
            std::cout << "std::string: " << arg << std::endl;
        }
        else if constexpr (std::is_same_v<T, void const*>) {
            std::cout << "void const*: " << arg << std::endl;
        }
    }, v2);


}