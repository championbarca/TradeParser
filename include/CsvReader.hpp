#ifndef TRADE_PARSER_CSVREADER_HPP
#define TRADE_PARSER_CSVREADER_HPP

#include <string>
#include <fstream>
#include <string.h>
#include "Error.hpp"
#include "LexicalCast.hpp"
#include "Utilities.hpp"

namespace TradeParser {

    /**
     * @brief This class is generic class for reading CSVfile.
     * On each row callback is returned to caller with tuple.
     * TO-DO To check number of fields matching number of fields in tuple.
     */
    class CsvReader {
    public:
        CsvReader(const std::string& fileName, const std::string& separator = ",") 
            : _inputFileName(fileName), _separator(separator) {
            
            _inputFile.open(_inputFileName);
            if (!_inputFile.is_open()) {
                throw TradeParser::BadInputFileException();
            }
        }

        ~CsvReader() {
            if (_inputFile.is_open()) {
                _inputFile.close();
            }
        }

        /**
         * @brief  To Read file line by line and calling callback for each row
         * 
         * @tparam CALLBACK Resulting back with row read in tuple
         * @tparam Args     Tuple Elements (no. of fields in CSV)
         * @param func      Callback function
         * @return true     File was processed succesfully
         * @return false    File failed to process successfully
         */
        template<typename CALLBACK, typename... Args> 
        bool process(CALLBACK& func) {
            using namespace TradeParser::Utilities;

            using CONTAINER = std::tuple<Args...>;
            if (!_inputFile.is_open()) {
                throw TradeParser::BadInputFileException();
            }

            std::string line;
            Fields fields;
            CONTAINER record;
            int lineNo = 0;
            while (std::getline(_inputFile, line)) {
                if (line.empty() || line[0] == '#') 
                    continue;   //Header or comment or empty
                
                char* temp = strtok(const_cast<char*>(line.c_str()), _separator.c_str());
                while (temp) {
                    fields.push_back(temp);
                    temp = strtok(NULL, _separator.c_str());
                }
                if (fields.size() > 0) {
                    filler<CONTAINER>::fill(record, fields.cbegin(), fields.cend());
                    func(record);
                }
                fields.clear();
                ++lineNo;
            }

            return true;
        }

        //To limit reader of csv file
        CsvReader(const CsvReader&) = delete;
        CsvReader& operator=(const CsvReader&) = delete;
        CsvReader(const CsvReader&&) = delete;
        CsvReader& operator=(const CsvReader&&) = delete;


    private:
        std::string         _inputFileName;
        std::ifstream       _inputFile;
        std::string         _separator;
    };
}

#endif  //TRADE_PARSER_CSVREADER_HPP