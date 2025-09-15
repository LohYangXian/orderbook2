#pragma once

#include <map>
#include <iostream>
#include <boost/optional.hpp>

class OrderBook {
    std::map<int, int> bids, asks;
    void add(int price, int amount, bool bid);
    void remove(int price, int amount, bool bid);

public:

    struct BidAsk {
        typedef boost::optional<std::pair<int,int>> Entry;
        Entry bid, ask;
        boost::optional<int> spread() const;
    };

    inline bool is_empty() const 
    {
        return bids.empty() && asks.empty();
    }

    void add_bid(int price, int amount);
    void add_ask(int price, int amount);
    void remove_bid(int price, int amount);
    void remove_ask(int price, int amount);

    BidAsk get_bid_ask() const;

    // The following friend function overloads the << operator for OrderBook.
    // This allows you to print an OrderBook object directly using std::cout.
    // Declaring it as 'friend' gives the function access to private members
    // of the OrderBook class, so it can format and display all order data.
    //
    // Example usage:
    //   OrderBook book;
    //   std::cout << book << std::endl;
    friend std::ostream& operator<<(std::ostream& os, const OrderBook& book);
    friend std::ostream& operator<<(std::ostream& os, const OrderBook::BidAsk& bidask);
};