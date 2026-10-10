
# RateGuard — C++ API Rate Limiter

RateGuard is a C++ project that implements three rate-limiting algorithms and integrates them with an HTTP server. It controls how frequently requests can be made to an API and returns an HTTP 429 response when the configured limit is exceeded.

## Features

- Implements Fixed Window, Sliding Window, and Token Bucket algorithms.
- Provides a simple HTTP API using the cpp-httplib library.
- Returns HTTP 200 for allowed requests and HTTP 429 when the rate limit is exceeded.
- Supports selecting the rate-limiting algorithm through a URL query parameter.
- Includes separate source files and tests for the algorithms.

## Rate-Limiting Algorithms

### 1. Fixed Window

Allows a fixed number of requests during a defined time window. The request count resets when the window expires.

### 2. Sliding Window

Tracks request timestamps over a moving time window to enforce the request limit.

### 3. Token Bucket

Maintains a bucket of tokens. Each request consumes one token, and tokens refill over time at a configured rate.

## Technologies Used

- C++
- Object-Oriented Programming (OOP)
- HTTP and REST-style API concepts
- cpp-httplib
- Microsoft Visual C++ (MSVC)

## HTTP API

The server runs locally at:

`http://localhost:8080/api/test`

Select an algorithm using the `algorithm` query parameter.

| Algorithm | Example URL |
|---|---|
| Fixed Window | `http://localhost:8080/api/test?algorithm=fixed` |
| Sliding Window | `http://localhost:8080/api/test?algorithm=sliding` |
| Token Bucket | `http://localhost:8080/api/test?algorithm=token` |

### Responses

- **HTTP 200:** Request allowed.
- **HTTP 429:** Rate limit exceeded.
- **HTTP 400:** Invalid algorithm name.

## Configuration

The current HTTP server uses these settings:

| Algorithm | Configuration |
|---|---|
| Fixed Window | 5 requests per 60 seconds |
| Sliding Window | 5 requests per 60 seconds |
| Token Bucket | Capacity of 5 tokens, refilling at 1 token per second |

These limits are configured in `RateGuardServer.cpp`.

## Project Structure

```text
RateGuard/
├── main.cpp
├── RateLimiter.h
├── RateLimiter.cpp
├── SlidingWindowLimiter.h
├── SlidingWindowLimiter.cpp
├── TokenBucketLimiter.h
├── TokenBucketLimiter.cpp
├── tests.cpp
├── sliding_window_tests.cpp
├── token_bucket_tests.cpp
├── RateGuardServer.cpp
├── http_test.cpp
├── httplib.h
└── README.md
```

## Build and Run

This project was compiled on Windows using Microsoft Visual C++ (MSVC).

From a suitable Visual Studio Developer Command Prompt, navigate to the project directory and compile the HTTP server:

```bat
cl /EHsc /std:c++14 RateGuardServer.cpp RateLimiter.cpp SlidingWindowLimiter.cpp TokenBucketLimiter.cpp /Fe:RateGuardServer.exe /link ws2_32.lib
```

Run the server:

```bat
RateGuardServer.exe
```

Open one of the API URLs listed above in your browser to test it.

## Testing

The project includes separate test programs for the three algorithms.

Previously completed test results:

- Fixed Window: 6 tests passed.
- Sliding Window: 6 tests passed.
- Token Bucket: 5 tests passed.
- Total: 17 tests passed.

## Future Improvements

- Return structured JSON responses.
- Add automated HTTP endpoint tests.
- Improve error handling and configuration.
- Add support for identifying individual users.
- Improve concurrency safety before production use.

## Author

Developed as a C++ learning project to explore rate-limiting algorithms, testing, and HTTP server integration.
