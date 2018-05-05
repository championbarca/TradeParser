#include <benchmark/benchmark.h>
#include <iostream>
#include "Statistics.hpp"



static void BM_StatsUpdate(benchmark::State &state) {
  std::string symbol("abc");
  TradeParser::Statistics<int, int, std::string, int, int> stats(symbol);
  int timestamp = 10000; int Qty = 10; int Price = 10;
  std::tuple<int, std::string, int, int> tup = std::make_tuple(timestamp, "abc", Qty, Price);
  
  for (auto _ : state) {
    stats.onUpdate(tup);
    timestamp += 1; Qty += 5; Price += 5;
    tup = std::make_tuple(timestamp, "abc", Qty, Price);
  }
} 
BENCHMARK(BM_StatsUpdate);


BENCHMARK_MAIN();