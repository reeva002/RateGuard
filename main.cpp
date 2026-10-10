
#include <iostream>
#include <string>
#include "RateLimiter.h"
#include "SlidingWindowLimiter.h"
#include "TokenBucketLimiter.h"

using namespace std;

int main() {
    cout << "====================================\n";
    cout << "       RateGuard API Rate Limiter\n";
    cout << "====================================\n\n";

    cout << "Choose a rate-limiting algorithm:\n";
    cout << "1. Fixed Window\n";
    cout << "2. Sliding Window\n";
    cout << "3. Token Bucket\n";

    int choice;
    cout << "\nEnter your choice (1-3): ";
    cin >> choice;

    string userId;
    cout << "Enter user ID: ";
    cin >> userId;

    int limit;
    cout << "Enter maximum requests / bucket capacity: ";
    cin >> limit;

    if (limit <= 0) {
        cout << "Limit must be greater than zero.\n";
        return 1;
    }

    if (choice == 1 || choice == 2) {
        int duration;
        cout << "Enter window duration in seconds: ";
        cin >> duration;

        if (duration <= 0) {
            cout << "Duration must be greater than zero.\n";
            return 1;
        }

        if (choice == 1) {
            RateLimiter limiter(limit, duration);

            cout << "\nTesting Fixed Window...\n";

            for (int i = 1; i <= limit + 1; i++) {
                if (limiter.allowRequest(userId)) {
                    cout << "Request " << i << ": Allowed\n";
                } else {
                    cout << "Request " << i << ": Blocked\n";
                }
            }
        } else {
            SlidingWindowLimiter limiter(limit, duration);

            cout << "\nTesting Sliding Window...\n";

            for (int i = 1; i <= limit + 1; i++) {
                if (limiter.allowRequest(userId)) {
                    cout << "Request " << i << ": Allowed\n";
                } else {
                    cout << "Request " << i << ": Blocked\n";
                }
            }
        }
    } else if (choice == 3) {
        double refillRate;
        cout << "Enter tokens refilled per second: ";
        cin >> refillRate;

        if (refillRate <= 0) {
            cout << "Refill rate must be greater than zero.\n";
            return 1;
        }

        TokenBucketLimiter limiter(limit, refillRate);

        cout << "\nTesting Token Bucket...\n";

        for (int i = 1; i <= limit + 1; i++) {
            if (limiter.allowRequest(userId)) {
                cout << "Request " << i << ": Allowed\n";
            } else {
                cout << "Request " << i << ": Blocked\n";
            }
        }

        cout << "\nTokens remaining: "
             << limiter.getTokensRemaining(userId) << "\n";
    } else {
        cout << "Invalid choice. Please select 1, 2, or 3.\n";
        return 1;
    }

    cout << "\nRateGuard finished.\n";

    return 0;
}
