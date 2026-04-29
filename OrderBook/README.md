# Order Book

This project simulates a limit-order book, maintaining buy and sell orders grouped by price levels and enforcing a price-time priority using sorted containers and FIFO queues, enabling efficient matching and spread calculation.

The project currently supports the following operations:

- Viewing/printing the order book i.e. all buy and sell orders
- Placing an order
- Modifying an order's quantity
- Cancelling an order
- Getting the best ask
- Getting the best bid
- Viewing the bid-ask spread

##

- _A matching engine feature (order execution) is yet to be implemented._

##

To run the program, first compile with:

```bash
g++ -std=c++20 main.cpp -o a.out
```

then run the generated executable file with:

```bash
./a.out
```
