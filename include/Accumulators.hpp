#ifndef TRADE_PARSER_ACCUMULATORS_HPP
#define TRADE_PARSER_ACCUMULATORS_HPP

#include <tuple>

namespace TradeParser {

    /**
     * @brief Field id index within tuple
     * 
     */
    enum class FieldsId : int {
        TIMESTAMP = 0,
        SYMBOL,
        QTY,
        PRICE
    };

    namespace Accumulators {

        /**
         * @brief : Max of Value from Tuple at Index
         * 
         * @tparam N    Index Of Tuple 
         * @tparam T    Type of max element
         * @tparam Args Tuple Args
         * @param max   Reference to Store Value
         * @param cont  Tuple of elements
         * @return T    Return Max after each call
         */
        template <size_t N, typename T, typename... Args>
        T Max(T& max, std::tuple<Args...>& cont) {
            max = max < std::get<N>(cont) ? std::get<N>(cont) : max;
            return max;
        }

        /**
         * @brief       Sum of value from Tuple at Index
         * 
         * @tparam N    Index Of Tuple 
         * @tparam T    Type of sum element
         * @tparam Args Tuple Args
         * @param sum   Reference to Store Value
         * @param cont  Tuple of elements
         * @return T&   Return Sum after each call
         */
        template <size_t N, typename T, typename... Args>
        T& Sum(T& sum, std::tuple<Args...>& cont) {
            sum += std::get<N>(cont);
            return sum;
        }

        /**
         * @brief               Weighted Average of given values from Tuple
         * 
         * @tparam VarIndex     Price variable Index
         * @tparam WeightIndex  Qty variable index
         * @tparam T            Type of elements
         * @tparam Args         Tuple Args
         * @param totalSum      Reference to cumulative Value
         * @param totalValue    Reference to cumulative Qty
         * @param cont          Tuple of elements
         * @return T            Return weighted average after each call
         */
        template <size_t VarIndex, size_t WeightIndex, typename T, typename... Args>
        T WeightedAverage(T& totalSum, T& totalValue, std::tuple<Args...>& cont) {
            totalValue += (std::get<VarIndex>(cont) * std::get<WeightIndex>(cont));
            totalSum += std::get<WeightIndex>(cont);
            return totalValue / totalSum; 
        }

        /**
         * @brief               MaxGap of Timestamp from previous timestamp
         * 
         * @tparam N            Tuple Index of timestamp
         * @tparam T            Type of timestamp
         * @tparam Args         Tuple Args
         * @param lastTimestamp Reference to Last TimeStamp
         * @param maxTimeGap    Calculated timegap from last timestamp
         * @param cont          Tuple of elements
         * @return T            Return MaxGap after each call
         */
        template <size_t N, typename T, typename... Args>
        T MaxGap(T& lastTimestamp, T& maxTimeGap, std::tuple<Args...>& cont) {
            if (lastTimestamp) {
                T latestTimeGap = std::get<N>(cont) - lastTimestamp;
                maxTimeGap = (maxTimeGap < latestTimeGap ? latestTimeGap : maxTimeGap);
            }
            else
                maxTimeGap = 0;

            lastTimestamp = std::get<N>(cont);
            return maxTimeGap;
        }
    }
}

#endif      //TRADE_PARSER_ACCUMULATORS_HPP