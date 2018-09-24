
#ifndef ORDER_BOOK_H
#define ORDER_BOOK_H

#include "types.h"
#include <list>
#include <vector>
#include <unordered_map>
#include <map>

namespace JT {


    enum class MessageType {
        Unknown,
        Add,
        Remove,
        Modify,
        Trade
    };

    enum class OrderStatus {
        Normal,                 // initial status
        TradeDeleted,           // deleted via trade match
    };

    const Side BUY = 0;
    const Side SELL = 1;

    class PriceOrderItem {

    public:
        PriceOrderItem(size_t qty, OrderId oid):quantity(qty), orderId(oid){}
        size_t      quantity;
        OrderId     orderId;
    };

    typedef std::list<PriceOrderItem> PriceOrderList;
    typedef PriceOrderList::iterator    PriceOrderitemPtr;

    typedef struct {
        MessageType     action;     // 4
        Price           price;      // 4
        TradeQty        qty;       // 4
        OrderId         orderId;    // 8
        Side            side;       // 4
        PriceOrderitemPtr    ptr;    // 8 (iterator)
        OrderStatus     status;     // 4
        void TradeDelete() {
            status = OrderStatus ::TradeDeleted;
            // ptr will be invalid!!
        }

    }Order;


    typedef struct {
        TradeQty    tradeQty;
        Price       tradePrice;
    }Trade;

    class SamePriceOrderList :public PriceOrderList{
        TradeQty       totalTradeQty_;
    public:
        uint32_t GetTradeSize() {
            return totalTradeQty_;
        }
        void ChangeTradeSize(TradeQty sz) {
            totalTradeQty_+=sz;
        }
    };

    typedef Order   OrderEntryType;

    typedef std::map<Price, SamePriceOrderList> PriceOrderBook;

    typedef std::unordered_map<OrderId, Order> HisOrderEntrys;

}


#endif //ORDER_BOOK_H
