
#include "SlidingWindowLimiter.h"

SlidingWindowLimiter::SlidingWindowLimiter(int limit, int duration)
    : maxRequests(limit),
      windowDuration(std::chrono::seconds(duration)) {
}

SlidingWindowLimiter::SlidingWindowLimiter(
    int limit,
    int duration,
    TimePoint startTime
)
    : maxRequests(limit),
      windowDuration(std::chrono::seconds(duration)),
      useSimulatedTime(true),
      simulatedTime(startTime) {
}

SlidingWindowLimiter::TimePoint SlidingWindowLimiter::currentTime() const {
    if (useSimulatedTime) {
        return simulatedTime;
    }

    return Clock::now();
}

void SlidingWindowLimiter::advanceTime(std::chrono::seconds amount) {
    if (useSimulatedTime) {
        simulatedTime += amount;
    }
}

bool SlidingWindowLimiter::allowRequest(const std::string& userId) {
    TimePoint now = currentTime();
    auto& requests = userRequests[userId];

    while (!requests.empty() &&
           now - requests.front() >= windowDuration) {
        requests.pop_front();
    }

    if (requests.size() >= static_cast<size_t>(maxRequests)) {
        return false;
    }

    requests.push_back(now);
    return true;
}

int SlidingWindowLimiter::getRequestsUsed(const std::string& userId) {
    TimePoint now = currentTime();
    auto& requests = userRequests[userId];

    while (!requests.empty() &&
           now - requests.front() >= windowDuration) {
        requests.pop_front();
    }

    return static_cast<int>(requests.size());
}

int SlidingWindowLimiter::getRequestsRemaining(const std::string& userId) {
    return maxRequests - getRequestsUsed(userId);
}
