#ifndef TRADE_PARSER_TESTPROGRAM_HPP
#define TRADE_PARSER_TESTPROGRAM_HPP
#include <iostream>
#include "version.hpp"
#include "Error.hpp"
#include "CsvReader.hpp"
#include "CsvWriter.hpp"
#include "TradeStore.hpp"

int RunProgram(const char* inputFile, const char* outputFile) {
    TradeParser::CsvReader reader(inputFile);
    TradeParser::TradeStore<int, int, std::string, int, int> tp;
    auto func = std::bind(&TradeParser::TradeStore<int, int, std::string, int, int>::onTrade, &tp, std::placeholders::_1);
    reader.process<decltype(func), int, std::string, int, int>(func);
    TradeParser::CsvWriter writer(outputFile);
    tp.print(writer.getStream(), writer.getSeparator());

    return 0;
}

#endif //TRADE_PARSER_TESTPROGRAM_HPP