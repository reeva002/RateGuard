
#include "TokenBucketLimiter.h"
#include <algorithm>

TokenBucketLimiter::TokenBucketLimiter(
    double bucketCapacity,
    double tokensPerSecond
)
    : capacity(bucketCapacity),
      refillRate(tokensPerSecond) {
}

void TokenBucketLimiter::refillBucket(Bucket& bucket, TimePoint now) {
    std::chrono::duration<double> elapsed =
        now - bucket.lastRefillTime;

    if (elapsed.count() > 0) {
        bucket.tokens = std::min(
            capacity,
            bucket.tokens + elapsed.count() * refillRate
        );

        bucket.lastRefillTime = now;
    }
}

bool TokenBucketLimiter::allowRequest(const std::string& userId) {
    TimePoint now = Clock::now();

    auto it = userBuckets.find(userId);

    if (it == userBuckets.end()) {
        it = userBuckets.emplace(
            userId,
            Bucket(capacity, now)
        ).first;
    }

    refillBucket(it->second, now);

    if (it->second.tokens >= 1.0) {
        it->second.tokens -= 1.0;
        return true;
    }

    return false;
}

double TokenBucketLimiter::getTokensRemaining(
    const std::string& userId
) {
    TimePoint now = Clock::now();

    auto it = userBuckets.find(userId);

    if (it == userBuckets.end()) {
        return capacity;
    }

    refillBucket(it->second, now);

    return it->second.tokens;
}
