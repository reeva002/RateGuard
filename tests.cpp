
#include <iostream>
#include <cassert>
#include "RateLimiter.h"

using namespace std;

int main() {
    cout << "Running RateGuard tests...\n\n";

    // Test 1: First request is allowed
    RateLimiter test1(5, 10);
    assert(test1.allowRequest("user1") == true);
    cout << "Test 1 passed: First request allowed\n";

    // Test 2: Five requests are allowed
    RateLimiter test2(5, 10);

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

    // Test 5: Another user has an independent limit
    assert(test2.allowRequest("user2") == true);
    cout << "Test 5 passed: Separate user works\n";

    
    // Test 6: Request window resets after expiration
    RateLimiter test3(2, 1);

    assert(test3.allowRequest("user3") == true);
    assert(test3.allowRequest("user3") == true);
    assert(test3.allowRequest("user3") == false);

    cout << "Waiting for the request window to expire...\n";

    // Temporarily test again after a short manual wait.
    cout << "Wait 2 seconds, then press Enter to continue: ";
    cin.ignore(10000, '\n');
    cin.get();

    assert(test3.allowRequest("user3") == true);
    cout << "Test 6 passed: Window reset works\n";

    cout << "\nAll tests passed successfully!\n";

    return 0;
}
