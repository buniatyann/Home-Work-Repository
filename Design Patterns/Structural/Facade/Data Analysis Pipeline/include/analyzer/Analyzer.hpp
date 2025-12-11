#ifndef ANALYZER_HPP
#define ANALYZER_HPP

#include <vector>
#include <string>
#include "AnalysisStrategy.hpp"

class Analyzer {
public:
    Analyzer(AnalysisStrategy* strategy);
    void setStrategy(AnalysisStrategy* strategy);
    std::string analyze(const std::vector<std::string>& data);

private:
    AnalysisStrategy* strategy;
};

#endif // ANALYZER_HPP
