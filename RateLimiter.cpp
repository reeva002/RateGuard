
#include "RateLimiter.h"

RateLimiter::RateLimiter(int limit, int duration) {
    maxRequests = limit;
    windowDuration = std::chrono::seconds(duration);
}

void RateLimiter::refreshWindow(UserData& user) {
    auto now = std::chrono::steady_clock::now();

    if (now - user.windowStart >= windowDuration) {
        user.requestCount = 0;
        user.windowStart = now;
    }
}

bool RateLimiter::allowRequest(std::string userId) {
    UserData& user = users[userId];

    refreshWindow(user);

    if (user.requestCount < maxRequests) {
        user.requestCount++;
        return true;
    }

    return false;
}

int RateLimiter::getRequestsUsed(std::string userId) {
    UserData& user = users[userId];

    refreshWindow(user);

    return user.requestCount;
}

int RateLimiter::getRequestsRemaining(std::string userId) {
    return maxRequests - getRequestsUsed(userId);
}
