#ifndef TRADE_PARSER_STATISTICS_HPP
#define TRADE_PARSER_STATISTICS_HPP
#include <tuple>
#include <functional>
#include <vector>
#include <iostream>
#include <fstream>
#include "Accumulators.hpp"

int             lineNo = 0;
namespace TradeParser {
    using namespace TradeParser::Accumulators;

    /**
     * @brief       Storing stats with respect to each Symbol
     * 
     * @tparam T    Type of stored variables
     * @tparam Args Type of tuple
     */
    template <typename T, typename... Args>
    class Statistics {
        
    public:
        /**
         * @brief Construct a new Statistics object
         *        All the required operations are mapped with reference to member variable.
         *        And stored in store so that when each rows are read they can be called.
         *        TODO: convert these bind operations into tuple so that they can be specified 
         *        as operation into type of class. Like boost::accumulator
         * @param symbol Stats belongs to Symbol
         */
        Statistics(std::string& symbol) : _symbol(symbol), _totalVolume(0), _maxTimeGap(0), _lastTimeStamp(0),
                                    _totalValue(0), _maxPrice(0) {
            using namespace TradeParser;
            std::function<T(std::tuple<Args...>&)> func  = 
                        std::bind(Max<static_cast<int>(FieldsId::PRICE), T, Args...>, std::ref(_maxPrice), 
                                                    std::placeholders::_1);
            _accumulators.push_back(func);
            func  = std::bind(WeightedAverage<static_cast<int>(FieldsId::PRICE), 
                            static_cast<int>(FieldsId::QTY), T, Args...>, std::ref(_totalVolume), 
                                        std::ref(_totalValue), std::placeholders::_1);
            _accumulators.push_back(func);
            func  = std::bind(MaxGap<static_cast<int>(FieldsId::TIMESTAMP), T, Args...>, 
                            std::ref(_lastTimeStamp), std::ref(_maxTimeGap), std::placeholders::_1);
            _accumulators.push_back(func);
        }

        ~Statistics() {
            _accumulators.clear();
        }

        Statistics(const Statistics& rhs) {
            if (this == &rhs)
                return;
            
            this->_totalValue       = rhs._totalValue;
            this->_totalVolume      = rhs._totalVolume;
            this->_maxTimeGap       = rhs._maxTimeGap;
            this->_maxPrice         = rhs._maxPrice;
            this->_lastTimeStamp    = rhs._lastTimeStamp;
            this->_symbol           = rhs._symbol;
            this->_accumulators     = rhs._accumulators;
        }

        Statistics(const Statistics&& rhs) {
            this->_totalValue       = rhs._totalValue;
            this->_totalVolume      = rhs._totalVolume;
            this->_maxTimeGap       = rhs._maxTimeGap;
            this->_maxPrice         = rhs._maxPrice;
            this->_lastTimeStamp    = rhs._lastTimeStamp;
            this->_symbol           = rhs._symbol;
            this->_accumulators     = std::move(rhs._accumulators);
        }

        Statistics& operator=(const Statistics& rhs) {
            if (this == &rhs)
                return (*this);
            
            this->_totalValue       = rhs._totalValue;
            this->_totalVolume      = rhs._totalVolume;
            this->_maxTimeGap       = rhs._maxTimeGap;
            this->_maxPrice         = rhs._maxPrice;
            this->_lastTimeStamp    = rhs._lastTimeStamp;
            this->_symbol           = rhs._symbol;
            this->_accumulators     = rhs._accumulators;
            return (*this);
        }

        Statistics& operator=(const Statistics&& rhs) {
            this->_totalValue       = rhs._totalValue;
            this->_totalVolume      = rhs._totalVolume;
            this->_maxTimeGap       = rhs._maxTimeGap;
            this->_maxPrice         = rhs._maxPrice;
            this->_lastTimeStamp    = rhs._lastTimeStamp;
            this->_symbol           = rhs._symbol;
            this->_accumulators     = std::move(rhs._accumulators);
            return (*this);
        }
        
        /**
         * @brief On reading each row from file and updating stat fields
         * 
         * @param tradeTup Tuple of elements being read from file
         */
        void onUpdate(std::tuple<Args...>& tradeTup) {
            for (auto& func : _accumulators)
                func(tradeTup);

            //if (_totalValue < 0 || _totalVolume < 0 || _maxPrice < 0) {
                std::cout << ::lineNo << "," << _symbol << "," << _maxTimeGap << "," << _totalVolume << "," <<
                    _totalValue << "," << _maxPrice << std::endl;
            //}
            ::lineNo++;
        }

        T getTotalVolume() const { return _totalVolume; }
        T getMaxTimeGap() const { return _maxTimeGap; }
        T getTotalValue() const { return _totalValue; }
        T getMaxPrice() const { return _maxPrice; }
        T getWeightedAvg() const { return _totalVolume ? _totalValue / _totalVolume : _totalValue; }
        std::string& getSymbol() const { return _symbol; }

        /**
         * @brief Print all the required fields to files
         * 
         * @param out Output stream
         * @param sep separator between fields
         * @return std::ofstream& return output stream
         */
        std::ofstream& print(std::ofstream& out, const std::string& sep) {
            out << _symbol << sep << _maxTimeGap << sep << _totalVolume << sep <<
                this->getWeightedAvg() << sep << _maxPrice << std::endl;
            return out;
        }

    private:

        std::string     _symbol;
        T               _totalVolume;
        T               _maxTimeGap;
        T               _lastTimeStamp;
        T               _totalValue;
        T               _maxPrice;
        
        std::vector<std::function<T(std::tuple<Args...>&)>>         _accumulators;
    };
    
}

#endif      //TRADE_PARSER_STATISTICS_HPP