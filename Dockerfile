

FROM gcc:14

WORKDIR /app

COPY . .

RUN g++ -std=c++14 -pthread RateGuardServer.cpp RateLimiter.cpp SlidingWindowLimiter.cpp TokenBucketLimiter.cpp -o RateGuardServer

CMD ["./RateGuardServer"]
