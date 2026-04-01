#include "benchmark/benchmark.h"

static void benchmarkString(benchmark::State& state)
{
    int64_t len = state.range(0);
    for (auto _ : state) {
        std::string str(len, 'a');
        benchmark::DoNotOptimize(str);
    }
}

// 测试指定参数的构造代价
BENCHMARK(benchmarkString)->Arg(8)->Arg(16)->Arg(24);
// 指定范围的抽样测试构造代价
BENCHMARK(benchmarkString)->Range(8, 8 << 10);

// 采用毫秒作为时间单位去统计
BENCHMARK(benchmarkString)->Arg(32)->Arg(64)->Unit(benchmark::kMillisecond);
// 采用多线程进行性能统计
BENCHMARK(benchmarkString)->Range(8, 8 << 10)->Threads(2);


BENCHMARK_MAIN();