#pragma once

#include <string>
#include <vector>

namespace Strategy
{
    class StrategyInput
    {
        double price_open, price_close, price_low, price_high;
        unsigned int volume_open, volume_close;
        std::string ticker;

        public:
        StrategyInput(double _price_open, double _price_close, double _price_low, double _price_high, unsigned int _volume_open, unsigned int _volume_close, std::string _ticker);
    };

    class BaseStrategy
    {
        // Explicitly mark private so there is no expectation for this to be instantiated
        private:
        BaseStrategy();
        ~BaseStrategy();

        public:
        static int SharesToBuy(std::vector<StrategyInput> s_ins);
    };
}