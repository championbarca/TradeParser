#include <gtest/gtest.h>
#include "Statistics.hpp"

TEST(Statistics_TEST, FirstMaxTimeGap) { 
    std::string symbol("abc");
    TradeParser::Statistics<int, int, std::string, int, int> stats(symbol);
    std::tuple<int, std::string, int, int> tup = std::make_tuple(1000, "abc", 10, 10);
    stats.onUpdate(tup);
    EXPECT_EQ(0, stats.getMaxTimeGap()); 
}

TEST(Statistics_TEST, TotalVolume) { 
    std::string symbol("def");
    TradeParser::Statistics<int, int, std::string, int, int> stats(symbol);
    std::tuple<int, std::string, int, int> tup = std::make_tuple(1000, "def", 10, 10);
    stats.onUpdate(tup);
    tup = std::make_tuple(1000, "def", 10, 10);
    stats.onUpdate(tup);
    //std::cout << stats.getTotalVolume() << std::endl;
    EXPECT_EQ(20, stats.getTotalVolume()); 
}

TEST(Statistics_TEST, MaxPriceFirstPrice) { 
    std::string symbol("cba");
    TradeParser::Statistics<int, int, std::string, int, int> stats(symbol);
    std::tuple<int, std::string, int, int> tup = std::make_tuple(1000, "cba", 10, 10);
    stats.onUpdate(tup);
    tup = std::make_tuple(1000, "cba", 10, 1);
    stats.onUpdate(tup);
    EXPECT_EQ(10, stats.getMaxPrice()); 
}

TEST(Statistics_TEST, MaxPriceLastPrice) { 
    std::string symbol("dva");
    TradeParser::Statistics<int, int, std::string, int, int> stats(symbol);
    std::tuple<int, std::string, int, int> tup = std::make_tuple(1000, "dva", 10, 1);
    stats.onUpdate(tup);
    tup = std::make_tuple(1000, "dva", 10, 10);
    stats.onUpdate(tup);
    tup = std::make_tuple(1000, "dva", 10, 20);
    stats.onUpdate(tup);
    EXPECT_EQ(20, stats.getMaxPrice()); 
}

TEST(Statistics_TEST, WeightedAverage) { 
    std::string symbol("abd");
    TradeParser::Statistics<int, int, std::string, int, int> stats(symbol);
    std::tuple<int, std::string, int, int> tup = std::make_tuple(1000, "abd", 10, 10);
    stats.onUpdate(tup);
    tup = std::make_tuple(1000, "abd", 10, 10);
    stats.onUpdate(tup);
    tup = std::make_tuple(1000, "abd", 10, 10);
    stats.onUpdate(tup);
    //std::cout << stats.getWeightedAvg() << std::endl;
    EXPECT_EQ(10, stats.getWeightedAvg()); 
}


