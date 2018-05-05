# TradeParser

Problem Statement:
1) Reading CSV file in following format
   <TimeStamp>,<Symbol>,<Quantity>,<Price>
   Field definitions:
   - TimeStamp is value indicating the microseconds since midnight.
   - Symbol is the 3 character unique identifier for a financial 
    instrument (Stock, future etc.)
   - Quantity is the amount traded
   - Price is the price of the trade for that financial instrument.
2) Generating stats as per follwing per instrument
   - Maximum time gap
    (time gap = Amount of time that passes between consecutive trades of a symbol)
    if only 1 trade is in the file then the gap is 0.
   - Total Volume traded (Sum of the quantity for all trades in a symbol).
   - Max Trade Price.
   - Weighted Average Price.  Average price per unit traded not per trade.
    Result should be truncated to whole numbers.
3) Output in csv in following format
   <symbol>,<MaxTimeGap>,<Volume>,<WeightedAveragePrice>,<MaxPrice>

Assumptions:
- TimeStamp is always for the same day and won't roll over midnight.
- TimeStamp is increasing or same as previous tick (time gap will never be < 0).
- Price - our currency is an integer based currency.  No decimal points.
- Price - Price is always > 0.

Design and Construction:
  CSVReader:
    Read line by line push tokens into vector and then convert them into Trade tuple as per fields type.
  TradeStore:
    Class to store stats per instrument and processing trade tuple
  Statistics:
    Create pointers to bind functions as per requirements in 2), and store these operations
    into store. Once Trade tuple is being passed apply all operations on trade tuple.
  CSVWriter
    Write resulting statistics into csv file as per 3)

I have incorporated various compile tools within this project using CMake
1) clang-format 
    For beautification of source code. Command for changeing source code format as per standard is "make clangformat"
2) cppcheck
    Tool for static code analysis
    make cppcheck
3) clang-tidy
    Tool for static code analysis. This tools follow most of the guidelines mentioned at https://github.com/isocpp/CppCoreGuidelines/blob/master/CppCoreGuidelines.md
    make clang-tidy 
4) gtest
    TDD tool for writing test cases
    make test
    ctest
5) gbenchamrk
    For testing performance of particular operation in C++
6) valgrind memcheck
    For detecting memory leak within source code
    ctest -T memcheck
7) package creation
    Once project is at delivery stage, there is make package and make package_source creates corresponding packages of the project
    make package 
    make package_source
8) doxygen documentation
    make doc