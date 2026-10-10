
#ifndef RATELIMITER_H
#define RATELIMITER_H

#include <string>
#include <unordered_map>
#include <chrono>

struct UserData {
    int requestCount = 0;
    std::chrono::steady_clock::time_point windowStart =
        std::chrono::steady_clock::now();
};

class RateLimiter {
private:
    int maxRequests;
    std::chrono::seconds windowDuration;
    std::unordered_map<std::string, UserData> users;

    void refreshWindow(UserData& user);

public:
    RateLimiter(int limit, int duration);

    bool allowRequest(std::string userId);
    int getRequestsUsed(std::string userId);
    int getRequestsRemaining(std::string userId);
};

#endif
