#include <algorithm>
#include <chrono>
#include <thread>
#include <iostream>
#include <random>
#include <vector>
#include <atomic>
#include <numeric>
#include <functional>

typedef unsigned long long int bigint;

bool isPrime(bigint n)
{
    if (n <= 1)
        return false;
    for (bigint i = 2; i <= n / 2; i++)
        if (n % i == 0)
            return false;
    return true;
}

size_t single(const std::vector<bigint>& v)
{
    return std::count_if(v.begin(), v.end(), [](const auto& el)
        {
            return isPrime(el);
        });
}

size_t block_way(const std::vector<bigint>& v, size_t n_threads)
{
    std::vector<size_t> results(n_threads);
    auto lambda = [&v, &results](size_t a, size_t b, size_t thread_id)
        {
            auto sum = std::count_if(v.begin() + a, v.begin() + b, [](const auto& el)
                {
                    return isPrime(el);
                });
            results[thread_id] = sum;
        };

    std::vector<std::thread> threads(n_threads);
    int part_size = v.size() / n_threads, a = 0, b = 0;
    for (int thread_id = 0; thread_id != n_threads; thread_id++, a = b)
    {
        b = (thread_id == n_threads - 1) ? v.size() : a + part_size;
        threads[thread_id] = std::thread(lambda, a, b, thread_id);
    }

    for (auto& t : threads)
        t.join();

    return std::accumulate(results.begin(), results.end(), 0);
}

size_t atomic_way(const std::vector<bigint>& v, size_t n_threads)
{
    std::atomic<size_t> index(0);
    std::atomic<size_t> count(0);

    auto lambda = [&v, &index, &count]()
        {
            size_t i;
            while ((i = index.fetch_add(1)) < v.size())
            {
                if (isPrime(v[i]))
                {
                    count.fetch_add(1);
                }
            }
        };

    std::vector<std::thread> threads(n_threads);
    for (size_t thread_id = 0; thread_id != n_threads; thread_id++)
    {
        threads[thread_id] = std::thread(lambda);
    }

    for (auto& t : threads)
        t.join();

    return count.load();
}

int main()
{
    std::vector<bigint> v(2520);
    std::mt19937_64 gen;
    gen.seed(1);
    std::uniform_int_distribution<bigint> dp(1, bigint(std::numeric_limits<int>::max()));
    for (auto& item : v)
        item = dp(gen);

    auto t1 = std::chrono::high_resolution_clock::now();
    auto nsingle = single(v);
    auto t2 = std::chrono::high_resolution_clock::now();
    auto single_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
    std::cout << 1 << '\t' << single_time << '\t' << single_time << '\t' << single_time << std::endl;

    for (size_t i = 2; i <= 8; i += 1)
    {
        t1 = std::chrono::high_resolution_clock::now();
        auto nblock = block_way(v, i);
        t2 = std::chrono::high_resolution_clock::now();
        auto block_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        t1 = std::chrono::high_resolution_clock::now();
        auto natomic = atomic_way(v, i);
        t2 = std::chrono::high_resolution_clock::now();
        auto atomic_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();

        std::cout << i << '\t' << single_time << '\t' << block_time << '\t' << atomic_time << '\t' << nsingle << '\t' << nblock << '\t' << natomic << std::endl;
    }
}

//#include <algorithm>
//#include <chrono>
//#include <thread>
//#include <iostream>
//#include <random>
//#include <vector>
//#include <limits>
//#include <numeric>
//#include <atomic>
//#include <cmath>
//
//typedef unsigned long long int bigint;
//
//bool isPrime(bigint n)
//{
//    if (n <= 1)
//        return false;
//    if (n <= 3)
//        return true;
//    if (n % 2 == 0 || n % 3 == 0)
//        return false;
//    for (bigint i = 5; i * i <= n; i += 6)
//    {
//        if (n % i == 0 || n % (i + 2) == 0)
//            return false;
//    }
//    return true;
//}
//
//size_t single(const std::vector<bigint>& v)
//{
//    return std::count_if(v.begin(), v.end(), [](const auto& el)
//        {
//            return isPrime(el);
//        });
//}
//
//size_t block_way(const std::vector<bigint>& v, size_t n_threads)
//{
//    std::vector<size_t> results(n_threads);
//    auto lambda = [&v, &results](size_t a, size_t b, size_t thread_id)
//        {
//            auto sum = std::count_if(v.begin() + a, v.begin() + b, [](const auto& el)
//                {
//                    return isPrime(el);
//                });
//            results[thread_id] = sum;
//        };
//
//    std::vector<std::thread> threads(n_threads);
//    size_t part_size = v.size() / n_threads, a = 0, b = 0;
//    for (size_t thread_id = 0; thread_id != n_threads; thread_id++, a = b)
//    {
//        b = (thread_id == n_threads - 1) ? v.size() : a + part_size;
//        threads[thread_id] = std::thread(lambda, a, b, thread_id);
//    }
//
//    for (auto& t : threads)
//        t.join();
//
//    return std::accumulate(results.begin(), results.end(), 0);
//}
//
//size_t atomic_way(const std::vector<bigint>& v, size_t n_threads)
//{
//    std::atomic<size_t> current_index(0);
//    std::atomic<size_t> prime_count(0);
//
//    auto lambda = [&]()
//        {
//            size_t index;
//            while ((index = current_index.fetch_add(1)) < v.size())
//            {
//                if (isPrime(v[index]))
//                {
//                    prime_count.fetch_add(1);
//                }
//            }
//        };
//
//    std::vector<std::thread> threads(n_threads);
//    for (auto& t : threads)
//    {
//        t = std::thread(lambda);
//    }
//
//    for (auto& t : threads)
//    {
//        t.join();
//    }
//
//    return prime_count.load();
//}
//
//int main()
//{
//    // список, заполненный случайными натуральными числами
//    std::vector<bigint> v(2520);
//    std::mt19937_64 gen;
//    gen.seed(1);
//    std::uniform_int_distribution<bigint> dp(1, bigint(std::numeric_limits<int>::max()));
//    for (auto& item : v)
//        item = dp(gen);
//
//    // однопоточная версия поиска простых чисел
//    auto t1 = std::chrono::high_resolution_clock::now();
//    auto nsingle = single(v);
//    auto t2 = std::chrono::high_resolution_clock::now();
//    auto single_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
//    std::cout << 1 << '\t' << single_time << '\t' << single_time << '\t' << single_time << '\t' << nsingle << '\t' << nsingle << '\t' << nsingle << std::endl;
//
//    // i - число потоков
//    for (size_t i = 2; i <= 8; i += 1)
//    {
//        t1 = std::chrono::high_resolution_clock::now();
//        auto nblock = block_way(v, i);
//        t2 = std::chrono::high_resolution_clock::now();
//        auto block_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
//
//        t1 = std::chrono::high_resolution_clock::now();
//        auto natomic = atomic_way(v, i);
//        t2 = std::chrono::high_resolution_clock::now();
//        auto atomic_time = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
//
//        std::cout << i << '\t' << single_time << '\t' << block_time << '\t' << atomic_time << '\t' << nsingle << '\t' << nblock << '\t' << natomic << std::endl;
//    }
//}
