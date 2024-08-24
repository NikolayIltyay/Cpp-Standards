#include "c++17_execution_policy.h"
#include <algorithm>
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>

#define PARALLEL

#ifdef PARALLEL
#include <execution>
namespace execution = std::execution;
#else
enum class execution { seq, unseq, par_unseq, par };
#endif

decltype(auto) measure([[maybe_unused]] auto policy, std::vector<std::uint64_t> v)
{
    const auto start = std::chrono::steady_clock::now();
#ifdef PARALLEL
    std::sort(policy, v.begin(), v.end());
#else
    std::sort(v.begin(), v.end());
#endif
    const auto finish = std::chrono::steady_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(finish - start)
        << '\n';

    return v;
};


void Cpp_17_ExecutionPolicy::example()
{
    std::vector<std::uint64_t> v(1'000'000);
    std::mt19937 gen{ std::random_device{}() };
    std::ranges::generate(v, gen);

    auto resVec = measure(execution::par_unseq, v);
    measure(execution::par, v);
    measure(execution::seq, v);
    measure(execution::unseq, v);
}
