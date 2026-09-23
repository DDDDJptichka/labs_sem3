#include <iostream>
#include <chrono>
#include <memory>

#include "includes/SharedPtr.hpp"
#include "includes/UniquePtr.hpp"


int main(){

    size_t sizes[] = {1000, 10000, 100000, 1000000};

    std::cout << "\n========== UNIQUE PTR ==========\n\n";

    for (size_t n : sizes){

        auto start_raw = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; ++i){

            int* ptr = new int(i);

            delete ptr;

        }

        auto end_raw = std::chrono::high_resolution_clock::now();
        auto time_raw = std::chrono::duration_cast<std::chrono::microseconds>(end_raw - start_raw).count();


        auto start_my = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; ++i){

            UniquePtr<int> ptr(new int(i));

        }

        auto end_my = std::chrono::high_resolution_clock::now();
        auto time_my = std::chrono::duration_cast<std::chrono::microseconds>(end_my - start_my).count();


        auto start_std = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; ++i){

            std::unique_ptr<int> ptr(new int(i));

        }

        auto end_std = std::chrono::high_resolution_clock::now();
        auto time_std = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();

        std::cout << "N = " << n << '\n';
        std::cout << "Raw:             " << time_raw << " us\n";
        std::cout << "MyUnique:        " << time_my << " us\n";
        std::cout << "std::unique_ptr: " << time_std << " us\n";
        std::cout << '\n';

    }


    std::cout << "\n========== SHARED PTR ==========\n\n";

    for (size_t n : sizes){

        auto start_raw = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; ++i){

            int* ptr = new int(i);

            delete ptr;

        }

        auto end_raw = std::chrono::high_resolution_clock::now();
        auto time_raw = std::chrono::duration_cast<std::chrono::microseconds>(end_raw - start_raw).count();


        auto start_my = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; ++i){

            SharedPtr<int> ptr(new int(i));

        }

        auto end_my = std::chrono::high_resolution_clock::now();
        auto time_my = std::chrono::duration_cast<std::chrono::microseconds>(end_my - start_my).count();


        auto start_std = std::chrono::high_resolution_clock::now();

        for (size_t i = 0; i < n; ++i){

            std::shared_ptr<int> ptr(new int(i));

        }

        auto end_std = std::chrono::high_resolution_clock::now();
        auto time_std = std::chrono::duration_cast<std::chrono::microseconds>(end_std - start_std).count();

        std::cout << "N = " << n << '\n';
        std::cout << "Raw:             " << time_raw << " us\n";
        std::cout << "MyShared:        " << time_my << " us\n";
        std::cout << "std::shared_ptr: " << time_std << " us\n";
        std::cout << '\n';

    }

    return 0;

}