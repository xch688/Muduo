#include "benchmark/benchmark.h"

static void stringFunc(benchmark::State& state)
{
    auto func = [](const std::string& str) {
        std::string cstr = str;
        benchmark::DoNotOptimize(cstr);   // 防止编译器进行优化
    };
    for (auto _ : state) {
        // 在此处放置您要基准测试的代码
        func("hello world");
        benchmark::ClobberMemory();
    }
}

static void stringViewFunc(benchmark::State& state)
{
    auto func = [](const std::string_view str) {
        std::string cstr(str);
        benchmark::DoNotOptimize(cstr);   // 防止编译器进行优化
    };
    for (auto _ : state) {
        // 在此处放置您要基准测试的代码
        func("hello world");
        benchmark::ClobberMemory();
    }
}

BENCHMARK(stringFunc);
BENCHMARK(stringViewFunc);

BENCHMARK_MAIN();