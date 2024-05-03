#ifndef LOGGING_FUNCTIONS_H
#define LOGGING_FUNCTIONS_H

#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

namespace LoggingFunctions {

void logProcessStart(const fs::path& filePath, const fs::path& outputDir);
void logNumMetrics(size_t numMetrics);
void logNumGroups(size_t numGroups);
void logProcessingGroup(size_t groupIndex);
void logGroupIndices(size_t groupIndex, size_t startIdx, size_t endIdx);
void logMetricsSubsetSize(size_t subsetSize);
void logTestFixtureSetupCompleted(size_t groupIndex);
void logFailedFileOpen(const fs::path& filePath);
void logCompletedInsertion(size_t groupIndex);
void logOutputFilePath(const fs::path& outputFilePath);
void logCompletedProcessingGroup(size_t groupIndex);
void logFinishedProcessing();

} // namespace LoggingFunctions

#endif // LOGGING_FUNCTIONS_H
