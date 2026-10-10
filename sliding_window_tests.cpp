
#include <iostream>
#include <cassert>
#include <chrono>
#include "SlidingWindowLimiter.h"

using namespace std;

int main() {
    cout << "Running Sliding Window tests...\n\n";

    // Test 1: First request is allowed
    SlidingWindowLimiter test1(5, 10);

    assert(test1.allowRequest("user1") == true);

    cout << "Test 1 passed: First request allowed\n";


    // Test 2: Five requests are allowed
    SlidingWindowLimiter test2(5, 10);

    for (int i = 0; i < 5; i++) {
        assert(test2.allowRequest("user1") == true);
    }

    cout << "Test 2 passed: Five requests allowed\n";


    // Test 3: Sixth request is blocked
    assert(test2.allowRequest("user1") == false);

    cout << "Test 3 passed: Sixth request blocked\n";


    // Test 4: No requests remain
    assert(test2.getRequestsRemaining("user1") == 0);

    cout << "Test 4 passed: No requests remaining\n";


    // Test 5: Different users have independent limits
    assert(test2.allowRequest("user2") == true);

    cout << "Test 5 passed: Separate user works\n";


    // Test 6: Requests expire individually using simulated time
    using Clock = SlidingWindowLimiter::Clock;

    auto startTime = Clock::now();

    SlidingWindowLimiter test3(2, 4, startTime);

    // First request at time 0
    assert(test3.allowRequest("user3") == true);

    // Move forward 2 seconds and send a second request
    test3.advanceTime(chrono::seconds(2));

    assert(test3.allowRequest("user3") == true);

    // Both requests are still within the 4-second window
    assert(test3.getRequestsUsed("user3") == 2);
    assert(test3.allowRequest("user3") == false);

    // Move to time 4 seconds: first request expires
    test3.advanceTime(chrono::seconds(2));

    assert(test3.getRequestsUsed("user3") == 1);

    // A new request should now be allowed
    assert(test3.allowRequest("user3") == true);

    cout << "Test 6 passed: Requests expire individually\n";


    cout << "\nAll Sliding Window tests passed!\n";

    return 0;
}
