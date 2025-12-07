#include "../../include/pipeline/DataPipelineFacade.hpp"
#include <thread>
#include <future>

void DataPipelineFacade::run(const std::string& inputFile, const std::string& outputFile) {
    Logger::instance().log("Starting pipeline...");
    auto loadFuture = std::async(std::launch::async, [&]() { return loader.load(inputFile); });

    auto cleanFuture = std::async(std::launch::async, [&]() {
        return cleaner.clean(loadFuture.get());
    });

    auto analysisResult = analyzer->analyze(cleanFuture.get());

    reporter.generate(analysisResult, outputFile);
    
    Logger::instance().log("Pipeline finished successfully.");
}
