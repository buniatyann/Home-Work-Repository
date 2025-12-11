#ifndef DATA_PIPELINE_FACADE_HPP
#define DATA_PIPELINE_FACADE_HPP

#include <string>
#include "../dataloader/DataLoader.hpp"
#include "../datacleaner/DataCleaner.hpp"
#include "../analyzer/Analyzer.hpp"
#include "../report/ReportGenerator.hpp"
#include "../utils/Logger.hpp"

class DataPipelineFacade {
public:
    void run(const std::string& inputFile, const std::string& outputFile);

private:
    DataLoader loader;
    DataCleaner cleaner;
    Analyzer* analyzer;
    ReportGenerator reporter;
};

#endif // DATA_PIPELINE_FACADE_HPP
