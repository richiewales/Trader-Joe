#include <iostream>
#include <iomanip>
#include <vector>

#include "alpaca/alpaca.h"
#include "gflags/gflags.h"
#include "glog/logging.h"
#include "traderjoe/client_utils/client.h"
#include "traderjoe/strategy/base_strategy.h"

using namespace std;

/*
Design:
    -   Provide a starting timestamp, "current_time"
    -   Iterate a whole day one step at a time (minute?)
    -   When pulling stats like bars, use this changing "current_time" timestamp
    -   Keep track of net gain/loss from day
*/

int main(int argc, char* argv[]) 
{
    google::InitGoogleLogging(argv[0]);
    gflags::ParseCommandLineFlags(&argc, &argv, true);

    FLAGS_logtostderr = 1;
    FLAGS_minloglevel = 2;    

    auto ticker = "AAPL";

    if (argc < 2)
        throw "Expected input arg: {StartTimestamp}, e.g. -- 2020-04-03T09:30:00-08:00";

    // Setup API Client
    auto client = client_utils::get_client();

    // Parse start-time
    std::tm tm = {};
    std::stringstream ss(argv[1]);
    ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S-00:00");
    auto tp = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    auto end_tp = (std::chrono::hours(0) + tp) + (std::chrono::minutes(10));

    // Iterate one minute at a time
    auto minute_step = std::chrono::minutes(1);

    while (tp < end_tp)
    {
        char start_buffer[26];
        char end_buffer[26];

        // Get % change over last 10 minutes
        auto prev_tp = tp - std::chrono::minutes(1);
        
        std::time_t tmp = std::chrono::system_clock::to_time_t(prev_tp);
        std::tm tmp_tm = *std::gmtime(&tmp);
        if (strftime(start_buffer, sizeof start_buffer, "%Y-%m-%dT%H:%M:%S-00:00", &tmp_tm))
            puts(start_buffer);

        tmp = std::chrono::system_clock::to_time_t(tp);
        tmp_tm = *std::gmtime(&tmp);
        if (strftime(end_buffer, sizeof end_buffer, "%Y-%m-%dT%H:%M:%S-00:00", &tmp_tm))
            puts(end_buffer);

        auto bars_response = client.getBars(
            {ticker}, 
            start_buffer,
            end_buffer,
            "",
            "",
            "1Min",
            100
        );
        
        tp += minute_step;

        if (auto status = bars_response.first; !status.ok()) 
        {
            cerr << "Error getting bars information: " << status.getMessage() << endl;
            continue;
        }

        auto bars = bars_response.second.bars["AAPL"];
        if (bars.size() == 0)
            continue;
        
        auto start_price = bars.front().open_price;
        auto end_price = bars.back().close_price;
        auto percent_change = (end_price - start_price) / start_price * 100;
        cout << "AAPL moved " << percent_change << "% over the time range." << start_price << " " << end_price << " " << bars.back().time << std::endl;

        Strategy::StrategyInput si(
            bars.front().open_price, 
            bars.back().close_price, 
            min(bars.front().low_price, bars.back().low_price),
            max(bars.front().high_price, bars.back().high_price),
            bars.front().volume,
            bars.back().volume,
            ticker
        );
        
        int shares_to_buy = Strategy::BaseStrategy::SharesToBuy({si});

        cout << "Strategy suggests to buy " << shares_to_buy << " shares" << endl;
    }

    return 0;
}