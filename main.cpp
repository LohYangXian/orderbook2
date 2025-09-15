#include <iostream>
#include "OrderBook.h"

int main() {
    OrderBook book;
    std::cout << book << std::endl;
    // if (book.is_empty()) {
        // std::cout << "Order book is empty." << std::endl;
    // } else {
        // std::cout << "Order book has orders." << std::endl;
    // }
    book.add_bid(100, 10);
    book.add_ask(105, 15);
    std::cout << book << std::endl;
    auto spread = book.get_bid_ask();
    std::cout << "Spread: " << spread << std::endl;
    return 0;
}