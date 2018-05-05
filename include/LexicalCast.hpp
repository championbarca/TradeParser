#ifndef TRADE_PARSER_LEXICAL_CAST_HPP
#define TRADE_PARSER_LEXICAL_CAST_HPP
#include <cstdlib>

namespace TradeParser {
    /**
     * @brief   Boost lexical cast can be used, but just wanted something
     *          quick and easy, so created it for reading from CSV file
     *          And converting it to corresponding type
     * @tparam T Type to be converted to from string
     */
    template <typename T>
    struct LexicalCast{
        T operator() (char* const str) {
            return T(str);
        }
    };

    template <>
    struct LexicalCast<int>{
        int operator() (char* const str) {
            return atoi(str);
        }

    };

    template <>
    struct LexicalCast<long>{
        long operator() (char* const str) {
            return atol(str);
        }

    };

}
#endif //TRADE_PARSER_LEXICAL_CAST_HPP