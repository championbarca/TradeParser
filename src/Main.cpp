#include <iostream>
#include "version.hpp"
#include "Error.hpp"
#include "CsvReader.hpp"
#include "CsvWriter.hpp"
#include "TradeStore.hpp"

int main(int argc, char** argv) {
    //Parse();
    if (argc < 3) {
        std::cout << TradeParser::ErrorStrings::COMMAND_USAGE << std::endl;
        return -1;
    }

    TradeParser::CsvReader reader(argv[1]);
    TradeParser::TradeStore<int, int, std::string, int, int> tp;
    auto func = std::bind(&TradeParser::TradeStore<int, int, std::string, int, int>::onTrade, &tp, std::placeholders::_1);
    reader.process<decltype(func), int, std::string, int, int>(func);
    TradeParser::CsvWriter writer(argv[2]);
    tp.print(writer.getStream(), writer.getSeparator());
    
    return 0;

}