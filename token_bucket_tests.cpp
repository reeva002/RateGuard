
#include <iostream>
#include <cassert>
#include "TokenBucketLimiter.h"

using namespace std;

int main() {
    cout << "Running Token Bucket tests...\n\n";

    // Test 1: First request is allowed
    TokenBucketLimiter test1(5, 1.0);
    assert(test1.allowRequest("user1") == true);
    cout << "Test 1 passed: First request allowed\n";

    // Test 2: Bucket allows requests up to capacity
    TokenBucketLimiter test2(3, 1.0);
    assert(test2.allowRequest("user1") == true);
    assert(test2.allowRequest("user1") == true);
    assert(test2.allowRequest("user1") == true);
    cout << "Test 2 passed: Requests within capacity allowed\n";

    // Test 3: Request blocked when bucket is empty
    assert(test2.allowRequest("user1") == false);
    cout << "Test 3 passed: Request blocked when bucket is empty\n";

    // Test 4: Separate users have separate buckets
    assert(test2.allowRequest("user2") == true);
    cout << "Test 4 passed: Separate user has its own bucket\n";

    // Test 5: Remaining tokens are correct
    TokenBucketLimiter test3(4, 1.0);
    test3.allowRequest("user3");
    assert(test3.getTokensRemaining("user3") <= 3.0);
    assert(test3.getTokensRemaining("user3") >= 0.0);
    cout << "Test 5 passed: Remaining tokens checked\n";

    cout << "\nAll Token Bucket tests passed!\n";

    return 0;
}
