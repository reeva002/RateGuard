
#ifndef TOKEN_BUCKET_LIMITER_H
#define TOKEN_BUCKET_LIMITER_H

#include <string>
#include <unordered_map>
#include <chrono>

class TokenBucketLimiter {
private:
    using Clock = std::chrono::steady_clock;
    using TimePoint = Clock::time_point;

    struct Bucket {
        double tokens;
        TimePoint lastRefillTime;

        Bucket(double capacity, TimePoint startTime)
            : tokens(capacity), lastRefillTime(startTime) {}
    };

    double capacity;
    double refillRate;
    std::unordered_map<std::string, Bucket> userBuckets;

    void refillBucket(Bucket& bucket, TimePoint now);

public:
    TokenBucketLimiter(double bucketCapacity, double tokensPerSecond);

    bool allowRequest(const std::string& userId);
    double getTokensRemaining(const std::string& userId);
};

#endif
