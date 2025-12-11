#include "../../include/analyzer/Analyzer.hpp"

Analyzer::Analyzer(AnalysisStrategy* strategy) : strategy(strategy) {}

void Analyzer::setStrategy(AnalysisStrategy* strategy) {
    this->strategy = strategy;
}

std::string Analyzer::analyze(const std::vector<std::string>& data) {
    return strategy->analyze(data);
}
