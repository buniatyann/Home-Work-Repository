#include "../../include/handlers/CompressionHandler.hpp"
#include <iostream>

void CompressionHandler::doHandle(Request& req, Response& res) {
    std::cout << "[Compression] Response will be gzip-compressed (simulated)\n";
}