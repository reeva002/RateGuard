
#include "httplib.h"
#include <iostream>

int main() {
    httplib::Server server;

    server.Get("/api/test", [](const httplib::Request& req,
                               httplib::Response& res) {
        res.set_content("RateGuard HTTP server is working!",
                        "text/plain");
    });

    std::cout << "RateGuard test server running at "
              << "http://localhost:8080\n";

    server.listen("127.0.0.1", 8080);

    return 0;
}
