
#include <climits>
#include <algorithm>
#include <iostream>
#include <iomanip>

#include "engine.h"
#include "error_monitor.h"
#include "order_book.h"


using namespace std;

namespace JT {
    Engine::Engine()
    :recentTradeSize_(0),recentTradePrice_(0)
    {
    }

    void Engine::HandleOrder(const Order &order) {
        auto oldOrderIt = hisOrderEntry_.find(order.orderId);

        if (oldOrderIt == hisOrderEntry_.end()) {
            if (order.action == MessageType ::Add) {
                Add(order);
            } else {
                // missing order id in our records, but not an add
                ErrorMonitor::GetInstance().MissingOrder();
            }
        } else {
            // order exists
            Order &oldOrder = oldOrderIt->second;

            if (order.action == MessageType::Add) {
                // duplicate add
                ErrorMonitor::GetInstance().DuplicateAdd();

            } else if (order.action == MessageType ::Remove) {

                Remove(oldOrder, order);

            } else if (order.action == MessageType ::Modify) {
                //skip same price and same size
                if (oldOrder.qty == order.qty && oldOrder.price == order.price) {
                    //no change
                    return;
                }

                Modify(oldOrder, const_cast<Order&>(order));
                // update oldOrder info
                //oldOrder.size = order.size;
                //oldOrder.price = order.price;

            } else {
                //unknown action

            }
        }
    }

    void Engine::CheckPriceCross() {
        if (buyOrderBook_.empty() || sellOrderBook_.empty()) {
            return;
        }
        auto sellIter = sellOrderBook_.begin();
        auto buyIter = buyOrderBook_.rbegin();
        if (sellIter->first <= buyIter->first) {
            ErrorMonitor::GetInstance().CrossBidAsk();
        }
    }

    void Engine::PrintMidQuote(){
        if (buyOrderBook_.empty() || sellOrderBook_.empty()) {
            std::cout << "--- MIDQuote --------------------------------------\n";
            std::cout << "NAN" << endl;

        } else {
            auto sellIter = sellOrderBook_.begin(); //lowest sell
            auto buyIter = buyOrderBook_.rbegin(); //highest buy
            auto mid = (sellIter->first + buyIter->first)/2.;
            std::cout << "--- MIDQuote --------------------------------------\n";
            std::cout << (double)mid << endl;
        }
    }
    //
    void Engine::Modify(Order &oldOrder, Order &newOrder) {
        CheckPriceCross();

        if (oldOrder.status == OrderStatus::TradeDeleted) {
            ErrorMonitor::GetInstance().modifyOrderDeleted();
            return;
        }

        if (oldOrder.qty == newOrder.qty &&
                oldOrder.side == newOrder.side &&
                oldOrder.price == newOrder.price) {
            // this is either modify order but without any change or
            // after trade happened
            // change(which was done in HandleTrade)
            ErrorMonitor::GetInstance().ModifyIgnored();
            return;
        }

        // not same side or not same price
        if (newOrder.side != oldOrder.side || newOrder.price != oldOrder.price) {
            // remove old order
            Remove(oldOrder, oldOrder);
            Add(newOrder);
        } else {
            // same side, same price, diff size, keep time priority
            // TODO if size = 0
            if (newOrder.side == BUY) {
                auto buyOrderList = buyOrderBook_.find(oldOrder.price);
                if (buyOrderList != buyOrderBook_.end()) {
                    oldOrder.ptr->quantity = newOrder.qty;
                } else {
                    ErrorMonitor::GetInstance().modifyOrderDeleted();
                    return;
                }
            } else if (newOrder.side == SELL) {
                auto sellOrderList = sellOrderBook_.find(oldOrder.price);
                if (sellOrderList != sellOrderBook_.end()) {
                    oldOrder.ptr->quantity = newOrder.qty;
                } else {
                    ErrorMonitor::GetInstance().modifyOrderDeleted();
                    return;
                }
            }
        }
    }

    void Engine::Remove(Order &oldOrder, const Order &newOrder) {
        CheckPriceCross();

        // to remove order, their price, size, side must be equal.
        if (oldOrder.status != OrderStatus::TradeDeleted) {
            if (oldOrder.price != newOrder.price ||
                oldOrder.qty != newOrder.qty ||
                oldOrder.side != newOrder.side) {
                ErrorMonitor::GetInstance().RemoveWithWrongData();
                return;
            }
        }


        // if the order status is 'trade deleted' means we don't need to modify order book
        if (oldOrder.status != OrderStatus::TradeDeleted) {
            PriceOrderBook &map = oldOrder.side == BUY ? buyOrderBook_ : sellOrderBook_;
            auto iter = map.find(oldOrder.price);

            if (iter == map.end()) {
                ErrorMonitor::GetInstance().RemoveWithWrongData();
            } else {
                auto ordList = iter->second;
                ordList.erase(oldOrder.ptr);
                // change order list total size
                ordList.ChangeTradeSize(-oldOrder.qty);

                if (ordList.empty()) {
                    map.erase(iter);
                }
            }
        }

        // remove from hisorderentry.
        auto oldOrderIt = hisOrderEntry_.find(oldOrder.orderId);
        if (oldOrderIt != hisOrderEntry_.end()) {
            hisOrderEntry_.erase(oldOrderIt);
        }
    }

