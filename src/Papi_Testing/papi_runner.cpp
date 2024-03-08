#include "../Algorithms/HashingAlgorithm.h"
#include "./TestingLib/papi_metrics.h"
#include "./TestingLib/test_fixture.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

namespace fs = std::filesystem;

// Example usage of HashingPerformanceMonitorTestFixture
void exampleTest() {
    // Initialize the test fixture with specific algorithm type, output file location, and table size
    HashingPerformanceMonitorTestFixture testFixture(HashingAlgorithmType::CHAINING, "out/test_out", 10);
    testFixture.SetUp();
    testFixture.monitor->insert("key", "value");
    testFixture.monitor->writeTotalMetricsToTxt(testFixture.testOutputFile);
    testFixture.TearDown();
}

std::string getAlgorithmName(HashingAlgorithmType algType) {
    switch (algType) {
        case HashingAlgorithmType::CHAINING: return "Chaining";
        case HashingAlgorithmType::CUCKOO_HASHING: return "Cuckoo";
        case HashingAlgorithmType::OPEN_ADDRESSING: return "OpenAddressing";
        default: return "Unknown";
    }
}

void processFile(const fs::path& filePath, const fs::path& outputDir, HashingAlgorithmType algType) {
    // Metric information for the HashingPerformanceMonitor, replace with actual metrics you're interested in
    std::vector<MetricInfo> metricInfos = {
        {PAPI_TOT_CYC, "Total Cycles"},
        {PAPI_TOT_INS, "Total Instructions"},
        {PAPI_L3_TCM, "Level 3 Cache Misses"},
        {PAPI_BR_MSP, "Branch Mispredictions"}
        // Add more metrics as needed
    };

    // Initialize test fixture for each file, now also passing metric information
    HashingPerformanceMonitorTestFixture testFixture(algType, outputDir.string(), 1000, metricInfos);
    testFixture.SetUp();

    // Open the file and insert each element into the hashtable
    std::ifstream fileStream(filePath);
    std::string line;
    while (getline(fileStream, line)) {
        // Assuming each line is an element to insert
        testFixture.monitor->insert(line, "value"); // Adjust based on file format
    }

    // Prepare filename for the metrics output
    std::string filenameWithoutExt = filePath.stem().string(); // This gets the filename without the extension
    // Construct the full path for the output metrics file
    fs::path outputFilePath = outputDir / (filenameWithoutExt + "_metrics.txt");
    
    // Write metrics to text file for this file's test
    testFixture.monitor->writeTotalMetricsToTxt(outputFilePath.string());
    testFixture.TearDown();

    fileStream.close();
}

void processDirectory(const fs::path& inputDir, const fs::path& outputDirBase, const std::vector<HashingAlgorithmType>& hashingAlgorithms) {
    for (const auto& entry : fs::recursive_directory_iterator(inputDir)) {
        if (entry.is_directory()) {
            auto relativePath = fs::relative(entry.path(), inputDir);
            for (HashingAlgorithmType algType : hashingAlgorithms) {
                std::string algName = getAlgorithmName(algType);
                for (const auto& fileEntry : fs::directory_iterator(entry.path())) {
                    if (!fileEntry.is_directory()) {
                        fs::path outputDir = outputDirBase / relativePath / algName;
                        fs::create_directories(outputDir);
                        processFile(fileEntry.path(), outputDir, algType);
                    }
                }
            }
        }
    }
}

int main() {
    // exampleTest();
    fs::path inputDataDir = "../Data";
    fs::path outputDataDir = "../Papi_Results";
    std::vector<HashingAlgorithmType> hashingAlgorithms = {
        HashingAlgorithmType::CHAINING, 
        HashingAlgorithmType::CUCKOO_HASHING, 
        HashingAlgorithmType::OPEN_ADDRESSING
    };
    processDirectory(inputDataDir, outputDataDir, hashingAlgorithms);
    return 0;
}
