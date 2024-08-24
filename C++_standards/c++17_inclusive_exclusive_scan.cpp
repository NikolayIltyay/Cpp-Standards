#include "c++17_inclusive_exclusive_scan.h"
#include <iostream>
#include <vector>
#include <numeric>
#include <array>

void Cpp_17_InclusiveExclusiveScan::example()
{
	{
        std::vector<int> vec = { 1, 2, 3, 4, 5 };
        std::vector<int> result(vec.size());

        std::inclusive_scan(vec.begin(), vec.end(), result.begin());

        for (int n : result) {
            std::cout << n << " ";
        }
        // Output: 1 3 6 10 15
	}

    {
        std::vector<int> vec = { 1, 2, 3, 4, 5 };
        std::vector<int> result(vec.size());

        std::exclusive_scan(vec.begin(), vec.end(), result.begin(), 0);

        for (int n : result) {
            std::cout << n << " ";
        }
        // Output: 0 1 3 6 10
    }

    {
        const std::array<int, 3> a{ 1, 2, 3 };

        const auto times_ten = [](const auto n) { return n * 10; };

        std::transform_inclusive_scan(std::cbegin(a), std::cend(a),
            std::ostream_iterator<int>{ std::cout, " " }, std::plus<>{}, times_ten); // 10 30 60

        std::transform_exclusive_scan(std::cbegin(a), std::cend(a),
            std::ostream_iterator<int>{ std::cout, " " }, 0, std::plus<>{}, times_ten); // 0 10 30
    }
}
