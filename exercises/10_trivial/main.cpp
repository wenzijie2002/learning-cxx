#include "../exercise.h"

// READ: Trivial type <https://learn.microsoft.com/zh-cn/cpp/cpp/trivial-standard-layout-and-pod-types?view=msvc-170>

#include <cassert>
#include <iostream>

// 定义用于缓存斐波那契数的结构体
struct FibonacciCache {
    unsigned long long cache[16];
    int cached;
};

// 实现正确的缓存优化斐波那契计算
static unsigned long long fibonacci(FibonacciCache &cache, int i) {
    // 先判断是否已经缓存了要计算的斐波那契数，如果已缓存则直接返回
    if (i < cache.cached) {
        return cache.cache[i];
    }
    // 如果还未缓存到需要的位置，则继续计算并填充缓存
    for (; cache.cached < sizeof(cache.cache) / sizeof(cache.cache[0]); ++cache.cached) {
        if (cache.cached == 0) {
            cache.cache[cache.cached] = 0;
        } else if (cache.cached == 1) {
            cache.cache[cache.cached] = 1;
        } else {
            cache.cache[cache.cached] = cache.cache[cache.cached - 1] + cache.cache[cache.cached - 2];
        }
    }
    return cache.cache[i];
}

int main(int argc, char **argv) {
    // 初始化缓存结构体
    FibonacciCache fib;
    fib.cache[0] = 0;
    fib.cache[1] = 1;
    fib.cached = 2;
    ASSERT(fibonacci(fib, 10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fibonacci(fib, 10) << std::endl;
    return 0;
}
