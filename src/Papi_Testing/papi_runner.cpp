// Assuming the presence of "HashingAlgorithmConfig.h" for HashingAlgorithmConfig struct definition
#include "../Algorithms/HashingAlgorithm.h"
#include "./TestingLib/test_fixture.h"
#include "./Util/papi_avail.h"
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>
#include <iterator>
#include <iostream>

namespace fs = std::filesystem;
using MetricInfo = std::pair<int, std::string>;
typedef fs::path FilePath; // Typedef for filesystem path

// Process a single metric for a file using a specific hashing algorithm configuration
std::string processMetric(const FilePath& filePath, const HashingConfig& hashConfig, const MetricInfo& metric) {
    HashingPerformanceMonitorTestFixture testFixture(hashConfig, metric);
    testFixture.SetUp();

    std::ifstream fileStream(filePath);
    if (!fileStream) {
        testFixture.TearDown();
        return "Failed to open file: " + filePath.string();
    }

    std::string line;
    std::vector<std::string> lines; // Vector to store each line with an ID

    while (getline(fileStream, line)) {
        lines.push_back(line); // Store line with its ID
    }

    // Assuming testFixture.getPerformanceData() processes these lines with IDs
    std::string metricsString = testFixture.getPerformanceData(lines);
    testFixture.TearDown();
    fileStream.close();
    return metricsString;
}

std::string processAllMetrics(const FilePath& filePath, const HashingConfig& hashConfig) {
    std::string allMetrics;

    for (const MetricInfo& metric : availMetrics) {
        std::string metricResult = processMetric(filePath, hashConfig, metric);
        allMetrics += metric.second + "\n" + metricResult + "\n\n";
    }

    return allMetrics;
}

void writeMetricsToFile(const std::string& fileName, const FilePath& outputDir, const std::string& allMetrics) {
    // Construct the full path with a proper file name, including a separator between the file name and "metrics_summary.txt"
    FilePath metricsOutputPath = outputDir / (fileName + "_metrics_summary.txt");

    std::ofstream outFile(metricsOutputPath);
    if (!outFile) {
        std::cerr << "Failed to open file for writing: " << metricsOutputPath << std::endl;
        return;
    }

    outFile << allMetrics;
    outFile.close();

    std::cout << "Metrics written to: " << metricsOutputPath << std::endl;
}

void processFile(const FilePath& filePath, const FilePath& outputDir, const HashingConfig& hashConfig) {
    std::string file = filePath.filename().stem().string();
    std::string allMetrics = "---> File: " + file + "\n" + processAllMetrics(filePath, hashConfig);
    writeMetricsToFile(file, outputDir, allMetrics);
}

// Process all files in a directory, using a specific hashing algorithm configuration
void processFilesInDirectory(const FilePath& directoryPath, const FilePath& outputDirBase, const FilePath& relativePath, const HashingAlgorithmConfig& defaultAlgConfig) {
    bool dirCreated = false;
    FilePath outputDir;
    int hashConfigNumber = 1000; // Default hash config number
    FilePath dataDetailsPath = directoryPath / "data_details";

    // Read hash config number from data_details file
    std::ifstream file(dataDetailsPath);
    if (file) {
        std::string line;
        if (std::getline(file, line)) {
            try {
                hashConfigNumber = std::stoi(line); // Set hash config number from the file
                std::cout << "Hash config number set to " << hashConfigNumber << " from file data_details" << std::endl;
            } catch (const std::exception& e) {
                std::cerr << "Error reading hash config number: " << e.what() << std::endl;
            }
        }
        file.close();
    } else {
        std::cerr << "Failed to open data_details file." << std::endl;
        return; // Exit if data_details cannot be read
    }

    // Process all files in the directory
    for (const auto& fileEntry : fs::directory_iterator(directoryPath)) {
        if (fileEntry.is_directory() || fileEntry.path().filename() == "data_details") continue;

        if (!dirCreated) {
            outputDir = outputDirBase / relativePath / fileEntry.path().filename().stem() / defaultAlgConfig.getName();
            std::cout << "Creating output directory: " << outputDir << std::endl;
            fs::create_directories(outputDir);
            dirCreated = true;
        }

        processFile(fileEntry.path(), outputDir, defaultAlgConfig.getHashConfig(hashConfigNumber));
    }
}

// Process the entire directory tree, using all specified hashing algorithm configurations
void processDirectory(const FilePath& inputDir, const FilePath& outputDirBase) {
    std::vector<HashingAlgorithmConfig> hashingAlgorithms = {
        HashingAlgorithmConfig(HashingAlgorithmType::CHAINING),
        HashingAlgorithmConfig(HashingAlgorithmType::CUCKOO_HASHING),
        HashingAlgorithmConfig(HashingAlgorithmType::OPEN_ADDRESSING)
    };

    for (const auto& entry : fs::recursive_directory_iterator(inputDir)) {
        if (!entry.is_directory()) continue;

        auto relativePath = fs::relative(entry.path(), inputDir);
        for (const HashingAlgorithmConfig& algConfig : hashingAlgorithms) {
            processFilesInDirectory(entry.path(), outputDirBase, relativePath, algConfig);
        }
    }
}

int main() {
    FilePath inputDataDir = "../Data";
    FilePath outputDataDir = "../Papi_Results";
    processDirectory(inputDataDir, outputDataDir);
    return 0;
}
