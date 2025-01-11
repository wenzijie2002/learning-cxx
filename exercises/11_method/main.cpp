#include "../exercise.h"

struct Fibonacci {
    unsigned long long cache[128];
    int cached;

    // 实现正确的缓存优化斐波那契计算
    unsigned long long get(int i) {
        // 如果要获取的斐波那契数已经在缓存中，直接返回
        if (i < cached) {
            return cache[i];
        }

        // 初始化缓存的前两个值
        cache[0] = 0;
        cache[1] = 1;
        cached = 2;

        // 填充缓存直到达到或超过要获取的索引 i
        while (cached <= i) {
            cache[cached] = cache[cached - 1] + cache[cached - 2];
            cached++;
        }

        return cache[i];
    }
};

int main(int argc, char **argv) {
    // 初始化缓存结构体
    Fibonacci fib;
    fib.cached = 0;// 初始时缓存中没有有效数据

    ASSERT(fib.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << fib.get(10) << std::endl;
    return 0;
}
