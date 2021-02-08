# Trader Joe
Trader Joe is a live market algo that uses Alpaca to buy and trade stock throughout the day using various defined strategies (TBD). Trader Joe is written in C++ for no reason other than it was an excuse for me to learn the language in a setting where latency is sort of important.

## Design

Basic flow:
- Define Base strategy class that takes a list of data points for a ticker
- Strategy will form KPIs from these data points
- Given some filtering, processing, or even model inference, a decision to buy X shares of the ticker is provided

In addition to writing the strategy, we need a sophisticated simulation engine to backtest a strategy on historical data. Currently I am getting most of the code bootstrapped to test on a single day/hour of data. Next I will extend this simulation process to a longer, provided input time range.

- Give time range to backtest
- Select trading strategy
- Run strategy and output metrics on P/L, etc.