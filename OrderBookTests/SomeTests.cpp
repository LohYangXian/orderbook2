#include <gtest/gtest.h>
#include "OrderBook.h"

TEST(OrderBookTests, OrderBookEmptyByDefault) 
{
    OrderBook book;
    EXPECT_TRUE(book.is_empty());
}

TEST(OrderBookTests, OrderAdditionWorks) 
{
    OrderBook book;
    book.add_bid(123, 456);
    auto bidask = book.get_bid_ask();
    EXPECT_TRUE(bidask.bid.is_initialized());
    auto bid = bidask.bid.get();
    EXPECT_EQ(bid.first, 123);
    EXPECT_EQ(bid.second, 456);
}

TEST(OrderBookTests, OrderRemovalWorks) 
{
    OrderBook book;
    book.add_bid(123, 456);
    book.remove_bid(123, 200);
    auto bidask = book.get_bid_ask();
    EXPECT_TRUE(bidask.bid.is_initialized());
    auto bid = bidask.bid.get();
    EXPECT_EQ(bid.first, 123);
    EXPECT_EQ(bid.second, 256); // 456 - 200 = 256
}

TEST(OrderBookTests, SpreadCalculated)
{
    OrderBook book;
    book.add_bid(50,100);
    book.add_ask(70,100);
    auto bidask = book.get_bid_ask();
    EXPECT_TRUE(bidask.bid.is_initialized());
    EXPECT_TRUE(bidask.ask.is_initialized());
    auto spread = bidask.spread();
    EXPECT_TRUE(spread.is_initialized());
    EXPECT_EQ(spread.get(), 20); // 70 - 50 = 20
}