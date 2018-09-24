
#include "feed_handler.h"
#include "order_book.h"
#include <sstream>
#include "error_monitor.h"

using namespace std;

namespace JT {
    FeedHandler::FeedHandler() {

    }

    /*
     *  A,100000,S,1,1075
        A,100001,B,9,1000
        A,100002,B,30,975
        A,100003,S,10,1050
        A,100004,B,10,950
        A,100005,S,2,1025
        A,100006,B,1,1000
        X,100004,B,10,950 // cancel
        A,100007,S,5,1025
        A,100008,B,3,1050
        T,2,1025
        T,1,1025
        X,100008,B,3,1050
        X,100005,S,2,1025
        M,100007,S,4,1025 // order is modified down to reflect quantity traded

     */

    void FeedHandler::LogParseError(ParseResult err) {
        switch (err) {
            case ParseResult ::CorruptMessage:
                ErrorMonitor::GetInstance().CorruptMessage();
                break;
            case ParseResult ::InvalidMsgData:
                ErrorMonitor::GetInstance().InvalidMsg();
                break;
            default:
                break;
        }
    }

    bool FeedHandler::ParseTrade(char *tokenMsg, Trade &trd) {
        ParseResult result = ParseTokenAsUInt(tokenMsg, trd.tradeQty);
        if (result != ParseResult::Good) {
            LogParseError(result);
            return false;
        }

        double price;
        result = ParsePrice(tokenMsg, price);
        if (result != ParseResult ::Good) {
            LogParseError(result);
            return false;
        }
        trd.tradePrice = price * 100;
        return true;
    }

    bool FeedHandler::ParseOrder(char *tokenMsg, Order &order) {
        // order id
        ParseResult result = ParseTokenAsUInt64(tokenMsg, order.orderId);
        if (result != ParseResult ::Good){
            LogParseError(result);
            return false;
        }

        // side
        result = ParseSide(tokenMsg, order.side);
        if (result != ParseResult ::Good) {
            LogParseError(result);
            return false;
        }

        // size
        result = ParseTokenAsUInt(tokenMsg, order.qty);
        if (result != ParseResult::Good) {
            LogParseError(result);
            return false;
        }

        if (order.qty > MaxTradeSize) {
            result = ParseResult ::InvalidMsgData;
            LogParseError(result);
            return false;
        }

        // price
        double price = 0;
        result = ParsePrice(tokenMsg, price);
        if (result != ParseResult ::Good) {
            LogParseError(result);
            return false;
        }
        order.price = price;
        if (order.price > MaxTradePrice) {
            result = ParseResult ::InvalidMsgData;
            LogParseError(result);
            return false;
        }
        order.status = OrderStatus::Normal;
        return true;
    }

    void FeedHandler::ProcessMessage(const std::string &line) {
        static Order order;
        static Trade trd;

        char *buf = const_cast<char*>(line.c_str());
        MessageType mt = GetMessageType(buf);

        if (mt == MessageType::Unknown) {
            ErrorMonitor::GetInstance().CorruptMessage();
        } else if (mt == MessageType::Trade) {
            if (ParseTrade(buf, trd)) {
                engine_.HandleTrade(trd);
            } else {
                ErrorMonitor::GetInstance().CorruptMessage();
            }
        } else {
            order.action = mt;
            if (ParseOrder(buf, order)) {
                engine_.HandleOrder(order);
                engine_.PrintMidQuote();
            } else {
                ErrorMonitor::GetInstance().CorruptMessage();
            }
        }

    }


    void FeedHandler::PrintCurrentOrderBook(std::ostream &os) const {
        engine_.PrintOrderBook(os);
    }
}