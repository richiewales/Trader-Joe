#include <iostream>
#include<string>

#include "alpaca/alpaca.h"
#include "traderjoe/client_utils/client.h"

using namespace std;

namespace client_utils {
    alpaca::Client get_client()
    {
        // Parse the configuration from the environment
        auto env = alpaca::Environment();
        if (auto status = env.parse(); !status.ok()) 
        {
            std::cerr << "Error parsing config from environment: " << status.getMessage() << std::endl;
            throw to_string(status.getCode());
        }
        
        // Create an API client object
        return alpaca::Client(env);
    }
}