
#ifndef SLIDING_WINDOW_LIMITER_H
#define SLIDING_WINDOW_LIMITER_H

#include <string>
#include <unordered_map>
#include <deque>
#include <chrono>

class SlidingWindowLimiter {
public:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

private:
    int maxRequests;
    std::chrono::seconds windowDuration;

    std::unordered_map<std::string, std::deque<TimePoint>> userRequests;

    TimePoint currentTime() const;

public:
    SlidingWindowLimiter(int limit, int duration);

    // Constructor for tests that use a simulated clock
    SlidingWindowLimiter(int limit, int duration, TimePoint startTime);

    bool allowRequest(const std::string& userId);
    int getRequestsUsed(const std::string& userId);
    int getRequestsRemaining(const std::string& userId);

    // Move simulated time forward during tests
    void advanceTime(std::chrono::seconds amount);
    
private:
    bool useSimulatedTime = false;
    TimePoint simulatedTime;
};

#endif
