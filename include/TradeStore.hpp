#ifndef TRADE_PARSER_TRADESTORE_HPP
#define TRADE_PARSER_TRADESTORE_HPP

#include <string>
#include <map>
#include <unordered_map>
#include <tuple>
#include <memory>
#include "Statistics.hpp"


namespace TradeParser {
    /**
     * @brief  Trade Store containing symbol vs Stats
     * 
     * @tparam T    Type of stats fields
     * @tparam Args Type of tuple elements
     */
    template <typename T, typename... Args>
    class TradeStore {
        static constexpr const char* const PRINT_HEADER = 
                    "<symbol>,<MaxTimeGap>,<Volume>,<WeightedAveragePrice>,<MaxPrice>";
        using Store = std::map<std::string, std::unique_ptr<TradeParser::Statistics<T, Args...>>>;
    public:
        /**
         * @brief On Each row from file is read or stats to be updated
         * 
         * @param tradeTup Tuple of elements being read
         */
        void onTrade(std::tuple<Args...>& tradeTup) {
            std::string& symbol = std::get<static_cast<int>(FieldsId::SYMBOL)>(tradeTup);
            if (_stats.find(symbol) == _stats.end())
                _stats[symbol] = std::make_unique<TradeParser::Statistics<T, Args...>>(symbol);
             _stats[symbol]->onUpdate(tradeTup);
        }

        /**
         * @brief Print store of all symbols and their stats
         * 
         * @param out Output stream
         * @param sep Separator between fields
         * @return std::ofstream& Output stream
         */
        std::ofstream& print(std::ofstream& out, std::string& sep) {
            out << PRINT_HEADER << std::endl;
            for (auto& stat : _stats)
                stat.second->print(out, sep);
            
            return out;
        }

        auto& getStats(const std::string& symbol) {
            return _stats[symbol];
        }

    private:
        Store           _stats;
    };
}


#endif //TRADE_PARSER_TRADESTORE_HPP