#include "c++20_jthread.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <stop_token>
#include <vector>
#include <future>
#include "additions.h"



void threadFunction(std::stop_token stoken, int id) {
    while (!stoken.stop_requested()) {
        // Perform some work
        additions::ThreadSafeCout::print("Thread ", id, " is running...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    additions::ThreadSafeCout::print("Thread ", id, " is stopping...\n");
}

void asyncFunction(std::stop_token stoken, int id) {
    std::stop_callback stopCallback(stoken, [id]() {
        additions::ThreadSafeCout::print("Async task ", " received stop request.\n");
    });

    while (!stoken.stop_requested()) {
        // Perform some work
        additions::ThreadSafeCout::print("Async task ", " is running...\n");
        std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
    additions::ThreadSafeCout::print("Async task ", " is stopping...\n");
}



void Cpp_20_JThread::example()
{
    // using jthread
    {
        const int numThreads = 3;
        std::vector<std::jthread> threads;

        // Create multiple jthreads
        for (int i = 0; i < numThreads; ++i) {
            threads.emplace_back(threadFunction, i);
        }

        // Allow the threads to run for a while
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Request all threads to stop
        for (auto& t : threads) {
            t.request_stop();
        }

        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Join all threads (automatic for std::jthread)
        // No need to explicitly join as std::jthread handles it

        additions::ThreadSafeCout::print("Main thread finished.\n");
    }

    // using std::stop_source with std::aync
    {
        // Create a stop_source
        std::stop_source stopSource;

        // Launch async tasks with the stop_token
        std::vector<std::future<void>> futures;
        for (int i = 0; i < 3; ++i) {
            futures.push_back(std::async(std::launch::async, asyncFunction, stopSource.get_token(), i));
        }

        // Allow the tasks to run for a while
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Request all tasks to stop
        stopSource.request_stop();

        // Wait for all tasks to complete
        for (auto& f : futures) {
            f.get();
        }

        additions::ThreadSafeCout::print("Main thread finished.\n");
    }
}
