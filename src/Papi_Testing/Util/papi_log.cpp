#include "./papi_log.h"

namespace LoggingFunctions {

void logProcessStart(const fs::path& filePath, const fs::path& outputDir) {
    std::cout << "Starting processFile with filePath: " << filePath << " and outputDir: " << outputDir << std::endl;
}

void logNumMetrics(size_t numMetrics) {
    std::cout << "Number of available metrics: " << numMetrics << std::endl;
}

void logNumGroups(size_t numGroups) {
    std::cout << "Number of groups (metrics divided by 4): " << numGroups << std::endl;
}

void logProcessingGroup(size_t groupIndex) {
    std::cout << "\nProcessing groupIndex: " << groupIndex << std::endl;
}

void logGroupIndices(size_t groupIndex, size_t startIdx, size_t endIdx) {
    std::cout << "Group " << groupIndex << " - Start index: " << startIdx << ", End index: " << endIdx << std::endl;
}

void logMetricsSubsetSize(size_t subsetSize) {
    std::cout << "Metrics subset size for this group: " << subsetSize << std::endl;
}

void logTestFixtureSetupCompleted(size_t groupIndex) {
    std::cout << "TestFixture setup completed for groupIndex: " << groupIndex << std::endl;
}

void logFailedFileOpen(const fs::path& filePath) {
    std::cerr << "Failed to open file: " << filePath << std::endl;
}

void logCompletedInsertion(size_t groupIndex) {
    std::cout << "Completed inserting elements from file into hash table for groupIndex: " << groupIndex << std::endl;
}

void logOutputFilePath(const fs::path& outputFilePath) {
    std::cout << "Output file path for metrics: " << outputFilePath << std::endl;
}

void logCompletedProcessingGroup(size_t groupIndex) {
    std::cout << "Completed processing for groupIndex: " << groupIndex << "\n" << std::endl;
}

void logFinishedProcessing() {
    std::cout << "Finished processFile function." << std::endl;
}

} // namespace LoggingFunctions