    void Engine::Add(const Order &tmpOrder) {
        CheckPriceCross();

        auto ret = hisOrderEntry_.insert(std::make_pair(tmpOrder.orderId, tmpOrder));
        Order &order = ret.first->second;

        // put in the book
        PriceOrderBook &map = order.side == BUY? buyOrderBook_ : sellOrderBook_;
        auto iter = map.find(order.price);
        if (iter!=map.end()) {
            iter->second.emplace_back(order.qty, order.orderId);
            iter->second.ChangeTradeSize(order.qty);
            order.ptr = iter->second.end();
            order.ptr--;
        } else {
            auto ret = map.insert(std::make_pair(order.price, SamePriceOrderList()));
            ret.first->second.emplace_back(order.qty, order.orderId);
            ret.first->second.ChangeTradeSize(order.qty);
            order.ptr = ret.first->second.end();
            order.ptr--;
        }
    }

    void Engine::HandleTrade(const Trade &trade) {
        if (buyOrderBook_.empty() || sellOrderBook_.empty()) {
            ErrorMonitor::GetInstance().TradeOnMissingOrder();
            return;
        }

        auto buyIter = buyOrderBook_.end();
        buyIter--;
        if (buyIter->first < trade.tradePrice) {
            ErrorMonitor::GetInstance().TradeOnMissingOrder();
            return;
        }


        auto sellIter = sellOrderBook_.find(trade.tradePrice);
        if (sellIter == sellOrderBook_.end()) {
            ErrorMonitor::GetInstance().TradeOnMissingOrder();
            return;
        }

        //ensure enough orderlist quantity
        TradeQty  tq = trade.tradeQty;
        auto sellOrderList = sellIter->second;
        auto buyOrderList = buyIter->second;
        if (buyOrderList.GetTradeSize() < trade.tradeQty ||
                sellOrderList.GetTradeSize() < trade.tradeQty) {
            ErrorMonitor::GetInstance().TradeOnMissingOrder();
            return;
        } else {
            sellOrderList.ChangeTradeSize(-tq);
            buyOrderList.ChangeTradeSize(-tq);
        }



        // sell order book
        auto curSellItem = sellOrderList.begin();
        auto endSellItem = sellOrderList.end();

        while (curSellItem != endSellItem) {
            auto orignOrd = this->hisOrderEntry_.find(curSellItem->orderId);
            if (orignOrd!=hisOrderEntry_.end()) {
                if (tq >= curSellItem->quantity) {
                    // mark order in hisorderentry as trade delete
                    orignOrd->second.TradeDelete();
                } else {
                    // change the hisorderentry order size
                    orignOrd->second.qty -= tq;
                }
            } else {
                ErrorMonitor::GetInstance().TradeOnMissingOrder();
            }

            if (tq >= curSellItem->quantity) {
                tq -= curSellItem->quantity;
                ++curSellItem;
            } else {
                curSellItem->quantity -= tq;
                tq = 0;
                break;
            }
        }
        sellOrderList.erase(sellOrderList.begin(), curSellItem);
        if (sellOrderList.empty()) {
            sellOrderBook_.erase(sellIter);
        }

        // buy order book
        tq = trade.tradeQty;

        auto curBuyItem = buyOrderList.begin();
        auto endBuyItem = buyOrderList.end();

        while (curBuyItem != endBuyItem) {
            auto orignOrd = this->hisOrderEntry_.find(curBuyItem->orderId);
            if (orignOrd!=hisOrderEntry_.end()) {
                if (tq >= curBuyItem->quantity) {
                    // mark order in hisorderentry as trade delete
                    orignOrd->second.TradeDelete();
                } else {
                    // change the hisorderentry order size
                    orignOrd->second.qty -= tq;
                }
            } else {
                ErrorMonitor::GetInstance().TradeOnMissingOrder();
            }

            if (tq >= curBuyItem->quantity) {
                tq -= curBuyItem->quantity;
                ++curBuyItem;
            } else {
                curBuyItem->quantity -= tq;
                tq = 0;
                break;
            }
        }
        buyOrderList.erase(buyOrderList.begin(),curBuyItem);


        if (buyOrderList.empty()) {
            buyOrderBook_.erase(buyIter);
        }

        // print recent trade message =================================
        if (recentTradePrice_ != trade.tradePrice) {
            recentTradePrice_ = trade.tradePrice;
            recentTradeSize_ = 0;
        }
        recentTradeSize_ += trade.tradeQty;
        std::cout << "--- TRADE --------------------------------------\n";
        std::cout << recentTradeSize_ << "@" << (double)(recentTradePrice_) << endl;
    }


    void Engine::PrintOrderBook(std::ostream &os) const {
        os << "---ORDER BOOK --------------------------------------\n";
        os << "SELLS\n";
        for (auto it = sellOrderBook_.rbegin(); it != sellOrderBook_.rend(); ++it) {
            auto lst = it->second;
            os << it->first;
            for (auto sz : lst) {
                os << ", " << sz.quantity;
            }
            os << endl;
        }

        os << "BUYS\n";
        for (auto it = buyOrderBook_.rbegin(); it != buyOrderBook_.rend(); ++it) {
            auto lst = it->second;
            os << it->first;
            for (auto sz : lst) {
                os << ", " << sz.quantity;
            }
            os << endl;
        }
    }

}