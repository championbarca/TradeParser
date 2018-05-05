#ifndef TRADE_PARSER_CSVWRITER_HPP
#define TRADE_PARSER_CSVWRITER_HPP

#include <string>
#include <fstream>
#include "Error.hpp"

namespace TradeParser {
    /**
     * @brief To Write CSV file 
     * To-Do to move writeline code inside this class
     */
    class CsvWriter {
    public:
        CsvWriter(const std::string& fileName, const std::string& separator = ",") 
            : _outputFileName(fileName), _separator(separator) {
            
            _outputFile.open(_outputFileName);
            if (!_outputFile.is_open()) {
                throw TradeParser::BadOutputFileException();
            }
        }

        ~CsvWriter() {
            if (_outputFile.is_open()) {
                _outputFile.close();
            }
        }

        std::ofstream& getStream() {
            return _outputFile;
        }

        std::string& getSeparator() {
            return _separator;
        }

    private:
        std::string         _outputFileName;
        std::ofstream       _outputFile;
        std::string         _separator;
    };
}


#endif  //TRADE_PARSER_CSVWRITER_HPP