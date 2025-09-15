#include "OrderBook.h"

void OrderBook::add_bid(int price, int amount) 
{
    add(price, amount, true);
}

void OrderBook::add_ask(int price, int amount) 
{
    add(price, amount, false);
}

void OrderBook::add(int price, int amount, bool bid) 
{
    if (bid)
        bids[price] += amount;
    else
        asks[price] += amount;
}

std::ostream& operator<<(std::ostream& os, const OrderBook& book) 
{
    if (book.is_empty()) {
        os << "ORDER BOOK EMPTY";
        return os;
    }

    for (auto it = book.asks.begin(); it != book.asks.end(); ++it) {
        os << it -> first << "\t" << it -> second << std::endl;
    }

    os << std::endl;
    for (auto it = book.bids.rbegin(); it != book.bids.rend(); ++it) {
        os << it -> first << "\t" << it -> second << std::endl;
    }
    return os;
}

std::ostream& operator<<(std::ostream& os, const OrderBook::BidAsk& bidask) 
{
    auto print = [&](const OrderBook::BidAsk::Entry& e, const std::string& text) 
    {
        bool have_value = e.is_initialized();
        if (have_value) 
        {
            auto value = e.get();
            os << value.second << text << "s @" << value.first;
        } else {
            os << "NO " << text;
        }
    };
    print(bidask.bid, "BID");
    os << ", ";
    print(bidask.ask, "ASK");
    return os;
}

// Returns the best bid and ask prices currently in the order book.
// - The best bid is the highest price in the bids map (if any).
// - The best ask is the lowest price in the asks map (if any).
// - Both are returned as optional values in a BidAsk struct.
// - If there are no bids or asks, the corresponding value will be empty.
//
// Example usage:
//   auto best = book.get_bid_ask();
//   if (best.bid) { /* use best.bid->first and best.bid->second */ }
//   if (best.ask) { /* use best.ask->first and best.ask->second */ }
OrderBook::BidAsk OrderBook::get_bid_ask() const {
    BidAsk result;

    auto best_bid = bids.rbegin();
    if (best_bid != bids.rend()) 
        result.bid = *best_bid;

    auto best_ask = asks.begin();
    if (best_ask != asks.end())
        result.ask = *best_ask;

    return result;
}

void OrderBook::remove_bid(int price, int amount) {
    remove(price, amount, true);
}

void OrderBook::remove_ask(int price, int amount) {
    remove(price, amount, false);
}

// Removes a specified amount from an order at a given price level.
// - If 'bid' is true, removes from the bids table; otherwise, from asks.
// - Finds the order at the given price. If it exists, subtracts 'amount'.
// - If the remaining amount becomes zero, the price level is erased.
// - If the price does not exist, nothing happens.
//
// Parameters:
//   price  - The price level to remove from.
//   amount - The quantity to subtract.
//   bid    - True for bids, false for asks.
//
// Example usage:
//   remove(100, 5, true);  // Removes 5 units from bid at price 100
//   remove(105, 2, false); // Removes 2 units from ask at price 105
void OrderBook::remove(int price, int amount, bool bid) {
    auto& table = bid ? bids : asks;
    auto it = table.find(price);
    if (it != table.end()) 
    {
        it -> second -= amount;
        if (it -> second == 0)
           table.erase(it);
    }
}

boost::optional<int> OrderBook::BidAsk::spread() const {
    boost::optional<int> result;
    if (bid.is_initialized() && ask.is_initialized()) {
        result = ask->first - bid->first;
    }
    return result;
}