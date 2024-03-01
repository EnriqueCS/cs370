#include <gtest/gtest.h>
#include "papi_metrics.h" // Include your HashingPerformanceMonitor definition
#include "../Algorithms/HashingAlgorithm.h"
#include <fstream>
#include <nlohmann/json.hpp> // For JSON handling

using json = nlohmann::json;

// Test fixture class
class HashingPerformanceMonitorTestFixture : public ::testing::Test {
protected:
    HashingPerformanceMonitor* monitor = nullptr;
    std::string testOutputFile = "test_metrics_output.json";

    // Setup before each test
    void SetUp() override {
        // Initialize the monitor with a mock or suitable parameters
        monitor = new HashingPerformanceMonitor(HashingAlgorithmType::CHAINING, 10);
    }

    // Cleanup after each test
    void TearDown() override {
        delete monitor;
        monitor = nullptr;
        // Optionally, remove the test output file
        std::remove(testOutputFile.c_str());
    }

    // Helper function to read JSON file
    json readJsonFile(const std::string& filePath) {
        std::ifstream file(filePath);
        json j;
        file >> j;
        return j;
    }
};

// Test case for insert operation and JSON output
TEST_F(HashingPerformanceMonitorTestFixture, InsertAndWriteJson) {
    // Assuming insert function is correctly implemented
    monitor->insert("key", "value");
    monitor->writeTotalMetricsToJson(testOutputFile);

    // Verify JSON file is created and contains expected structure
    auto metricsJson = readJsonFile(testOutputFile);
    EXPECT_TRUE(metricsJson.contains("totalInsertMetrics"));
    EXPECT_TRUE(metricsJson["totalInsertMetrics"].contains("cpuCycles"));
    // Add more checks as necessary to validate the JSON structure and values
}

// Additional tests can be added for search, remove, and other functionalities
