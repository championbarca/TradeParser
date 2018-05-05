#ifndef TRADE_PARSER_ERROR_HPP
#define TRADE_PARSER_ERROR_HPP
#include <string>
#include <exception>


namespace TradeParser {
    /**
     * @brief All errors generated within this program will be kept here
     * 
     */
    struct ErrorStrings {
        static constexpr const char* const COMMAND_USAGE = "Command Usage: <Program Name> <InputFilename> <OutputFilename>";
    };

    /**
     * @brief Any exception reagrding reading of input file 
     * 
     */
    class BadInputFileException : public std::exception {
    public:
        virtual ~BadInputFileException() {}

        virtual const char* what() const noexcept {
            return "Input file opening error";
        }
    };

    /**
     * @brief Any exception reagrding reading of output file
     * 
     */
    class BadOutputFileException : public std::exception {
    public:
        virtual ~BadOutputFileException() {}

        virtual const char* what() const noexcept {
            return "Output file opening error";
        }
    };    
}

#endif  //TRADE_PARSER_ERROR_HPP