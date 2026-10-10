
#include "httplib.h"
#include "RateLimiter.h"
#include "SlidingWindowLimiter.h"
#include "TokenBucketLimiter.h"

#include <iostream>
#include <string>

int main() {
    httplib::Server server;

    // Create all three rate limiters.
    RateLimiter fixedLimiter(5, 60);
    SlidingWindowLimiter slidingLimiter(5, 60);
    TokenBucketLimiter tokenLimiter(5, 1);

    server.Get("/api/test", [&](const httplib::Request& req,
                                httplib::Response& res) {
        std::string userId = "demo-user";
        std::string algorithm = "fixed";

        // Read the algorithm from the URL.
        if (req.has_param("algorithm")) {
            algorithm = req.get_param_value("algorithm");
        }

        bool allowed = false;

        if (algorithm == "fixed") {
            allowed = fixedLimiter.allowRequest(userId);
        }
        else if (algorithm == "sliding") {
            allowed = slidingLimiter.allowRequest(userId);
        }
        else if (algorithm == "token") {
            allowed = tokenLimiter.allowRequest(userId);
        }
        else {
            res.status = 400;
            res.set_content(
                "Invalid algorithm. Use fixed, sliding, or token.",
                "text/plain"
            );
            return;
        }

        if (allowed) {
            res.status = 200;
            res.set_content(
                "Request allowed! Algorithm: " + algorithm,
                "text/plain"
            );
        }
        else {
            res.status = 429;
            res.set_content(
                "Too Many Requests! Algorithm: " + algorithm,
                "text/plain"
            );
        }
    });

    std::cout << "RateGuard server running at "
              << "http://localhost:8080/api/test\n";

    server.listen("127.0.0.1", 8080);

    return 0;
}
