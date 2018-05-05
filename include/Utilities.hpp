#ifndef TRADE_PARSER_UTILITIES_HPP
#define TRADE_PARSER_UTILITIES_HPP

#include <tuple>
#include <vector>
#include <utility>

namespace TradeParser {
    namespace Utilities {
        using Fields = std::vector<char*>;
        using strItr = Fields::const_iterator;

        template<class Tuple, int N >
        struct helper {
            static void fill(Tuple& tuple, strItr& it, strItr& end){

                typedef typename std::tuple_element<std::tuple_size<Tuple>::value-N-1,Tuple>::type value_type ;
                std::get<std::tuple_size<Tuple>::value-N-1>(tuple) = TradeParser::LexicalCast<value_type>()(*it);
                ++it;
                helper<Tuple,N-1>::fill(tuple,it,end);
            }
        };

        template<class Tuple>
        struct helper<Tuple, 0> {
            static void fill(Tuple& tuple, strItr it, strItr end){
                
                typedef typename std::tuple_element<std::tuple_size<Tuple>::value-1,Tuple>::type value_type;
                std::get<std::tuple_size<Tuple>::value-1>(tuple) = TradeParser::LexicalCast<value_type>()(*it);
                ++it;
            };
        };

        /**
         * @brief To fill the elements from other container into tuple
         * 
         * @tparam Tuple Tuple type to fill the elemetns
         */
        template<class Tuple>
        struct filler {
        static void fill(Tuple& tuple, strItr it, strItr end){
                helper<Tuple, std::tuple_size<Tuple>::value-1>::fill(tuple,it,end);
            }
        };

        /**
         * @brief helper function to print a tuple of any size
         * 
         * @tparam Tuple Tuple type
         * @tparam N     Args count
         */
        template<class Tuple, std::size_t N>
        struct TuplePrinter {
            static void print(const Tuple& t) 
            {
                TuplePrinter<Tuple, N-1>::print(t);
                std::cout << ", " << std::get<N-1>(t);
            }
        };
        
        template<class Tuple>
        struct TuplePrinter<Tuple, 1> {
            static void print(const Tuple& t) 
            {
                std::cout << std::get<0>(t);
            }
        };

        template <class... Args>
        void PrintElements(std::tuple<Args...>& cont) {
            std::cout << "(";
            TuplePrinter<decltype(cont), sizeof...(Args) >::print(cont);
            std::cout << ")\n";
        }
    }
}

#endif  //TRADE_PARSER_UTILITIES_HPP