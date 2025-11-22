#include <iostream>
#include <memory>
#include "./include/handlers/LoggingHandler.hpp"
#include "./include/handlers/CorsHandler.hpp"
#include "./include/handlers/RateLimitHandler.hpp"
#include "./include/handlers/AuthenticationHandler.hpp"
#include "./include/handlers/AuthorizationHandler.hpp"
#include "./include/handlers/CompressionHandler.hpp"
#include "./include/controller/APIController.hpp"

int main() {
    std::cout << "=== HTTP Request Pipeline – Chain of Responsibility ===\n\n";

    auto pipeline = std::make_unique<LoggingHandler>();
    pipeline->setNext(std::make_unique<CorsHandler>())
            ->setNext(std::make_unique<RateLimitHandler>())
            ->setNext(std::make_unique<AuthenticationHandler>())
            ->setNext(std::make_unique<AuthorizationHandler>())
            ->setNext(std::make_unique<CompressionHandler>())
            ->setNext(std::make_unique<APIController>());

    Request req;
    Response res;

    // Test 1: No auth
    std::cout << "Test 1: Public endpoint (no auth needed)\n";
    req = Request{"GET", "/public", "", {}};
    pipeline->handle(req, res);
    std::cout << "→ " << res.statusCode << " " << res.body << "\n\n";

    // Test 2: Valid token + admin path
    std::cout << "Test 2: Admin endpoint with valid token\n";
    req = Request{"GET", "/admin/dashboard", "", {{"Authorization", "Bearer valid-token-123"}}};
    res = Response{};
    pipeline->handle(req, res);
    std::cout << "→ " << res.statusCode << " " << res.body << "\n\n";

    // Test 3: Invalid token
    std::cout << "Test 3: Invalid token\n";
    req = Request{"POST", "/api/data", "", {{"Authorization", "Bearer wrong"}}};
    res = Response{};
    pipeline->handle(req, res);
    std::cout << "→ " << res.statusCode << " " << res.body << "\n";

    return 0;
}