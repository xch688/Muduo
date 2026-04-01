#include "benchmark/benchmark.h"
#include "benchmark/benchmark_api.h"
#include "sylar/log.h"

static void benchmarkString(benchmark::State& state)
{
    int64_t len = state.range(0);
    for (auto _ : state) {
        std::string str(len, 'z');
        benchmark::DoNotOptimize(str);
        benchmark::ClobberMemory();
    }
}

// BENCHMARK(benchmarkString)->Arg(8)->Arg(64)->Arg(256);
// BENCHMARK(benchmarkString)->Range(8, 8 << 10);
// BENCHMARK(benchmarkString)->Ranges({{1, 8}, {8, 8 << 10}});
// BENCHMARK(benchmarkString)->RangeMultiplier(2)->Range(8, 8 << 10)->Complexity();


static void benchArgsProduct(benchmark::State& state)
{
    int64_t size = state.range(0);
    int64_t time = state.range(1);
    for (auto _ : state) {
        std::string str(size * time, 'z');
        benchmark::DoNotOptimize(str);
        benchmark::ClobberMemory();
    }
}

// BENCHMARK(benchArgsProduct)->ArgsProduct({{8, 64, 128}, {1, 2}});

class NmBenchmark : public benchmark::Fixture {
public:
    void SetUp(const ::benchmark::State& state) override
    {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "Setup....";
    }

    void TearDown(const ::benchmark::State& state) override
    {
        SYLAR_LOG_INFO(SYLAR_LOG_ROOT()) << "TearDown....";
    }
};

BENCHMARK_DEFINE_F(NmBenchmark, StringBenckmark)(benchmark::State& state)
{
    int64_t len = state.range(0);
    for (auto _ : state) {
        std::string str(len, 'z');
        benchmark::DoNotOptimize(str);
        benchmark::ClobberMemory();
    }
}

BENCHMARK_REGISTER_F(NmBenchmark, StringBenckmark)->Args({8});

BENCHMARK(benchmarkString)->Arg(8)->Arg(64)->Arg(256);


BENCHMARK_MAIN();
