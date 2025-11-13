#include "decorators/CachingDB.hpp"
#include "decorators/LoggingDB.hpp"
#include "decorators/AuditingDB.hpp"
#include "decorators/RateLimitingDB.hpp"
#include "decorators/TransactionDB.hpp"
#include "decorators/ValidationDB.hpp"
#include "decorators/MockDB.hpp"
#include <iostream>
#include <thread>
#include <chrono>

int main() {
    IDataBase::Ptr db = std::make_unique<MockDB>();

    db = std::make_unique<ValidationDB>(std::move(db));
    db = std::make_unique<TransactionDB>(std::move(db));
    db = std::make_unique<RateLimitingDB>(std::move(db));
    db = std::make_unique<AuditingDB>(std::move(db));
    db = std::make_unique<LoggingDB>(std::move(db));
    db = std::make_unique<CachingDB>(std::move(db));

    std::cout << "=== Decorator Pattern Demo ===\n\n";

    // Normal query – cache hit on second call
    db->execute("SELECT * FROM users WHERE id = :id", {{"id", "42"}});
    db->execute("SELECT * FROM users WHERE id = :id", {{"id", "42"}});

    // Transaction
    db->execute("BEGIN", {});
    db->execute("INSERT INTO users(name) VALUES(:n)", {{"n", "Alice"}});
    db->execute("INSERT INTO users(name) VALUES(:n)", {{"n", "Bob"}});
    db->execute("COMMIT", {});

    // Validation error
    db->execute("DROP TABLE users", {});

    // Rate-limit test
    std::cout << "\n--- Rate-limit burst ---\n";
    for (int i = 0; i < 12; ++i) {
        db->execute("SELECT COUNT(*) FROM logs", {});
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }

    return 0;
}