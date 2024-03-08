#ifndef HASHINGPERFORMANCEMONITORTESTFIXTURE_H
#define HASHINGPERFORMANCEMONITORTESTFIXTURE_H

#include "./papi_metrics.h"
#include <vector>
#include <utility> // For std::pair
#include <string>
#include <cstdio> // For std::remove

// Define a pair of PAPI event code and its string name
using MetricInfo = std::pair<int, std::string>;

class HashingPerformanceMonitorTestFixture {
public:
    HashingPerformanceMonitor* monitor = nullptr;
    std::string testOutputFile;
    HashingAlgorithmType algorithmType; // Variable to specify the hashing algorithm
    int tableSize; // Variable to specify the size of the table
    std::vector<MetricInfo> metricInfos; // Variable to store metric information

    // Constructor to specify the hashing algorithm, test output file location, table size, and metric information
    HashingPerformanceMonitorTestFixture(HashingAlgorithmType type, const std::string& outputFile, int size, const std::vector<MetricInfo>& metrics)
    : algorithmType(type), testOutputFile(outputFile), tableSize(size), metricInfos(metrics) {}

    // Setup before each test
    void SetUp() {
        // Initialize the monitor with the specified algorithm type, table size, and metric information
        monitor = new HashingPerformanceMonitor(algorithmType, tableSize, metricInfos);
    }

    // Cleanup after each test
    void TearDown() {
        delete monitor;
        monitor = nullptr;
        // Optionally, remove the test output file
        std::remove(testOutputFile.c_str());
    }

    // Function to trigger writing total metrics to text file
    void writeTotalMetricsToTxt(const std::string& dest) {
        monitor->writeTotalMetricsToTxt(dest);
    }
};

#endif // HASHINGPERFORMANCEMONITORTESTFIXTURE_H
