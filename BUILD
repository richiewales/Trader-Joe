cc_binary(
    name = "simulate_day",
    srcs = ["traderjoe/client_utils/client.h", "traderjoe/client_utils/client.cpp", "traderjoe/sim/simulate_day.cpp"],
    includes = ["traderjoe/client_utils/client.h"],
    deps = [
        "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ],
)

cc_binary(
    name = "view_open_positions",
    srcs = ["examples/view_open_positions.cpp"],
    deps = [
        "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ],
)

cc_binary(
    name = "run_stream_handler",
    srcs = ["examples/run_stream_handler.cpp"],
    deps = [
        "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ],
)

cc_binary(
    name = "check_if_market_is_open",
    srcs = ["examples/check_if_market_is_open.cpp"],
    deps = [
        "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ],
)

cc_binary(
    name = "view_account_info",
    srcs = ["examples/view_account_info.cpp"],
    deps = [
        "@com_github_marpaia_alpaca_trade_api_cpp//alpaca:alpaca",
    ],
)