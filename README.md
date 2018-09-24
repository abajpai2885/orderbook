C++ Order Book

Design

    Data Structure:

    order book is implemented with std::map of std::list, one per side,
        see:
        Class Engine {
            PriceOrderBook  buyOrderBook_;
            PriceOrderBook  sellOrderBook_;
        }


    std::unordered_map of all orders:
        see:
        Class Engine {
            HisOrderEntrys  hisOrderEntry_;
        }
        map key is order id, value is of type struct Order.


Constraint


        const size_t MaxTradeSize = 1000000;
        const size_t MaxTradePrice = 10000000;
        const size_t MaxMsgLength = 500;
        const size_t MinMsgLength = 5;

Build

    mkdir build && cd build
    cmake ../
    make

    tested with:


    Apple LLVM version 10.0.0 (clang-1000.11.45.2)
    Target: x86_64-apple-darwin17.7.0, cmake 3.11.2


Run

    ./matchengine ../test/sample_msg.txt

    build and tested with
    --prefix=/Applications/Xcode.app/Contents/Developer/usr --with-gxx-include-dir=/usr/include/c++/4.2.1
    Apple LLVM version 10.0.0 (clang-1000.11.45.2)
    Target: x86_64-apple-darwin17.7.0


    output:

--- MIDQuote --------------------------------------
NAN
--- MIDQuote --------------------------------------
1037.5
--- MIDQuote --------------------------------------
1037.5
--- MIDQuote --------------------------------------
1025
--- MIDQuote --------------------------------------
1025
--- MIDQuote --------------------------------------
1012.5
--- MIDQuote --------------------------------------
1012.5
--- MIDQuote --------------------------------------
1012.5
--- MIDQuote --------------------------------------
1012.5
--- MIDQuote --------------------------------------
1037.5
---ORDER BOOK --------------------------------------
SELLS
1075, 1
1050, 10
1025, 2, 5
BUYS
1050, 3
1000, 9, 1
975, 30
--- MIDQuote --------------------------------------
1012.5
--- MIDQuote --------------------------------------
1012.5
--- MIDQuote --------------------------------------
1012.5
---ORDER BOOK --------------------------------------
SELLS
1075, 1
1050, 10
1025, 4
BUYS
1000, 9, 1
975, 30
