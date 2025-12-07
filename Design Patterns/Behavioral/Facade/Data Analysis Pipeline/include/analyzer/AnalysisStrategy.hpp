#ifndef ANALYSIS_STRATEGY_HPP
#define ANALYSIS_STRATEGY_HPP

#include <vector>
#include <string>

class AnalysisStrategy {
public:
    virtual std::string analyze(const std::vector<std::string>& data) = 0;
    virtual ~AnalysisStrategy() = default;
};

class AverageAnalysis : public AnalysisStrategy {
public:
    std::string analyze(const std::vector<std::string>& data) override;
};

class CustomAnalysis : public AnalysisStrategy {
public:
    std::string analyze(const std::vector<std::string>& data) override;
};

#endif // ANALYSIS_STRATEGY_HPP
