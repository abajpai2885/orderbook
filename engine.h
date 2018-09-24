//
// Created by Rui Zhou on 2/3/18.
//

#ifndef ORDERBOOK_MATCH_ENGINE_H
#define ORDERBOOK_MATCH_ENGINE_H

#include "types.h"
#include "order_book.h"


namespace JT {
    class Engine {
        HisOrderEntrys  hisOrderEntry_;
        PriceOrderBook  buyOrderBook_;
        PriceOrderBook  sellOrderBook_;

        TradeQty        recentTradeSize_;
        Price           recentTradePrice_;

    private:
        void CheckPriceCross();

    public:
        Engine();
        void HandleOrder(const Order &order);

        void HandleTrade(const Trade &trade);

        void PrintOrderBook(std::ostream &os) const;

        void PrintTradeMessage();
        void PrintMidQuote();

        void Add(const Order &order);
        void Remove(Order &oldOrder, const Order &newOrder);
        void Modify(Order &oldOrder, Order &newOrder);
    };
}
#endif //ORDERBOOK_MATCH_ENGINE_H
