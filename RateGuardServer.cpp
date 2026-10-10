#include <fstream>
#include <iterator>
#include <cstdlib>
#include <stdexcept>
#include <iostream>
#include <string>

#include "httplib.h"
#include "RateLimiter.h"
#include "SlidingWindowLimiter.h"
#include "TokenBucketLimiter.h"

int main() {
    httplib::Server server;

    // Serve the RateGuard webpage.
    server.Get("/", [](const httplib::Request& req,
                       httplib::Response& res) {
        std::ifstream file("public/index.html");

        if (!file.is_open()) {
            res.status = 500;
            res.set_content(
                "Could not load public/index.html",
                "text/plain"
            );
            return;
        }

        std::string html(
            (std::istreambuf_iterator<char>(file)),
            std::istreambuf_iterator<char>()
        );

        res.set_content(html, "text/html");
    });

    // Create all three rate limiters.
    RateLimiter fixedLimiter(5, 60);
    SlidingWindowLimiter slidingLimiter(5, 60);
    TokenBucketLimiter tokenLimiter(5, 1);

    // API endpoint for testing the algorithms.
    server.Get("/api/test", [&](const httplib::Request& req,
                                httplib::Response& res) {
        std::string userId = "demo-user";
        std::string algorithm = "fixed";

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

    const char* portEnv = std::getenv("PORT");
    int port = portEnv ? std::stoi(portEnv) : 8080;

    std::cout << "RateGuard server running on port "
              << port << std::endl;

    server.listen("0.0.0.0", port);

    return 0;
}
