#include "traderjoe/strategy/base_strategy.h"
#include <string>
#include <vector>

Strategy::StrategyInput::StrategyInput(double _price_open, double _price_close, double _price_low, double _price_high, unsigned int _volume_open, unsigned int _volume_close, std::string _ticker)
{
    price_open = _price_open;
    price_close = _price_close;

    price_low = _price_low;
    price_high = _price_high;

    volume_open = _volume_open;
    volume_close = _volume_close;

    ticker = _ticker;
}

int Strategy::BaseStrategy::SharesToBuy(std::vector<Strategy::StrategyInput> s_ins)
{
    return 1;
}